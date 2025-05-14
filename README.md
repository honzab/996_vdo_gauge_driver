# Building an oil temperature gauge for Porsche 996

## Introduction

This project is about building an oil temperature gauge for a Porsche 996/996.

The car does not have a temperature gauge from the factory and neither does it expose the information on 
the CAN bus so that it can be read by an OBD-II reader.

People have developed different kind of solutions for this problem, but there was one that especially
caught my eye, both because of the design but also reversibility and accuracy of the solution.

## Ahsai's design from 2014

Back in 2014, [Ahsai](https://rennlist.com/forums/members/32590-ahsai.html)
[published a design for a temperature gauge that uses the factory oil level/temperature sensor](https://rennlist.com/forums/996-forum/827720-oil-temp-gauge-using-the-built-in-oil-temp-sensor.html) by
tapping the sensor wire directy on its way to the ECU. This way, the factory ECU is still able to read the oil pressure,
but we can through the tap see it as well.

When you have access to the voltage from the sensor, you can choose to display it in any way you'd like. Back then
Ahsai chose to use the VDO gauge, which fits the design of the interior pretty well.

## Trying to build it in 2025

In April 2025 I decided to try to build it as well.

I looked at the original schematics, but some of the components have already been replaced by newer ones. This meant 
that I would need to redo the schematics, look at all the datasheets and find replacement components.

[Ahsai's Original Schematics](ExpressSCH-page-0.jpg)

The circuit itself is fairly simple and smart. It uses an ATTiny85 to convert the voltage from the sensor to a voltage
that drives the VDO gauge.

What we can use from the original design is the values for the sensor signal, or at least the polynomial that 
was used to approximate the conversion values.

### Getting to what value is what

In the original design, Ahsai used Durametric software to get the temperature values (in F) and mapped them to the
voltage observed on the sensor wire.

> [!NOTE]
> I would like to maybe borrow someone's Durametric and check myself. But as of now (May 2025), I trust this data.

[Ahsai's original values](Drawing1.jpg), with the polynomial approximated (in F):

```
y = 8.5645 * x^4 - 59.284 * x^3 + 160.76 * x^2 - 245.49x + 299.24
R^2 = 0.9997
```

We can then use this information to build the table of values in Celsius, using a simple [python script](engine_sensor_voltage_temperature.py).

![plot](engine_sensor_voltage_temperature.png)

| voltage   | °C       | F       |
|-----------|----------|---------|
| 2.90V     | 37.32°C  | 99.18F  |
| 2.80V     | 36.25°C  | 97.25F  |
| 2.70V     | 35.90°C  | 96.62F  |
| 2.60V     | 36.17°C  | 97.11F  |
| 2.50V     | 36.95°C  | 98.50F  |
| 2.40V     | 38.14°C  | 100.65F |
| 2.30V     | 39.66°C  | 103.39F |
| 2.20V     | 41.45°C  | 106.61F |
| 2.10V     | 43.44°C  | 110.20F |
| 2.00V     | 45.59°C  | 114.06F |
| 1.90V     | 47.85°C  | 118.14F |
| 1.80V     | 50.21°C  | 122.38F |
| 1.70V     | 52.65°C  | 126.77F |
| 1.60V     | 55.17°C  | 131.30F |
| 1.50V     | 57.77°C  | 135.99F |
| 1.40V     | 60.48°C  | 140.87F |
| 1.30V     | 63.33°C  | 146.00F |
| 1.20V     | 66.37°C  | 151.46F |
| 1.10V     | 69.64°C  | 157.35F |
| 1.00V     | 73.22°C  | 163.79F |
| 0.90V     | 77.18°C  | 170.92F |
| 0.80V     | 81.61°C  | 178.89F |
| 0.70V     | 86.61°C  | 187.89F |
| 0.60V     | 92.29°C  | 198.12F |
| 0.50V     | 98.78°C  | 209.81F |
| 0.40V     | 106.22°C | 223.19F |
| 0.30V     | 114.74°C | 238.53F |
| 0.20V     | 124.51°C | 256.11F |
| 0.10V     | 135.69°C | 276.24F |
| 0.00V     | 148.47°C | 299.24F |

The next thing we will need is to figure out what is the needed voltage to drive the VDO gauge.

The VDO gauge is driven by 12V, with the signal ranging from 0V to 5V. The temperature range is from 50°C to 150°C,
where it seems like 0V corresponds to the maximum (over 150°C) and the minimum is around 2.5V.

### What's needed

TODO: add list of components

### Prepping Arduino IDE

Add this to Preferences / Additional Boards Manager URLs:

```
https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json
```

Then Choose:

* Tools > Board > attiny > ATtiny25/45/85
* Tools > Clock > 8 MHz (internal)
* Tools > Processor > ATtiny85
* Tools > Programmer > USBtinyISP

Then do `Tools > Burn Bootloader`.

### Uploading your code

Write your code, compile with `Sketch > Verify/Compile` and upload with `Sketch > Upload`.
