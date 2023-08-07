//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_INDEX_H
#define KNOMI_ALT_INDEX_H

#include <Arduino.h>

const String INDEX_HTML PROGMEM = "<!DOCTYPE html>\n"
                                  "<html>\n"
                                  "  <head>\n"
                                  "    <title>ESP WEB SERVER</title>\n"
                                  "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                                  "    <link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n"
                                  "    <link rel=\"icon\" type=\"image/png\" href=\"favicon.png\">\n"
                                  "    <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">\n"
                                  "  </head>\n"
                                  "  <body>\n"
                                  "    <div class=\"topnav\">\n"
                                  "      <h1>ESP WEB SERVER</h1>\n"
                                  "    </div>\n"
                                  "    <div class=\"content\">\n"
                                  "      <div class=\"card-grid\">\n"
                                  "        <div class=\"card\">\n"
                                  "          <p class=\"card-title\"><i class=\"fas fa-lightbulb\"></i> GPIO 2</p>\n"
                                  "          <p>\n"
                                  "            <a href=\"on\"><button class=\"button-on\">ON</button></a>\n"
                                  "            <a href=\"off\"><button class=\"button-off\">OFF</button></a>\n"
                                  "          </p>\n"
                                  "          <p class=\"state\">State: %STATE%</p>\n"
                                  "        </div>\n"
                                  "      </div>\n"
                                  "    </div>\n"
                                  "  </body>\n"
                                  "</html>";

#endif //KNOMI_ALT_INDEX_H
