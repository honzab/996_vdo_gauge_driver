/*
VDO Vision oil temperature gauge driver (7/31/2014) by Ahsai
Tap the DME NTC oil temp sensor voltage reading of 2003 Porsche 996 (0 - 5V. High voltage = low temp)
Reads an analog input, converts it to voltage, then converts the voltage to voltage_out
using a function (based on Durametric reading, gauge calibration data and Excel spreadsheet trendline equation).
Write voltage_out to analog output pin D1, as a fraction of 5.0v, to drive the VDO gauage
*/

// the setup routine runs once when you press reset:
void setup() {}

// the loop routine runs over and over again forever:
void loop() {
// read the input on analog pin A3 and convert the analog reading (which goes from 0 - 1023) to voltage (0 - 5V):
float v = analogRead(A3) * (5.0 / 1023.0);
float vout = 2.0; // To ensure the needle stays below 120F when the temp is below 120F
//y = -0.3023x2 + 1.3098x + 0.294
if (v < 2.0) { vout = -0.3023*pow(v,2) + 1.3098*v + 0.294; }
// If using a non-Vision VDO oil temp gauge, comment out the previous line and uncomment the following line
//if (v < 2.0) { vout = -0.2352*pow(v,2) + 1.3098*v + 0.3117; }
//float vout = v; // Uncomment this line for calibration
// convert vout (0 - 5.0V) to output (0 - 255) and write to D1
analogWrite(1, (int)(255.0*vout/5.0));
delay(100);
} 
