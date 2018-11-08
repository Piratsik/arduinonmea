int relayPin = 3;                           // relay pin -- Digital 3
int relayState=HIGH;


void setup() {
          
  Serial.begin(9600);
  pinMode(relayPin, OUTPUT);// put your setup code here, to run once:
digitalWrite(relayPin, relayState); 
}

void loop() {
   int val;               
    double data;          
    val=analogRead(0);  
    data = (double) val * (5/10.24); // convert the voltage to temperture
    
    if(data>60){
     relayState = !relayState;}

      

 digitalWrite(relayPin, relayState); 
}


