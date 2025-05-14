int COUNTER = 0;

void setup() {}

void loop() {
    // read the input on analog pin A3 and convert the analog reading (which goes from 0 - 1023) to voltage (0 - 5V):
    float v = analogRead(A3) * (5.0 / 1023.0);

    // float vout = 2.0; // To ensure the needle stays below 120F when the temp is below 120F

    float vout = (float)(COUNTER % 5);

    analogWrite(1, (int)( 255.0 * vout / 5.0));

    // Wait 5 seconds before the next reading
    delay(5000);
} 
