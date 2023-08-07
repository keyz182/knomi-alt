/*********
  Rui Santos
  Complete instructions at https://RandomNerdTutorials.com/esp32-wi-fi-manager-asyncwebserver/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <Constants.hpp>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include "SPIFFS.h"
#include <FSUtils.hpp>
#include <WifiManager.hpp>
#include <AsyncElegantOTA.h>
#include "API.h"

#include "Display/Display.hpp"
#include "Display/SadScreen.h"
#include "Display/SleepyScreen.h"
#include "Display/PauseScreen.h"
#include "Display/NoWifiScreen.h"
#include "Display/HotendTempScreen.h"

#include "Pages/index-html.h"
#include "Pages/style-css.h"

DNSServer dnsServer;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

//Variables to save values from HTML form
String ssid;
String pass;
String ip;
String gateway;

IPAddress localIP;

// Set your Gateway IP address
IPAddress localGateway;
IPAddress subnet(255, 255, 0, 0);

API api = API();

Display display = Display();
SadScreen *sadScreen;
SleepyScreen *sleepyScreen;
PauseScreen *pauseScreen;
NoWiFiScreen *noWifiScreen;
HotendTempScreen * hotendTempScreen;

// Timer variables
unsigned long previousMillis = 0;
const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)
const long displayInterval = 1000;

// Initialize SPIFFS
void initSPIFFS() {
    if (!SPIFFS.begin(true)) {
        Serial.println("An error has occurred while mounting SPIFFS");
    }
    Serial.println("SPIFFS mounted successfully");
}

// Initialize WiFi
bool initWiFi() {
    if (ssid == "" || ip == "") {
        Serial.println("Undefined SSID or IP address.");
        return false;
    }

    WiFi.mode(WIFI_STA);
    localIP.fromString(ip.c_str());
    localGateway.fromString(gateway.c_str());


    if (!WiFi.config(localIP, localGateway, subnet)) {
        Serial.println("STA Failed to configure");
        return false;
    }
    WiFi.begin(ssid.c_str(), pass.c_str());
    Serial.println("Connecting to WiFi...");

    unsigned long currentMillis = millis();
    previousMillis = currentMillis;

    while (WiFi.status() != WL_CONNECTED) {
        currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            Serial.println("Failed to connect.");
            return false;
        }
    }

    Serial.println(WiFi.localIP());
    return true;
}

bool AP_MODE = false;

TaskHandle_t DisplayTickTask;
TaskHandle_t APITickTask;
TaskHandle_t ScreenManagerTask;

void displayTick(void *pvParameters) {
    Serial.print("displayTick running on core ");
    Serial.println(xPortGetCoreID());

    for (;;) {
        display.tick();
        yield();
    }
}

void apiTick(void *pvParameters) {
    delay(10);
    Serial.print("apiTick running on core ");
    Serial.println(xPortGetCoreID());

    for (;;) {
        api.tick();
        yield();
    }
}

void screenManager(void *pvParameters) {
    delay(20);
    Serial.print("screenManager running on core ");
    Serial.println(xPortGetCoreID());

    for (;;) {
        delay(1000);
        Serial.println(api.status);
        if (api.status == "unknown") {
            Serial.println("Setting sadScreen");
            display.setScreen(sadScreen);
        } else if (api.status == "standby") {
            Serial.println("Setting sleepyScreen");
            display.setScreen(sleepyScreen);
        } else if (api.status == "paused") {
            Serial.println("Setting pauseScreen");
            display.setScreen(pauseScreen);
        } else if (api.status == "printing") {
            Serial.println("Setting hotendTempScreen");
            display.setScreen(hotendTempScreen);
        } else {
            display.setScreen(sadScreen);
        }
        yield();
    }
}

void setup() {
//    delay(2000);
    display.display_Init();
    sadScreen = new SadScreen(display.tft);
    sleepyScreen = new SleepyScreen(display.tft);
    pauseScreen = new PauseScreen(display.tft);
    noWifiScreen = new NoWiFiScreen(display.tft);
    hotendTempScreen = new HotendTempScreen(display.tft, &api);

    display.setScreen(noWifiScreen);

    // Serial port for debugging purposes
    Serial.begin(115200);

    initSPIFFS();

    // Load values saved in SPIFFS
    ssid = readFile(SPIFFS, ssidPath);
    pass = readFile(SPIFFS, passPath);
    ip = readFile(SPIFFS, ipPath);
    gateway = readFile(SPIFFS, gatewayPath);

    Serial.println(ip);
    Serial.println(gateway);

    server.serveStatic("/", SPIFFS, "/");

    if (!initWiFi()) {
        AP_MODE = true;
        // Connect to Wi-Fi network with SSID and password
        Serial.println("Setting AP (Access Point)");
        // NULL sets an open Access Point
        WiFi.softAP("ESP-WIFI-MANAGER", NULL);

        dnsServer.start(53, "*", WiFi.softAPIP());

        IPAddress IP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(IP);
    }

    if (AP_MODE) {
        // Route for root / web page
        server.on("/redirect", HTTP_GET, Configure);
        server.on("/hotspot-detect.html", HTTP_GET, Configure);
        server.on("/generate_204", HTTP_GET, Configure);
        server.on("/", HTTP_GET, Configure);
        server.on("/", HTTP_POST, Configure);
    } else {
        // Route for root / web page
        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
            AsyncWebServerResponse * response = request->beginResponse(200, "text/html", INDEX_HTML);
            request->send(response);
        });

        // Route for root / web page
        server.on("/wifi", HTTP_GET, Configure);
        server.on("/wifi", HTTP_POST, Configure);
    }

    // Route to set GPIO state to HIGH
    server.on("/reset", HTTP_POST, [](AsyncWebServerRequest *request) {
        deleteFile(SPIFFS, "/ssid.txt");
        deleteFile(SPIFFS, "/pass.txt");
        deleteFile(SPIFFS, "/ip.txt");
        deleteFile(SPIFFS, "/gateway.txt");
        AsyncWebServerResponse * response = request->beginResponse(200, "text/html", INDEX_HTML);
        request->send(response);
    });


    // Route to set GPIO state to HIGH
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse * response = request->beginResponse(200, "text/css", STYLE_CSS);
        request->send(response);
    });


    // Route to set GPIO state to HIGH
    server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse * response = request->beginResponse(200, "text/html", INDEX_HTML);
        request->send(response);
    });

    // Route to set GPIO state to LOW
    server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse * response = request->beginResponse(200, "text/html", INDEX_HTML);
        request->send(response);
    });

    AsyncElegantOTA.begin(&server);
    server.begin();

    xTaskCreatePinnedToCore(
            displayTick, /* Task function. */
            "displayTick",   /* name of task. */
            10000,     /* Stack size of task */
            NULL,      /* parameter of the task */
            1,         /* priority of the task */
            &DisplayTickTask,    /* Task handle to keep track of created task */
            1);        /* pin task to core 0 */

    xTaskCreatePinnedToCore(
            apiTick, /* Task function. */
            "apiTick",   /* name of task. */
            10000,     /* Stack size of task */
            NULL,      /* parameter of the task */
            1,         /* priority of the task */
            &APITickTask,    /* Task handle to keep track of created task */
            1);        /* pin task to core 0 */

    xTaskCreatePinnedToCore(
            screenManager, /* Task function. */
            "screenManager",   /* name of task. */
            10000,     /* Stack size of task */
            NULL,      /* parameter of the task */
            1,         /* priority of the task */
            &ScreenManagerTask,    /* Task handle to keep track of created task */
            1);        /* pin task to core 0 */
}

void loop() {
    if (AP_MODE) {
        dnsServer.processNextRequest();
    } else {
        delay(1);
    }
}