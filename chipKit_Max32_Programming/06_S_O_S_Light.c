//==========================
// S-O-S Light
// Name: Xiaolou Huang (Lor)
// Summer 2018
//==========================

const int ledPin =  13;  // System Operational LED
const int LD1 =  70;     //*** Note: label on the board is for Uno32, this is MAX32, see MAX32 Reference Manual
const int LD2 =  71;     //*** Reference manual is wrong! LD pins are corrected here.
const int LD3 =  72;
const int LD4 =  73;
const int LD5 =  74;
const int LD6 =  75;
const int LD7 =  76;
const int LD8 =  77;

const int SW1 = 2; // switch 1
// variables will change:
int SW1_state = 0; 

// define LD array
int LD_array[8] = {LD1, LD2, LD3, LD4, LD5, LD6, LD7, LD8}; 


void setup() {
  pinMode(ledPin, OUTPUT);
  // initialize the LED pin as an output:
  for(int i = 0; i <= 8; i++) {
    pinMode(LD_array[i], OUTPUT);
  }

  // initialize switches as inputs:
   pinMode(SW1, INPUT);   
}

void loop(){
  // System Operation LED ON:
     digitalWrite(ledPin, HIGH);
  //----------------------------------------------   
  // read switches:
  SW1_state = digitalRead(SW1);
  
  if (SW1_state == HIGH) {
    
    // first S
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }
    delay(200);

    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }
    delay(200); 
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }
    delay(200);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }
    delay(200); 
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }
    delay(200);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }    
    delay(500);
    
    // second O
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }    
    delay(400);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    } 
    delay(400);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }
    delay(400);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }
    delay(400);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    } 
    delay(400);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }    
    delay(500);
    
    // third S
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }    
    delay(200);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }    
    delay(200);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }    
    delay(200);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }    
    delay(200);
    
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], HIGH);
    }    
    delay(200);
    
    // one second low interval
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }        
    delay(1000);
  }
    
  if (SW1_state == LOW) {
    for(int i = 0; i <=8; i++) {
      digitalWrite(LD_array[i], LOW);
    }  
  } 
  //------------------------------------
   // System Operation LED OFF:
     digitalWrite(ledPin, LOW); 
     delay(50);  // wait for 50 ms 
  
} // end loop