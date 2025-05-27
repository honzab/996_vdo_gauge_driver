#include <iostream>
#include <cmath>
using namespace std;

#include "../vdo_gauge_calc.h"

template<typename T>
bool assert(string what, T expected, T actual) {
    if (expected != actual) {
        cout << "Error: " << what << " expected " << expected << " but got " << actual << "\n";
        return false;
    } else {
        cout << "OK: " << what << " expected " << expected << " and got " << actual << "\n";
        return true;
    }
}

// Specialized version for float comparisons with tolerance
bool assert(string what, float expected, float actual, float tolerance = 0.001f) {
    if (fabs(expected - actual) > tolerance) {
        cout << "Error: " << what << " expected " << expected << " but got " << actual << " (diff: " << fabs(expected - actual) << ")\n";
        return false;
    } else {
        cout << "OK: " << what << " expected " << expected << " and got " << actual << " (diff: " << fabs(expected - actual) << ")\n";
        return true;
    }
}

int main() {
    bool result = true;
    result &= assert("pinValueToVoltage(0)", 0.0f, pinValueToVoltage(0));
    result &= assert("pinValueToVoltage(100)", 0.488759f, pinValueToVoltage(100));
    result &= assert("pinValueToVoltage(200)", 0.977517f, pinValueToVoltage(200));
    result &= assert("pinValueToVoltage(500)", 2.44379f, pinValueToVoltage(500));
    result &= assert("pinValueToVoltage(1023)", 5.0f, pinValueToVoltage(1023));

    result &= assert("voltageToPinValue(0.0)", 0, voltageToPinValue(0.0));
    result &= assert("voltageToPinValue(0.5)", 25, voltageToPinValue(0.5));
    result &= assert("voltageToPinValue(1.0)", 51, voltageToPinValue(1.0));
    result &= assert("voltageToPinValue(1.5)", 76, voltageToPinValue(1.5));
    result &= assert("voltageToPinValue(2.0)", 102, voltageToPinValue(2.0));
    result &= assert("voltageToPinValue(2.5)", 127, voltageToPinValue(2.5));
    result &= assert("voltageToPinValue(3.0)", 153, voltageToPinValue(3.0));
    result &= assert("voltageToPinValue(3.5)", 178, voltageToPinValue(3.5));
    result &= assert("voltageToPinValue(4.0)", 204, voltageToPinValue(4.0));
    result &= assert("voltageToPinValue(4.5)", 229, voltageToPinValue(4.5));

    result &= assert("vInToTemperatureInCelsius(0.0)", 148, vInToTemperatureInCelsius(0.0));
    result &= assert("vInToTemperatureInCelsius(0.2)", 124, vInToTemperatureInCelsius(0.2));
    result &= assert("vInToTemperatureInCelsius(0.4)", 106, vInToTemperatureInCelsius(0.4));
    result &= assert("vInToTemperatureInCelsius(0.6)", 92, vInToTemperatureInCelsius(0.6));
    result &= assert("vInToTemperatureInCelsius(0.8)", 81, vInToTemperatureInCelsius(0.8));
    result &= assert("vInToTemperatureInCelsius(1.0)", 73, vInToTemperatureInCelsius(1.0));
    result &= assert("vInToTemperatureInCelsius(1.2)", 66, vInToTemperatureInCelsius(1.2));
    result &= assert("vInToTemperatureInCelsius(1.4)", 60, vInToTemperatureInCelsius(1.4));
    result &= assert("vInToTemperatureInCelsius(1.6)", 55, vInToTemperatureInCelsius(1.6));
    result &= assert("vInToTemperatureInCelsius(1.8)", 50, vInToTemperatureInCelsius(1.8));
    result &= assert("vInToTemperatureInCelsius(2.0)", 45, vInToTemperatureInCelsius(2.0));
    result &= assert("vInToTemperatureInCelsius(2.2)", 41, vInToTemperatureInCelsius(2.2));
    result &= assert("vInToTemperatureInCelsius(2.4)", 38, vInToTemperatureInCelsius(2.4));
    result &= assert("vInToTemperatureInCelsius(2.6)", 36, vInToTemperatureInCelsius(2.6));
    result &= assert("vInToTemperatureInCelsius(2.7)", 0, vInToTemperatureInCelsius(2.7)); // Test threshold
    result &= assert("vInToTemperatureInCelsius(3.0)", 0, vInToTemperatureInCelsius(3.0)); // Above threshold
    result &= assert("vInToTemperatureInCelsius(0.1)", 135, vInToTemperatureInCelsius(0.1)); // Near zero
    result &= assert("vInToTemperatureInCelsius(2.65)", 35, vInToTemperatureInCelsius(2.65)); // Near threshold

    result &= assert("temperatureInCelsiusToVout(30)", 0.0f, temperatureInCelsiusToVout(30)); // Below threshold
    result &= assert("temperatureInCelsiusToVout(35)", 0.0f, temperatureInCelsiusToVout(35)); // Below threshold
    result &= assert("temperatureInCelsiusToVout(40)", 0.4637f, temperatureInCelsiusToVout(40)); // At threshold
    result &= assert("temperatureInCelsiusToVout(45)", 0.508687f, temperatureInCelsiusToVout(45));
    result &= assert("temperatureInCelsiusToVout(50)", 0.55285f, temperatureInCelsiusToVout(50));
    result &= assert("temperatureInCelsiusToVout(60)", 0.6387f, temperatureInCelsiusToVout(60));
    result &= assert("temperatureInCelsiusToVout(70)", 0.72125f, temperatureInCelsiusToVout(70));
    result &= assert("temperatureInCelsiusToVout(80)", 0.8005f, temperatureInCelsiusToVout(80));
    result &= assert("temperatureInCelsiusToVout(90)", 0.87645f, temperatureInCelsiusToVout(90));
    result &= assert("temperatureInCelsiusToVout(100)", 0.9491f, temperatureInCelsiusToVout(100));
    result &= assert("temperatureInCelsiusToVout(110)", 1.01845f, temperatureInCelsiusToVout(110));
    result &= assert("temperatureInCelsiusToVout(120)", 1.0845f, temperatureInCelsiusToVout(120));
    result &= assert("temperatureInCelsiusToVout(130)", 1.14725f, temperatureInCelsiusToVout(130));
    result &= assert("temperatureInCelsiusToVout(140)", 1.2067f, temperatureInCelsiusToVout(140));
    result &= assert("temperatureInCelsiusToVout(150)", 1.26285f, temperatureInCelsiusToVout(150));
    result &= assert("temperatureInCelsiusToVout(160)", 1.3157f, temperatureInCelsiusToVout(160));
    result &= assert("temperatureInCelsiusToVout(170)", 1.36525f, temperatureInCelsiusToVout(170));
    result &= assert("temperatureInCelsiusToVout(180)", 1.4115f, temperatureInCelsiusToVout(180));
    result &= assert("temperatureInCelsiusToVout(190)", 1.45445f, temperatureInCelsiusToVout(190));
    result &= assert("temperatureInCelsiusToVout(200)", 1.4941f, temperatureInCelsiusToVout(200));

    if (result) {
        cout << "All tests passed\n";
        return 0;
    } else {
        cout << "Some tests failed\n";
        return 1;
    }
 
    // $ clang++ -o test_cpp -lc++ test_vdo_gauge_calc.cpp ../vdo_gauge_calc.cpp && ./test_cpp
}
 