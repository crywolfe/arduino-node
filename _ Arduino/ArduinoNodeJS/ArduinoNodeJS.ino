#include<LiquidCrystal.h>

// LCD pins
LiquidCrystal lcd(12,11,5,4,3,2);

// LED vars
const int ledPin = 13;
const int pwmPin = 10;

// LED read vars
String inputString = "";         // a string to hold incoming data
boolean toggleComplete = false;  // whether the string is complete
boolean pwmComplete = false;

// Potmeter vars
const int analogInPin = A0;
int sensorValue = 0;        // value read from the potmeter
int prevValue = 0;          // previous value from the potmeter

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // init LEDS
  pinMode(ledPin,OUTPUT);
  pinMode(pwmPin,OUTPUT);
  digitalWrite(ledPin,0);
  analogWrite(pwmPin,0);
  //set up LCD
  lcd.begin(16,2);
  //Print Message to LCD
  lcd.print("HELLO GA ATTENDEES!");
}

void loop() {
  //set LCD Cursor
  lcd.setCursor(0,1);
  //print number of seconds since reset
  lcd.print(millis()/1000);

   // Receive data from Node and write it to a String
   while (Serial.available() && toggleComplete == false && pwmComplete == false) {
    char inChar = (char)Serial.read();
    if(inChar == 'E'){ // end character for toggle LED
     toggleComplete = true;
    }
    if(inChar == 'P'){// end character for dim LED
      pwmComplete = true;
    }
    else{
      inputString += inChar;
    }
  }
  // Toggle LED 13
  if(!Serial.available() && toggleComplete == true)
  {
    // convert String to int.
    int receivedVal = stringToInt();

    if(receivedVal == 0)
    {
      digitalWrite(ledPin,receivedVal);
    }
    else if(receivedVal == 1)
    {
      digitalWrite(ledPin,receivedVal);
    }
    toggleComplete = false;
  }
  // Dim LED 3
  if(!Serial.available() && pwmComplete == true)
  {
    // convert String to int
    int receivedVal = stringToInt();
    analogWrite(pwmPin,receivedVal);
    pwmComplete = false;
  }
    // Potmeter
     sensorValue = analogRead(analogInPin);
    // read the analog in value:
    if(prevValue != sensorValue){
      Serial.print("B"); // begin character
      Serial.print(sensorValue);
      Serial.print("E"); // end character
      prevValue = sensorValue;
    }
  delay(50); // give the Arduino some breathing room.
}

int stringToInt()
{
    char charHolder[inputString.length()+1];
    inputString.toCharArray(charHolder,inputString.length()+1);
    inputString = "";
    int receivedVal = atoi(charHolder);
    return receivedVal;
}
