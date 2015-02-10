/*
 	
 The circuit:
 * TBD...
 *
 * author: Eyal Pinkas pinkasey@gmail.com
 * author: Yonatan Broza
 */

// this constant won't change:
const int buttonPin1 = 5;    // the pin that the pushbutton is attached to
const int buttonPin2 = 6;    // the pin that the pushbutton is attached to
const int ledPin1 = 1;       // the pin that the LED is attached to
const int ledPin2 = 2;       // the pin that the LED is attached to
const int ledPinMain = 13;    // the pin that the LED is attached to
const unsigned int tonePin = 9;
const unsigned int middleCNote = 261;
const unsigned int errorToneHigh = middleCNote;
const unsigned int errorToneLow = middleCNote * 2;

// Variables will change:
//int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;         // current state of the button

boolean hasWinner;
int waitForTheLight;

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  // initialize the LED as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPinMain, OUTPUT);

//  // initialize serial communication:
//  Serial.begin(9600);
}


void loop() {
  doStartSequence();
  boolean noOneCheated = lightAfterRandom();
  if ( noOneCheated ) {
    listenForWinner();
  }
  delay(1000);
}


void doStartSequence(){
  digitalWrite(ledPinMain, LOW);  
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  
  digitalWrite(ledPinMain, HIGH);
  delay (250);
  digitalWrite(ledPinMain, LOW);
  delay (250);
  digitalWrite(ledPinMain, HIGH);
  delay (250);
  digitalWrite(ledPinMain, LOW);
  delay (250);
  digitalWrite(ledPinMain, HIGH);
  delay (250);
  digitalWrite(ledPinMain, LOW);
} 

boolean lightAfterRandom(){
  long waitMillis = random(2000, 9000);
  long endTime = millis() + waitMillis;
  long currTime;
  do{
    buttonState1 = digitalRead(buttonPin1);
    if ( buttonState1 == LOW ){
      doFaulSequence(ledPin1);
      return false;
    }
    buttonState2 = digitalRead(buttonPin2);
    if ( buttonState2 == LOW ){
      doFaulSequence(ledPin2);
      return false;
    }
    currTime = millis();
  } while( currTime < endTime );
  
  digitalWrite(ledPinMain, HIGH);
  tone(tonePin, middleCNote); 
  return true;
}

void doFaulSequence( int ledPin){
  for(int i=0; i<4; i++){
    digitalWrite(ledPin,HIGH);
    tone(tonePin, errorToneHigh);
    delay(150);
    digitalWrite(ledPin,LOW);
    digitalWrite(ledPinMain,HIGH);
    tone(tonePin, errorToneLow);
    delay(150);
    digitalWrite(ledPinMain,LOW);
  }
  noTone(tonePin);
}

void listenForWinner(){
  
  long endTime = millis() + 5000;
  long currTime;
  hasWinner = false;
  do{
    buttonState1 = digitalRead(buttonPin1);
    buttonState2 = digitalRead(buttonPin2);
    if ( buttonState1 == LOW ){
      hasWinner = true;
      digitalWrite(ledPin1,HIGH);
    }
    if ( buttonState2 == LOW ){
      hasWinner = true;
      digitalWrite(ledPin2,HIGH);
    }
    currTime = millis();
  } while( !hasWinner && currTime < endTime);

  digitalWrite(ledPinMain,LOW);
  noTone(tonePin);
}


