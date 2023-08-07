//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_WIFIMANAGER_HTML_H
#define KNOMI_ALT_WIFIMANAGER_HTML_H

#include <Arduino.h>

const String WIFIMANAGER_HTML PROGMEM = "<!DOCTYPE html>\n"
                                        "<html>\n"
                                        "<head>\n"
                                        "  <title>ESP Wi-Fi Manager</title>\n"
                                        "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                                        "  <link rel=\"icon\" href=\"data:,\">\n"
                                        "  <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n"
                                        "</head>\n"
                                        "<body>\n"
                                        "  <div class=\"topnav\">\n"
                                        "    <h1>ESP Wi-Fi Manager</h1>\n"
                                        "  </div>\n"
                                        "  <div class=\"content\">\n"
                                        "    <div class=\"card-grid\">\n"
                                        "      <div class=\"card\">\n"
                                        "        <form action=\"/\" method=\"POST\">\n"
                                        "          <p>\n"
                                        "            <label for=\"ssid\">SSID</label>\n"
                                        "            <input type=\"text\" id =\"ssid\" name=\"ssid\"><br>\n"
                                        "            <label for=\"pass\">Password</label>\n"
                                        "            <input type=\"text\" id =\"pass\" name=\"pass\"><br>\n"
                                        "            <label for=\"ip\">IP Address</label>\n"
                                        "            <input type=\"text\" id =\"ip\" name=\"ip\" value=\"192.168.1.200\"><br>\n"
                                        "            <label for=\"gateway\">Gateway Address</label>\n"
                                        "            <input type=\"text\" id =\"gateway\" name=\"gateway\" value=\"192.168.1.1\"><br>\n"
                                        "            <input type =\"submit\" value =\"Submit\">\n"
                                        "          </p>\n"
                                        "        </form>\n"
                                        "        <form action=\"/reset\" method=\"POST\">\n"
                                        "          <p>\n"
                                        "            <input type =\"submit\" value =\"Reset\">\n"
                                        "          </p>\n"
                                        "        </form>\n"
                                        "      </div>\n"
                                        "    </div>\n"
                                        "  </div>\n"
                                        "</body>\n"
                                        "</html>";

#endif //KNOMI_ALT_WIFIMANAGER_HTML_H
