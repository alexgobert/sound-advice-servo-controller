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
std::map<uint8_t, uint8_t> ledStates = {
    {HIGH, LOW},
    {LOW, HIGH}
};

// create servo object to control servos
Servo servos[numServos];
int servoDelay = 200;

// Notes on Glockenspiel as Strings, G5-G7
String notes[numServos] = {"G5","A6", "B6", "C6", "D6", "E6", "F6", "G6", "A7", "B7", "C7", "D7", "E7", "F7", "G7"};

// note to Servo
std::map<String, Servo> servoDict;

// note to LED pin
std::map<String, int> ledDict;

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
int happyBdayNumBeats = 54;

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
        int curLED = ledPins[i];
        String curNote = notes[i];
        
        curServo.attach(servoPins[i]);

        servoDict[curNote] = curServo;
        ledDict[curNote] = curLED;

        // define LED pins
        pinMode(curLED, OUTPUT);
    }

}

// Arduino loop function
// Can be used for user input (pick and play song)
void loop() {
    showOptions();

    // empty loop to halt for user input
    while (Serial.available() == 0) {} 
    
    int input = Serial.parseInt();
    
    int bpm;
    int numBeats;
    std::map<int, std::vector<String>> beats;

    // set song data based on user input
    switch (input) {
        case 1: // Happy Birthday
            bpm = happyBdayBPM;
            numBeats = happyBdayNumBeats;
            beats = happyBdayBeats;

        default: // Invalid selection
            Serial.println("Please make a valid selection");
    }

    playSong(bpm, numBeats, beats);

    delay(1000);
}

void showOptions() {
    Serial.println("Please pick a song from the following list of songs: ");
    Serial.println();
    Serial.println("\t1) Happy Birthday");
    Serial.println("\t2) Song 2");
    Serial.println("\t3) Song 3");
    Serial.println();
}

// Plays a song given data about it
// @param bpm is the beats per minute of song
// @param numBeats is the number of beats in song
// @param beats is (int -> vector<String>) map that contains the notes for every beat
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
// @param notes is a vector of strings that represent the notes to play
void writeNote(std::vector<String> notes) {
    moveServosAtNote(notes, 0);
    delay(servoDelay);
    moveServosAtNote(notes, 35);
}

// actuates servos at a note to a given angle
// @param notes is a vector of notes that need to be played
// @param angle is an int that represents a target angle for servos
void moveServosAtNote(std::vector<String> notes, int angle) {
    for (String note: notes) {
        Servo servo = servoDict[note];
        int ledPin = ledDict[note];
        uint8_t curState = digitalRead(ledPin);

        servo.write(angle);
        digitalWrite(ledPin, ledStates[curState]);
    }
}