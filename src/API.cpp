//
// Created by keyz_ on 07/08/2023.
//

#include "API.h"

#include <HTTPClient.h>
#include <ArduinoJson.h>

void API::tick() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= ApiInterval) {
        previousMillis = currentMillis;
        // Do stuff!
        String APIPath = String("http://" + host + ":" + port + "/api/printer");
        Serial.print("Doing HTTP Requests to: ");
        Serial.println(APIPath);

        HTTPClient http;
        http.setTimeout(2500);

        http.begin(APIPath);

        int httpCode = http.GET();

        yield();

        switch (httpCode) {
            case 200: {
                String payload = http.getString();
                DynamicJsonDocument doc(payload.length() * 2);
                deserializeJson(doc, payload);

                String bedtemp_str = doc["temperature"]["bed"]["actual"].as<String>();
                String target_bedtemp_str = doc["temperature"]["bed"]["target"].as<String>();
                String tooltemp_str = doc["temperature"]["tool0"]["actual"].as<String>();
                String target_tooltemp_str = doc["temperature"]["tool0"]["target"].as<String>();
                String printing_str = doc["state"]["flags"]["printing"].as<String>();
                String paused_str = doc["state"]["flags"]["paused"].as<String>();

//                Serial.println(bedtemp_str);
//                Serial.println(target_bedtemp_str);
//                Serial.println(tooltemp_str);
//                Serial.println(target_tooltemp_str);
//                Serial.println(printing_str);
//                Serial.println(paused_str);

                bedtemp = doc["temperature"]["bed"]["actual"].as<double>();
                target_bedtemp = doc["temperature"]["bed"]["target"].as<double>();
                tooltemp = doc["temperature"]["tool0"]["actual"].as<double>();
                target_tooltemp = doc["temperature"]["tool0"]["target"].as<double>();


                if (printing_str == "true") {
                    status = "printing";
                } else {
                    if (paused_str == "true") {
                        status = "paused";
                    } else {
                        status = "standby";
                    }
                }

                break;
            }
            default: {
                Serial.print("Unhandled HTTP Status: ");
                Serial.println(httpCode);
            }
        }
        http.end(); //Free the resources
    } else {
        delay(ApiInterval / 10);
    }
}

void API::setInterval(unsigned long interval) {
    ApiInterval = interval;
}