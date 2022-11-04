#include <ArduinoSTL.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <Servo.h>
#include <map>

const int numServos = 15;
const int baudRate = 31250;

// create servo object to control servos
Servo servos[numServos];
int pins[numServos]; // TODO make constant

// notes
String notes[numServos]; // TODO make constant

// TODO
// note to Servo
std::map<String, Servo> servo_dict = {
    {"Hello", Servo()},
    {"World", Servo()}
};

void setup() {
    Serial.begin(baudRate);
    
    // attach Servos to pins and add Servo to dictionary
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(pins[i]);

        // TODO add Servo to dict
    }

    // read file
}

void loop() {
    int dummy = 0;
}

void playSong(int bpm, int numBeats, std::map<int, std::vector<String>> beats) {
    double beatDuration = 60.0 / bpm; // seconds

    for (int i = 0; i < numBeats; i++) {
        std::vector<String> beatNotes = beats[i];

        for (int n = 0; n < beatNotes.size(); n++) {
            writeNote(servo_dict[beatNotes[n]]);
        }

        delay(beatDuration * 1000); // delay in milliseconds
    }
}

void writeNote(Servo servo) {
    servo.write(0);
    delay(200);
    servo.write(35);
}