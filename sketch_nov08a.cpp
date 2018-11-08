#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // Rx,Tx

#include <nmea.h>
NMEA nmeaDecoder(ALL);

const int button = 9;
int buttonState = 0;

const int bps1 = 4800;
const int bps2 = 9600;
const int bps3 = 19200;
const int bps4 = 38400;
const int bps5 = 57600;

int counter = 1;

void setup() {
    pinMode(button, INPUT); 
    Serial.begin(9600);
    Serial.println("Goodnight moon!");

    // set the data rate for the SoftwareSerial port
    mySerial.begin(4800);
}

void loop() {   
    if (mySerial.available()) { //if something is incoming through the Serial Port
        if (nmeaDecoder.decode(mySerial.read())) { //if it's a valid NMEA sentence   
            Serial.println(nmeaDecoder.sentence()); // print it 
            buttonState = digitalRead(button); //check if button is pressed and it is over 5 seconds since last button press
            if(buttonState == HIGH){//call the function to change the baudrate
                changeBPS();
            }
        }else{
            Serial.println("Error: Message could not be decoded");
        } 
    }else{
        Serial.println("No connection");
    }
}

void changeBPS(){
    switch(counter % 5){
        case(0):
            mySerial.begin(bps1);
            Serial.println("Data rate changed: 4800bps");
        case(1): 
            mySerial.begin(bps2);
            Serial.println("Data rate changed: 9600bps");
        case(2): 
            mySerial.begin(bps3);
            Serial.println("Data rate changed: 19200bps");
        case(3): 
            mySerial.begin(bps4);
            Serial.println("Data rate changed: 38400bps");
        case(4): 
            mySerial.begin(bps5);
            Serial.println("Data rate changed: 57600bps");
    }

    counter++;

    if (counter > 100){
        counter = 1
    }
}
