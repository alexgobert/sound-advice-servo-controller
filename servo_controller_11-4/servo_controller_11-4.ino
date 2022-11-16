#include <ArduinoSTL.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <Servo.h>
#include <map>

const int numServos = 15;
int baudRate = 9600;

// pin constants
int servoPins[numServos] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};
int ledPins[numServos] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51};

// create servo object to control servos
Servo servos[numServos];
int servoDelay = 200;

// Notes on Glockenspiel as Strings, G5-G7
String notes[numServos] = {"G5","A6", "B6", "C6", "D6", "E6", "F6", "G6", "A7", "B7", "C7", "D7", "E7", "F7", "G7"};

// note to Servo
std::map<String, Servo> servo_dict;

// songs
std::map<int, std::vector<String>> happyBdayBeats = {
    {5, {"G6"}},
    {6, {"G6"}},
    {7, {"A6"}},
    {9, {"G6"}},
    {11, {"C7"}},
    {13, {"B6"}},
    {17, {"G6"}},
    {18, {"G6"}},
    {19, {"A6"}},
    {21, {"G6"}},
    {23, {"D7"}},
    {25, {"C6"}},
    {29, {"G6"}},
    {30, {"G6"}},
    {31, {"G7"}},
    {33, {"E7"}},
    {35, {"C7"}},
    {37, {"B6"}},
    {39, {"A6"}},
    {41, {"F7"}},
    {42, {"F7"}},
    {43, {"E7"}},
    {45, {"C7"}},
    {47, {"D7"}},
    {49, {"C7"}},
};
int happyBdayBPM = 180;
int happyBdayNumBeats = 3;

std::map<int, std::vector<String>> tempBeats = {
    {1, {"G6"}},
    {2, {"G6"}},
    {3, {"G7"}},
};

// Arduino setup function
void setup() {
    Serial.begin(baudRate);

    for (int i = 0; i < numServos; i++) {
        Servo curServo = servos[i];

        curServo.attach(servoPins[i]);

        servo_dict[notes[i]] = curServo;

        // define LED pins
        pinMode(i, OUTPUT);
    }

}

// Arduino loop function
// Can be used for user input (pick and play song)
void loop() {
    Serial.println("NEW ITERATION");
    Serial.println();
    playSong(happyBdayBPM, happyBdayNumBeats, tempBeats);
}

// Plays a song given data about it
void playSong(int bpm, int numBeats, std::map<int, std::vector<String>> beats) {
    double beatDuration = 60.0 / bpm; // seconds

    for (int i = 1; i <= numBeats; i++) {
        unsigned long start = millis();

        int beatDelay = beatDuration * 1000;

        if (beats.count(i)) {

            writeNote(beats[i]);

            beatDelay -= servoDelay;
        }

        delay(beatDelay); // delay in milliseconds

        Serial.print("Beat: " + String(i) + "\t\t");
        Serial.println("Time Passed [s]: " + String(millis()-start));
    }
}

// plays a note
// @param 
void writeNote(std::vector<String> notes) {
    moveServosAtNote(notes, 0);
    delay(servoDelay);
    moveServosAtNote(notes, 35);
}

void moveServosAtNote(std::vector<String> notes, int angle) {
    // int ledPin; // TODO
    // digitalWrite(ledPin, HIGH);

    for (String note: notes) {
        servo_dict[note].write(angle);
    }
}
