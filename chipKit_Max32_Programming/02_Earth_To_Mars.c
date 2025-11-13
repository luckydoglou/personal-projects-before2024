//==========================
// Earth to Mars
// Name: Xiaolou Huang (Lor)
// Summer 2018
//==========================
//
// System Inputs:
// 1.	SW1: Launch Switch (L), L=1 will activate Rocket Ignition (R = 1)
// 2.	SW2: Rocket Fuel Sensor (F): F=1 (Fuel presence); F=0 (Fuel empty)
// 3.	SW3: Mars Gravity Detection (M): M=1: gravity detected
// 4.	SW4: Mars Touch Down Detection (T): T=1: Touch Down
// (Note: for visual feedback, echo SW1,SW2,SW3,SW4 to LD1,LD2,LD3,LD4)
// 
//  
// System Outputs:
// 1.	LD5: Rocket Ignition (R): R=1: Ignite Rocket
// 2.	LD6: Disengage Rocket (D): (0: Attach; 1: Disengage)
// 3.	LD7: Ion Thrust Ignition (I): I=1: Ignite Ion Thrust Engine
// 4.	LD8: Landing Jet Ignition (J): J=1: Jet Engine Ignition
//
//
// Transitions: 
// •	Launch Switch (L=1) initiates transition from Rest1 to Launch
// •	Rocket Fuel Sensor (F=0) initiates transition from Launch to Cruise
// •	Mars Gravity Detection (M=1) initiates transition from Cruise to Landing
// •	Touch Down Detection (T=1) initiates transition from Landing to Rest2
//
//

#include <IOShieldOled.h>

// set pin numbers:
const int BTN1 = 4;    
const int BTN2 = 78;    
const int BTN3 = 80;    
const int BTN4 = 81;

const int SW1 = 2;
const int SW2 = 7;
const int SW3 = 8;
const int SW4 = 79;   

const int ledPin =  13;     
const int LD1 =  70;      
const int LD2 =  71;    
const int LD3 =  72;
const int LD4 =  73;
const int LD5 =  74;
const int LD6 =  75;
const int LD7 =  76;
const int LD8 =  77;	 // System Operational LED

// state variables:
int BTN1_state = 0;       
int BTN2_state = 0;
int BTN3_state = 0;
int BTN4_state = 0;
int SW1_state = 0; 
int SW2_state = 0; 
int SW3_state = 0; 
int SW4_state = 0; 

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
// Note: for 10-bit A/D, the range of sensorValue = 0 to 1023

// variables
int state = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);  
  pinMode(LD1, OUTPUT);  
  pinMode(LD2, OUTPUT);    
  pinMode(LD3, OUTPUT);  
  pinMode(LD4, OUTPUT);     
  pinMode(LD5, OUTPUT);  
  pinMode(LD6, OUTPUT);    
  pinMode(LD7, OUTPUT);  
  pinMode(LD8, OUTPUT);     

  // initialize the pushbutton pin as an input:
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);

  // initialize switches as inputs:
  pinMode(SW1, INPUT);  
  pinMode(SW2, INPUT);
  pinMode(SW3, INPUT);
  pinMode(SW4, INPUT); 

  // Turn OFF all LEDs
  digitalWrite(LD1, LOW); 
  digitalWrite(LD2, LOW); 
  digitalWrite(LD3, LOW); 
  digitalWrite(LD4, LOW);  

  digitalWrite(LD5, LOW); 
  digitalWrite(LD6, LOW); 
  digitalWrite(LD7, LOW); 
  digitalWrite(LD8, LOW); 

  // Initialize OLED:
  IOShieldOled.begin();
  IOShieldOled.displayOn();

}  // end setup()

void loop() {
  delay(10);

  // read switches and buttons
  SW1_state = digitalRead(SW1);
  SW2_state = digitalRead(SW2);
  SW3_state = digitalRead(SW3);
  SW4_state = digitalRead(SW4);

  if (SW1_state == HIGH) {
    digitalWrite(LD1, HIGH);
  } 
  else if (SW1_state == LOW) {
    digitalWrite(LD1,LOW); 
  }
  if (SW2_state == HIGH) {
    digitalWrite(LD2, HIGH);
  } 
  else if (SW2_state == LOW) {
    digitalWrite(LD2,LOW); 
  }
  if (SW3_state == HIGH) {
    digitalWrite(LD3, HIGH);
  } 
  else if (SW3_state == LOW) {
    digitalWrite(LD3,LOW); 
  }
  if (SW4_state == HIGH) {
    digitalWrite(LD4, HIGH);
  } 
  else if (SW4_state == LOW) {
    digitalWrite(LD4,LOW); 
  }

  switch(state) 
  {
  case 0:
    // rest1, state0    
    digitalWrite(LD5, LOW); 
    digitalWrite(LD6, LOW); 
    digitalWrite(LD7, LOW); 
    digitalWrite(LD8, LOW);

    if (SW1_state == HIGH) {
      state = 1;
    } 
    else {
      state = 0;
    }
    break;

  case 1:
    // Launch, state1 
    digitalWrite(LD5, HIGH); 
    digitalWrite(LD6, LOW); 
    digitalWrite(LD7, LOW); 
    digitalWrite(LD8, LOW);

    if (SW2_state == LOW) {
      state = 2;
    } 
    else {
      state = 1;  
    }
    break;

  case 2:
    // Cruise, state2   
    digitalWrite(LD5, LOW); 
    digitalWrite(LD6, HIGH); 
    digitalWrite(LD7, HIGH); 
    digitalWrite(LD8, LOW);

    if (SW3_state == HIGH) {
      state = 3;
    } 
    else {
      state = 2;
    }
    break;

  case 3:
    // Landing, state3 
    digitalWrite(LD5, LOW); 
    digitalWrite(LD6, LOW); 
    digitalWrite(LD7, LOW); 
    digitalWrite(LD8, HIGH);

    if (SW4_state == HIGH) {
      state =4;
    } 
    else {
      state = 3;
    }
    break;

  case 4:
    // Rest2, state4   
    digitalWrite(LD5, LOW); 
    digitalWrite(LD6, LOW); 
    digitalWrite(LD7, LOW); 
    digitalWrite(LD8, LOW);
    break;

  }
  delay(10);
}