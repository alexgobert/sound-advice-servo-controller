# Sound Advice Servo Controller  

Collaborative project in Dr. Carolyn Seepersad's Fall 2022 semester of M E 366J at the University of Texas at Austin. This repo contains the source code for automating a 15-key glockenspiel on an Arduino Mega (or equivalent).

Team members:  

- Michael Borja  
- Austin Case  
- Alex Gobert  
- Justin Oca  
- Jason Shim  
- Andres Vieira  

## How It Works  

There are three hardcoded songs embedded in `servo_controller.ino`: Happy Birthday, Jingle Bells, and Payphone. Uploading `servo_controller.ino` to an Arduino Mega takes user input (on a loop) corresponding to one of the three songs. The sketch then plays the given song on its glockenspiel, assuming that the wiring is done properly and the servo/mallet configuration is properly aligned.  

## Dependencies  

- ArduinoSTL  
- Servo  

## Potential Improvements  

### 1. Use Python

Rely on Python as a computational driver and use an Arduino sketch as a listener to Python via the [Serial](https://pypi.org/project/serial/) module. We ran into RAM overload issues by storing the songs as array literals, so offloading the space complexity of the songs to an external control terminal would've been helpful. Implementing Python would also allow for more complex, polished UI implementations, like a GUI. Use of a GUI would allow easy, intuitive usage for users with no prior programming experience.

### 2. Use the [SD Arduino Library](https://www.arduino.cc/reference/en/libraries/sd/)  

Another way of combatting the aforementioned memory limitations would be to store the songs in an SD card and use Arduino's SD library to read the songs on demand. This would cause the Arduino to store one song to RAM at a time, rather than all of them. This allows for an arbitrary number of playable songs, granted any single song does not exceed the Arduino's RAM limitations.  
