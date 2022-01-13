#include "IRremote.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h"
const int receiver = 9; //Signal Pin of IR receiver to Arduino Pin 9
const int LedPin = 11; //output to pin 11
int LedState = LOW;
LiquidCrystal_I2C lcd(0x27,5,4); //initialize the library with the numbers of the interface pins
IRrecv irrecv(receiver);
decode_results results;
 
void setup(){
  lcd.init();
  lcd.backlight();
  Serial.begin(9600); //initialize the serial communications
  pinMode(LedPin, OUTPUT);
  Serial.println("IR Controls Online");
  lcd.setCursor(0,0);
  lcd.print("IR Online");
  irrecv.enableIRIn(); //Start the receiver
}

void loop(){
  if (irrecv.decode(&results)){ //have we received an IR signal?
    translateIR();
    irrecv.resume(); //receive the next value
  }
  if (Serial.available()){ //when characters arrive over the serial port
    delay(100); //wait a bit for the entire message to arrive
      lcd.clear(); //clear the screen
    while (Serial.available() > 0) { //read all the available characters
      lcd.write(Serial.read()); } //display each character to the LCD
  }
}

void translateIR(){ //takes action based on IR code received
 switch(results.value){
  case 0xE0E036C9: digitalWrite(LedPin, HIGH);
    Serial.println("A Button  Led ON"); break;
    lcd.print("A Button  Led ON"); break;
  case 0xE0E06897: digitalWrite(LedPin, LOW);
    Serial.println("D button Led OFF"); break;
    lcd.print("D Button Led OFF"); break;
  default:
    Serial.println(" Button not used"); 
  }
  delay(500); //Do not get immediate repeat
}
