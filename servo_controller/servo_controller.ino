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
int servoDelay = 200;
int angle1 = 0;
int angle2 = 35;

// Notes on Glockenspiel as Strings, G5-G7
const char* notes[numServos] = {"G5","A6", "B6", "C6", "D6", "E6", "F6", "G6", "A7", "B7", "C7", "D7", "E7", "F7", "G7"};

// note to Servo
std::map<const char*, Servo> servoDict;

// note to LED pin
std::map<const char*, int> ledDict;

// Happy Birthday
const int happyBdayBPM = 180;
// const int happyBdayNumBeats = 49;
std::vector<const char*> happyBdayBeats[] = {
    {},
    {},
    {},
    {},
    {"G6"},
    {"G6"},
    {"A6"},
    {},
    {"G6"},
    {},
    {"C7"},
    {},
    {"B6"},
    {},
    {},
    {},
    {"G6"},
    {"G6"},
    {"A6"},
    {},
    {"G6"},
    {},
    {"D7"},
    {},
    {"C6"},
    {},
    {},
    {},
    {"G6"},
    {"G6"},
    {"G7"},
    {},
    {"E7"},
    {},
    {"C7"},
    {},
    {"B6"},
    {},
    {"A6"},
    {},
    {"F7"},
    {"F7"},
    {"E7"},
    {},
    {"C7"},
    {},
    {"D7"},
    {},
    {"C7"},
};

// Jingle Bells
const int jingleBellsBPM = 160;
std::vector<const char*> jingleBellBeats[] = {
    {"G6"},
    {"E7"},
    {"D7"},
    {"C7"},
    {"G6"},
    {},
    {},
    {},
    {"G6"},
    {"E7"},
    {"D7"},
    {"C7"},
    {"A6"},
    {},
    {},
    {},
    {"A6"},
    {"F7"},
    {"E7"},
    {"D7"},
    {"B6"},
    {},
    {},
    {},
    {"G7"},
    {"G7"},
    {"F7"},
    {"D7"},
    {"E7"},
    {},
    {},
    {},
    {"G6"},
    {"E7"},
    {"D7"},
    {"C7"},
    {"G6"},
    {},
    {},
    {},
    {"G6"},
    {"E7"},
    {"D7"},
    {"C7"},
    {"A6"},
    {},
    {},
    {},
    {"A6"},
    {"F7"},
    {"E7"},
    {"D7"},
    {"G7"},
    {"G7"},
    {"G7"},
    {"G7"},
    {"A7"},
    {"G7"},
    {"F7"},
    {"D7"},
    {"C7"},
    {},
    {"G7"},
    {},
    {"E7"},
    {"E7"},
    {"E7"},
    {},
    {"E7"},
    {"E7"},
    {"E7"},
    {},
    {"E7"},
    {"G7"},
    {"C7"},
    {"D7"},
    {"E7"},
    {},
    {},
    {},
    {"F7"},
    {"F7"},
    {"F7"},
    {"F7"},
    {"F7"},
    {"E7"},
    {"E7"},
    {"E7"},
    {"E7"},
    {"D7"},
    {"D7"},
    {"E7"},
    {"D7"},
    {},
    {"G7"},
    {},
    {"E7"},
    {"E7"},
    {"E7"},
    {},
    {"E7"},
    {"E7"},
    {"E7"},
    {},
    {"E7"},
    {"G7"},
    {"C7"},
    {"D7"},
    {"E7"},
    {},
    {},
    {},
    {"F7"},
    {"F7"},
    {"F7"},
    {"F7"},
    {"F7"},
    {"E7"},
    {"E7"},
    {"E7"},
    {"G7"},
    {"G7"},
    {"F7"},
    {"D7"},
    {"C7"},
};

