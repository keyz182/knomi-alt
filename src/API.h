//
// Created by keyz_ on 07/08/2023.
//

#ifndef KNOMI_ALT_API_H
#define KNOMI_ALT_API_H

#include "Arduino.h"

class API {
public:
    void tick();

    void setInterval(unsigned long);

    double bedtemp = 0;
    double target_bedtemp = 0;
    double tooltemp = 0;
    double target_tooltemp = 0;

    String status = "unknown";


private:
    unsigned long previousMillis = 0;
    unsigned long ApiInterval = 3000;
    String host = "192.168.1.11";
    String port = "7125";
};


#endif //KNOMI_ALT_API_H
