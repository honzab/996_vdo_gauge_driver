/*
VDO Gauge Driver Software for https://github.com/honzab/996_vdo_gauge_driver

Jan Brucek (jan@brucek.se), 2025
*/

#ifndef FOO_H_
#define FOO_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Takes measured V_in and returns corresponding temperature reading in ºC */
int vInToTemperatureInCelsius(float vin);

/* Returns output voltage based on input temperature in ºC */
float temperatureInCelsiusToVout(int temperature);

/* Returns integer value to set on the output pin based on the desired V_out */
int voltageToPinValue(float voltageOut);

/* Returns corresponding 0-5 voltage value for the pin value */
float pinValueToVoltage(int pinValue);

#ifdef __cplusplus
}
#endif

#endif
