#include <WifiManager.hpp>
#include <SPIFFS.h>
#include <Constants.hpp>
#include <FSUtils.hpp>
#include "Pages/wifimanager-html.h"

void Configure(AsyncWebServerRequest *request) {
    Serial.println("Configure");
    if (request->method() == HTTP_GET) {
        AsyncWebServerResponse * response = request->beginResponse(200, "text/html", WIFIMANAGER_HTML);
        request->send(response);
    } else {
        int params = request->params();
        for (int i = 0; i < params; i++) {
            AsyncWebParameter *p = request->getParam(i);
            if (p->isPost()) {
                // HTTP POST ssid value
                if (p->name() == PARAM_INPUT_1) {
                    String ssid = p->value().c_str();
                    Serial.print("SSID set to: ");
                    Serial.println(ssid);
                    // Write file to save value
                    writeFile(SPIFFS, ssidPath, ssid.c_str());
                }
                // HTTP POST pass value
                if (p->name() == PARAM_INPUT_2) {
                    String pass = p->value().c_str();
                    Serial.print("Password set to: ");
                    Serial.println(pass);
                    // Write file to save value
                    writeFile(SPIFFS, passPath, pass.c_str());
                }
                // HTTP POST ip value
                if (p->name() == PARAM_INPUT_3) {
                    String ip = p->value().c_str();
                    Serial.print("IP Address set to: ");
                    Serial.println(ip);
                    // Write file to save value
                    writeFile(SPIFFS, ipPath, ip.c_str());
                }
                // HTTP POST gateway value
                if (p->name() == PARAM_INPUT_4) {
                    String gateway = p->value().c_str();
                    Serial.print("Gateway set to: ");
                    Serial.println(gateway);
                    // Write file to save value
                    writeFile(SPIFFS, gatewayPath, gateway.c_str());
                }
                //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
            }
        }
        request->send(200, "text/plain", "Done. ESP will restart");
        delay(3000);
        ESP.restart();
    }
}