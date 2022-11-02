#include <Servo.h>
#include <map>

// create servo object to control servos
const int numServos = 1;
Servo servos[numServos];
int positions[numServos];
int pins[numServos] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

// note to Servo

std::map<string, Servo> servo_dict = {
    {}
};

void setup() {
    Serial.begin(31250);
    
    // attach Servos to pins
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(pins[i]);
    }

    // create servo dict
    for (int i = 0; i < numServos; i++) {

    }

    // read file
}

void loop() {
    int dummy = 0;
}

void playSong(int bpm, int numBeats, std::map<int, std::vector> beats) {
    double beatDuration = 60 * 1.0 / bpm; // seconds

    for (int i = 0; i < numBeats; i++) {
        notes = beats[i];

        for (int n = 0; n < notes.length; n++) {
            writeNote(servo_dict[notes[n]]);
        }

        delay(beatDuration * 1000) // delay in milliseconds
    }
}

void writeNote(Servo servo) {
    servo.write(0);
    delay(200);
    servo.write(35);
}