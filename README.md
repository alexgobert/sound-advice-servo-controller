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