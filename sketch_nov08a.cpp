#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // Rx,Tx

#include <nmea.h>
NMEA nmeaDecoder(ALL);
int button=9

  void setup() {
	pinMode(button, INPUT); 
    Serial.begin(9600);
    Serial.println("Goodnight moon!");

    // set the data rate for the SoftwareSerial port
    mySerial.begin(9600);
  }

  void loop() {   
    if (mySerial.available()) { // if something is incoming through the Serial Port
      if (nmeaDecoder.decode(mySerial.read())) { // if it's a valid NMEA sentence   
        Serial.println(nmeaDecoder.sentence()); // print it 
		int state = digitalRead(button);
        //check if button is pressed and it is over 5 seconds since last button press
        if(state == HIGH && (millis() - changeTime)> 5000){
               //call the function to change the baudrate

        }
      } 
    }
  }

  void changeBPS(){

  }
