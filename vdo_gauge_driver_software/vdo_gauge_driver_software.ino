/*
VDO Gauge Driver Software for https://github.com/honzab/996_vdo_gauge_driver

Jan Brucek (jan@brucek.se), 2025
*/

#include "vdo_gauge_calc.h"

void setup() {
    pinMode(1, OUTPUT);

    // Just to show that it's operational, move to 150ºC and back on start
    analogWrite(1, voltageToPinValue(temperatureInCelsiusToVout(150)));
    delay(10000);
    analogWrite(1, 0);
}

void loop() {
    float tempInCelsius = vInToTemperatureInCelsius(
        pinValueToVoltage(analogRead(A3))
    );
    analogWrite(1, voltageToPinValue(
        temperatureInCelsiusToVout(tempInCelsius))
    );
    delay(100);


    /*
    // Copy input code
    float vIn = pinValueToVoltage(analogRead(A3));
    analogWrite(1, voltageToPinValue(vIn));
    delay(100);
    */

    // Test sequence to set the output pin to various temperatures
    /*
    int temp = 0;
    analogWrite(1, 0);
    delay(5000);

    for (temp = 50; temp < 150; temp += 10) {
        analogWrite(1, voltageToPinValue(temperatureInCelsiusToVout(temp)));
        delay(5000);
    }
    */
}