// Song 3 (jingle bells placeholder to test memory limitations)
const int song3BPM = 160;
std::vector<const char*> song3Beats[] = {
    {"E7"},
    {"D7"},
    {"G7"},
    {"G7"},
    {"G7"},
    {"G7"},
    {"A7"},
    {"G7"},
    {"F7"},
    {"D7"},
    {"C7"},
    {},
    {"G7"},
    {},
    {"E7"},
    {"E7"},
    {"E7"},
    {},
    {"E7"},
    {"E7"},
    {"E7"},
    {},
    {"E7"},
    {"G7"},
    {"G7"},
    {"C7"},
    {"D7"},
    {"E7"},
    {},
    {},
    {},
    {"F7"},
    {"F7"},
    {"F7"},
    {"F7"},
    {"F7"},
    {"E7"},
    {"E7"},
    {"E7"},
    {"G7"},
    {"G7"},
    {"F7"},
    {"D7"},
    {"C7"},
};

// Arduino setup function
void setup() {
    Serial.begin(19200);
    
    for (int i = 0; i < numServos; i++) {
        servos[i].attach(servoPins[i]);

        servoDict[notes[i]] = servos[i];
        ledDict[notes[i]] = ledPins[i];

        // define LED pins
        pinMode(ledPins[i], OUTPUT);
    }

}

// Arduino loop function
// Can be used for user input (pick and play song)
void loop() {
    showOptions();

    // empty loop to halt for user input
    while (Serial.available() == 0) {
        delay(1000);
    } 
    
    // set song data based on user input
    switch (Serial.parseInt()) {
        case 0:
            break;
        case 1: // Happy Birthday
            playSong(happyBdayBPM, *(&happyBdayBeats + 1) - happyBdayBeats, happyBdayBeats);
            break;
        case 2: // Jingle Bells
            playSong(jingleBellsBPM, *(&jingleBellBeats + 1) - jingleBellBeats ,jingleBellBeats);
            break;
        case 3: // Song 3
            playSong(song3BPM, *(&song3Beats+ 1) - song3Beats, song3Beats);
        default: // Invalid selection
            Serial.println(F("Please make a valid selection"));
    }    

    delay(1000);
}

void showOptions() {
    Serial.println(F("Please pick a song from the following list of songs: "));
    Serial.println();
    Serial.println(F("\t1) Happy Birthday"));
    Serial.println(F("\t2) Song 2"));
    Serial.println(F("\t3) Song 3"));
    Serial.println(F("\t4) Temp Song"));
    Serial.println();
}

// Plays a song given data about it
// @param bpm is the beats per minute of song
// @param numBeats is the number of beats in song
// @param beats is (int -> vector<String>) map that contains the notes for every beat
void playSong(int bpm, int numBeats, std::vector<const char*> *beats) {
    double beatDuration = 60.0 / bpm; // seconds

    for (int i = 1; i <= numBeats; i++) {
        unsigned long start = millis();

        int beatDelay = beatDuration * 1000;
        
        if (!beats[i].empty()) {

            writeNotes(beats[i]);

            beatDelay -= servoDelay;
        }

        delay(beatDelay); // delay in milliseconds

        Serial.print(F("Beat: "));
        Serial.print(i);
        Serial.print(F("\t\t"));

        Serial.print(F("Time Passed [s]: "));
        Serial.println(millis() - start);
    }
}

// plays a note
// @param notes is a vector of strings that represent the notes to play
void writeNotes(std::vector<const char*>& notes) {
    moveServosAtNotes(notes, angle1);
    delay(servoDelay);
    moveServosAtNotes(notes, angle2);
}

// actuates servos at a note to a given angle
// @param notes is a vector of notes that need to be played
// @param angle is an int that represents a target angle for servos
void moveServosAtNotes(std::vector<const char*>& notes, int angle) {
    for (const char* note: notes) {
        uint8_t curState = digitalRead(ledDict[note]);

        servoDict[note].write(angle);
        digitalWrite(ledDict[note], ledStates[curState]);
    }
    Serial.print(F("Angle: "));
    Serial.print(angle);
    Serial.print(F("\t\t"));
}
