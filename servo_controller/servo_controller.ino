#include <ArduinoSTL.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <Servo.h>
#include <map>

const int numServos = 15;
int baudRate = 19200;

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
String notes[numServos] = {"G5","A6", "B6", "C6", "D6", "E6", "F6", "G6", "A7", "B7", "C7", "D7", "E7", "F7", "G7"};

// note to Servo
std::map<String, Servo> servoDict;

// note to LED pin
std::map<String, int> ledDict;

// Happy Birthday
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

// Jingle Bells
std::map<int, std::vector<String>> jingleBellBeats = {
{1, {"G6"}},
{2, {"E7"}},
// {3, {"D7"}},
// {4, {"C7"}},
// {5, {"G6"}},
// {9, {"G6"}},

// {10, {"E7"}},
// {11, {"D7"}},
// {12, {"C7"}},
// {13, {"A6"}},
// {17, {"A6"}},
// {18, {"F7"}},
// {19, {"E7"}},
// {20, {"D7"}},
// {21, {"B6"}},
// {25, {"G7"}},
// {26, {"G7"}},
// {27, {"F7"}},
// {28, {"D7"}},
// {29, {"E7"}},
// {33, {"G6"}},
// {34, {"E7"}},
// {35, {"D7"}},
// {36, {"C7"}},
// {37, {"G6"}},
// {41, {"G6"}},
// {42, {"E7"}},
// {43, {"D7"}},
// {44, {"C7"}},
{45, {"A6"}},
{49, {"A6"}},
{50, {"F7"}},
{51, {"E7"}},
{52, {"D7"}},
{53, {"G7"}},
{54, {"G7"}},
{55, {"G7"}},
{56, {"G7"}},
{57, {"A7"}},
{58, {"G7"}},
{59, {"F7"}},
{60, {"D7"}},
{61, {"C7"}},
{63, {"G7"}},
{65, {"E7"}},
{66, {"E7"}},
{67, {"E7"}},
{69, {"E7"}},
{70, {"E7"}},
{71, {"E7"}},
{73, {"E7"}},
{74, {"G7"}},
{75, {"C7"}},
{76, {"D7"}},
{77, {"E7"}},

// {81, {"F7"}},
// {82, {"F7"}},
// {83, {"F7"}},
// {84, {"F7"}},
// {85, {"F7"}},
// {86, {"E7"}},
// {87, {"E7"}},
// {88, {"E7"}},
// {89, {"E7"}},
// {90, {"D7"}},
// {91, {"D7"}},
// {92, {"E7"}},
// {93, {"D7"}},
// {95, {"G7"}},
// {97, {"E7"}},
// {98, {"E7"}},
// {99, {"E7"}},
// {101, {"E7"}},
// {102, {"E7"}},
// {103, {"E7"}},
// {105, {"E7"}},
// {106, {"G7"}},
{107, {"C7"}},
{108, {"D7"}},
{109, {"E7"}},
{113, {"F7"}},
{114, {"F7"}},
{115, {"F7"}},
{116, {"F7"}},
{117, {"F7"}},
{118, {"E7"}},
{119, {"E7"}},
{120, {"E7"}},
{121, {"G7"}},
{122, {"G7"}},
{123, {"F7"}},
{124, {"D7"}},
{125, {"C7"}},
};
int jingleBellsBPM = 160;
int jingleBellsNumBeats = 128;

std::map<int, std::vector<String>> tempBeats = {
    {1, {"G6", "G7"}},
    {2, {"G6"}},
    {3, {"G7"}},
    {5, {"G7"}}
};
int tempBPM = 180;
int tempNumBeats = 7;

// Arduino setup function
void setup() {
    Serial.begin(baudRate);
    
    for (int i = 0; i < numServos; i++) {
        Servo curServo = servos[i];
        int curLED = ledPins[i];
        String curNote = notes[i];
        
        curServo.attach(servoPins[i]);

        servoDict[notes[i]] = curServo;
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

        // case 2: // Jingle Bells
        //     bpm = jingleBellsBPM;
        //     numBeats = jingleBellsNumBeats;
        //     beats = jingleBellBeats;

        case 4: // temporary
            bpm = tempBPM;
            numBeats = tempNumBeats;
            beats = tempBeats;

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
    Serial.println("\t4) Temp Song");
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

            writeNotes(beats[i]);

            beatDelay -= servoDelay;
        }

        delay(beatDelay); // delay in milliseconds

        Serial.print("Beat: " + String(i) + "\t\t");
        Serial.println("Time Passed [s]: " + String(millis()-start));
    }
}

// plays a note
// @param notes is a vector of strings that represent the notes to play
void writeNotes(std::vector<String> notes) {
    moveServosAtNotes(notes, 0);
    delay(servoDelay);
    moveServosAtNotes(notes, 35);
}

// actuates servos at a note to a given angle
// @param notes is a vector of notes that need to be played
// @param angle is an int that represents a target angle for servos
void moveServosAtNotes(std::vector<String> notes, int angle) {
    for (String note: notes) {
        Servo servo = servoDict[note];
        int ledPin = ledDict[note];
        uint8_t curState = digitalRead(ledPin);

        servo.write(angle);
        digitalWrite(ledPin, ledStates[curState]);
    }
    Serial.print("Angle: " + String(angle) + "\t\t");
}
