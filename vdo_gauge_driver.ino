/*
VDO Gauge Driver for https://github.com/honzab/996_vdo_gauge_driver

Jan Brucek (jan@brucek.se), 2025
*/
void setup() {
    pinMode(1, OUTPUT);
}

/* Takes measured V_in and returns corresponding temperature reading in ºC */
int vInToTemperatureInCelsius(float vin) {
    // Ahsai's measurements in F:  8.5645 * x^4 - 59.284 * x^3 + 160.76 * x^2 - 245.49x + 299.24
    // to celsius:                 (x - 32) * (5 / 9)
    float f = (8.5645 * pow(vin, 4)) - (59.284 * pow(vin, 3)) + (160.76 * pow(vin, 2)) - (245.49 * vin) + 299.24;
    return (f - 32) * (5 / 9);
}

/* Returns output voltage based on input temperature in ºC */
float temperatureInCelsiusToVout(int temperature) {
    // v3(2025-05-24) 0,0741 + 0,0104x + −1,65×10^−05x^2
    return 0.0741 + (0.0104 * temperature) + (-1.65 * pow(10, -5) * pow(temperature, 2));
}

/* Returns integer value to set on the output pin based on the desired V_out */
int voutToPinValue(float vout) {
    return (int)(255.0 * vout / 5.0);
}

/* Returns corresponding 0-5 voltage value for the pin value */
float pinValueToVoltage(int pinValue) {
    return pinValue * (5.0 / 1023.0);
}


void loop() {
    /*
    float tempInCelsius = vInToTemperatureInCelsius(
        pinValueToVoltage(analogRead(A3))
    );
    analogWrite(1, voutToPinValue(
        temperatureInCelsiusToVout(tempInCelsius))
    );
    delay(1000);
    */

    // Test sequence to set the output pin to various temperatures
    int temp = 0;
    analogWrite(1, 0);
    delay(5000);

    for (temp = 50; temp < 150; temp += 10) {
        analogWrite(1, voutToPinValue(temperatureInCelsiusToVout(temp)));
        delay(5000);
    }

    delay(6000);
} 
