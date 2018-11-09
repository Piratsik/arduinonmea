#include <SoftwareSerial.h>
SoftwareSerial mySerial(10,11); // Rx,Tx

#include <nmea.h>
NMEA nmeaDecoder(ALL);

const int button = 9;
int buttonState = 0;
int lastButtonState = 0;

const long bps0 = 1200;
const long bps1  = 2400;
const long bps2= 4800;
const long bps3 = 9600;
const long bps4 = 19200;
const long bps5 = 38400;
const long bps6 = 57600;
const long bps7= 115200;


int counter = 1;
unsigned long changeTime = 0;
unsigned long connectionError = 0;
unsigned long messageError = 0;

void setup() {
    pinMode(button, INPUT); 
    Serial.begin(9600);

    // set the data rate for the SoftwareSerial port
    mySerial.begin(4800);
}

void loop() {

    if(Serial.available() > 0){
        long input = Serial.parseInt();
        delay (1000);
        if (input==-1){
          scanBPS();
        }
        changeBPS(input);
    }

    buttonState = digitalRead(button); //check if button is pressed and it is over 5 seconds since last button press
    if (buttonState != lastButtonState) {
        if((buttonState == HIGH) && (millis() - changeTime) > 2000){//call the function to change the baudrate
            changeBPS();

            counter++;

            if (counter > 100){
                counter = 1;
            }
        }
    }
    lastButtonState = buttonState;

    if (mySerial.available()) { //if something is incoming through the Serial Port
        if (nmeaDecoder.decode(mySerial.read())) { //if it's a valid NMEA sentence   
            Serial.println(nmeaDecoder.sentence()); // print it 
        }else{
            if (millis() - messageError > 10000){
                Serial.println("Error: Message could not be decoded");
                messageError = millis();
            }
        } 
    }else{
        if (millis() - connectionError > 15000){
            Serial.println("No connection");
            connectionError = millis();
        }
    }


}

void changeBPS(){
  if (counter % 5==0){
    mySerial.begin(bps2);
    Serial.println("Data rate changed: 4800bps");
  }else if (counter % 5==1){
    mySerial.begin(bps3);
  Serial.println("Data rate changed: 9600bps");
  }else if (counter%5==2){
    mySerial.begin(bps4);
            Serial.println("Data rate changed: 19200bps");
  }else if (counter%5==3){
    mySerial.begin(bps5);
            Serial.println("Data rate changed: 38400bps");
  }else {
    mySerial.begin(bps6);
            Serial.println("Data rate changed: 57600bps");
    }

    changeTime = millis();
}

void changeBPS(long value){
  if (value>0){
    mySerial.begin(value);
    Serial.println ("Data rate changed: ");
    Serial.println (value);
  }
}
void scanBPS(){
  unsigned long tiktak=0;
  unsigned long start=millis();
  int konter=0;
  
    while (!nmeaDecoder.decode(mySerial.read()) && tiktak<30000){
   if (mySerial.available()) { //if something is incoming through the Serial Port
      Serial.println(mySerial.read());
      delay(3000);
        if (nmeaDecoder.decode(mySerial.read())) { //if it's a valid NMEA sentence   
            Serial.println("Opoiodipote Minima"); // print it 
        }
   }
      if (konter % 8==0){
        mySerial.begin(bps0);
        Serial.println("Data rate changed: 1200bps");
      }else if (konter%8==1){
        mySerial.begin(bps1);
        Serial.println("Data rate changed: 2400bps");
      }else if (konter%8==2){
        mySerial.begin(bps2);
          Serial.println("Data rate changed: 4800bps");
        }else if (konter % 8==3){
          mySerial.begin(bps3);
        Serial.println("Data rate changed: 9600bps");
        }else if (konter%8==4){
          mySerial.begin(bps4);
                  Serial.println("Data rate changed: 19200bps");
        }else if (konter%8==5){
          mySerial.begin(bps5);
                  Serial.println("Data rate changed: 38400bps");
        }else if(konter%8==6){
          mySerial.begin(bps6);
                  Serial.println("Data rate changed: 57600bps");
        }else{
        mySerial.begin(bps7);
                  Serial.println("Data rate changed: 115200bps");
        }
        konter++;
        if (konter>100) {
          konter=1;
        }
        tiktak=millis()-start;
    }
    
  }

