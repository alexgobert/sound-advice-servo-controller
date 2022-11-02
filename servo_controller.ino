#include <Servo.h>

// create servo object to control servos
const int numServos = 1;
Servo servos[numServos];
int positions[numServos];
// int pins[numServos] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
int pins[numServos] = {44};

void setup() {
    Serial.begin(31250);
    
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(pins[i]);
    }
}

void loop() {

    // for (int i = 0; i < numServos; i++) {
    //     writeNote(servos[i]);
    // }

    writeAll(0);
    delay(200);

    writeAll(35);
    delay(1000);
}

void writeAll(int pos) {
    for (int i = 0; i < numServos; i++) {
        servos[i].write(pos);
    }
}

// void writeNote(Servo servo) {
//     servo.write(0);
//     delay(200);
//     servo.write(35);
// }