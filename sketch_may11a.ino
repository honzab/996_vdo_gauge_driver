int COUNTER = 0;

const float temps[]= {
1.91,
1.99,
2,
2.028,
2.05,
2.079,
2.1,
2.13,
2.165,
2.185,
2.21,
};

const float volts[]= {
0.54, //50
0.76, //80
0.85, //90
0.93, //100
0.99, //110
1.04, //120
1.10, //130
1.20, //140
};


void setup() {
    // pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);

    /*analogWrite(1, (int)( 255.0 * temps[0] / 5.0));
    delay(400);
    analogWrite(1, (int)( 255.0 * temps[10] / 5.0));
    delay(10000);
    analogWrite(1, (int)( 255.0 * temps[0] / 5.0));*/
}


void loop() {
    // read the input on analog pin A3 and convert the analog reading (which goes from 0 - 1023) to voltage (0 - 5V):
    float v = analogRead(A3) * (5.0 / 1023.0);

    // float vout = 2.0; // To ensure the needle stays below 120F when the temp is below 120F
    // float vout = v;
    // float vout = (float)(COUNTER % 5);

    float vout = (float)volts[COUNTER % 8];

    COUNTER = (COUNTER + 1) % 255;

    /*int volts = 0;
    int i;
    for (i = 0; i < 20; i++) {
        analogWrite(1, (int)(255.0 * volts / 5.0));
        volts += 0.1;
        delay(5000);
    }*/

    // digitalWrite(0, HIGH);

    analogWrite(1, (int)( 255.0 * vout / 5.0));

    // Wait 5 seconds before the next reading
    // delay(5000);
    // digitalWrite(0, LOW);
    delay(4000);
} 
