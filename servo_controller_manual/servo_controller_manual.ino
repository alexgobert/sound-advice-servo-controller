#include <ArduinoSTL.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <Servo.h>
#include <map>

const int numServos = 15;

// pin constants
int servoPins[numServos] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};
int ledPins[numServos] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};
std::map<uint8_t, uint8_t> ledStates = {
    {HIGH, LOW},
    {LOW, HIGH}
};

// create servo object to control servos
Servo servos[numServos];
const int servoDelay = 40; // milliseconds
const int angle1 = 15;
const int angle2 = 50;

// Notes on Glockenspiel as Strings, G5-G7
const String notes[numServos] = {"G5", "A5", "B5", "C6", "D6", "E6", "F6", "G6", "A6", "B6", "C7", "D7", "E7", "F7", "G7"};

// note to Servo
std::map<String, Servo> servoDict;

// note to LED pin
std::map<String, int> ledDict;

// Arduino setup function
void setup() {
    Serial.begin(19200);
    
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(servoPins[i]);

        servoDict[notes[i]] = servos[i];
        ledDict[notes[i]] = ledPins[i];

        servos[i].write(angle2);

        // define LED pins
        pinMode(ledPins[i], OUTPUT);
    }

}

// Arduino loop function
// Can be used for user input (pick and play song)
void loop() {

    // empty loop to halt for user input
    while (Serial.available() == 0) {
        delay(1000);
    } 
    
    // set song data based on user input
    String input = Serial.readStringUntil('\n').c_str();

    playSong(input);
}

// Plays a song given data about it
void playSong(String note) {
    unsigned long start = millis();
    
    writeNotes(note);

    Serial.print(F("Note: "));
    Serial.print(note);
    Serial.print(F("\t\t"));

    Serial.print(F("Time Passed [s]: "));
    Serial.println(millis() - start);
}

// plays a note
// @param note is a String containing the note to play
void writeNotes(String note) {
    moveServosAtNotes(note, angle1);
    delay(servoDelay);
    moveServosAtNotes(note, angle2);
}

// actuates servos at a note to a given angle
// @param note is a String containing the note to play
// @param angle is an int that represents a target angle for servos
void moveServosAtNotes(String note, int angle) {
    uint8_t curState = digitalRead(ledDict[note]);

    servoDict[note].write(angle);
    digitalWrite(ledDict[note], ledStates[curState]);

    Serial.print(F("Angle: "));
    Serial.print(angle);
    Serial.print(F("\t\t"));
}
