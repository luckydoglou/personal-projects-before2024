//======================================
// POT Trig
// Name: Xiaolou Huang (Lor)
// Summer 2018
//======================================
// Input: POT: sensorValue: 0 - 1023
//        scaling to convert: 0 - 180 degree
//======================================
// Output: OLED, minimum 4 significant digit
// cursor(0,1): POT TRIG SU2018
// cursor(0,2): LOR| degree: 000
// cursor(0,3): cos: 0.0000
// cursor(0,4): tan: 0.0000
//======================================

#include <IOShieldOled.h>

// set pin numbers:
const int ledPin =  13;
const int LD8 = 77;
int sensorPin = A0;    // select the input pin for the potentiometer

float sensorValue = 0;  // variable to store the value coming from the sensor
// Note: for 10-bit A/D, the range of sensorValue = 0 to 1023
//=============================================================================
// variables
float cos_value = 0;    // cosine value
float tan_value = 0;    // tangent value
float degree_value = 0;         // for converted degree value from sensorValue
//=============================================================================

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);   
  pinMode(LD8, OUTPUT);

  // Initialize OLED:
  IOShieldOled.begin();
  IOShieldOled.displayOn();

}  // end setup()

void loop() {  

  // System Operation LED ON:
  digitalWrite(LD8, HIGH);
  delay(10);  // wait for 10 ms 
  // note: @ the end, 10ms OFF
  // loop time = 10 ms + instructions + 10 ms = 20ms +
  //----------------------------------------------  

  // 1. Read POT input, scale to temperature in Fahrenheit:
  // -------------------------------------------------------------
  // read the value from the POT sensor:
  sensorValue = analogRead(sensorPin);

  // Scale 180 degree in degree:
  degree_value = round(sensorValue * 180 / 1023);

  // compute cosine and tangent value
  cos_value = (round(cos(degree_value * PI / 180) * 10000.0)) / 10000.0;  // change from degree to radian, then compute
  tan_value = (round(tan(degree_value * PI / 180) * 10000.0)) / 10000.0;  // change from degree to radian, then compute

  // 2. Display trig value @ OLED:
  // -------------------------------------
  //clear the display and reset the cursor to zero
  IOShieldOled.clearBuffer();

  IOShieldOled.setCursor(0,0);
  IOShieldOled.putString("POT TRIG SU2018");      

  IOShieldOled.setCursor(0,1);
  char degree_charArr[50];
  //convert the string to an array of characters
  snprintf(degree_charArr, 50, "LOR| degree:%.1f", degree_value);  // Lor is my NAME!
  //Display it @OLED:
  IOShieldOled.putString(degree_charArr);       

  // display cosine
  IOShieldOled.setCursor(0,2);
  char cosConvert_charArr[50];
  //convert the float date type number to an array of characters
  snprintf(cosConvert_charArr, 50, "cos: %.4f", cos_value);
  //Display it @OLED:
  IOShieldOled.putString(cosConvert_charArr);

  // display tangent
  IOShieldOled.setCursor(0,3);
  char tanConvert_charArr[50];
  //convert the float data type number to an array of characters
  snprintf(tanConvert_charArr, 50, "tan: %.4f", tan_value);
  //Display it @OLED:
  IOShieldOled.putString(tanConvert_charArr);


  //Display it @ OLED:
  IOShieldOled.updateDisplay();
  //----------------------------------------

  // System Operation LED Indicator:
  digitalWrite(LD8, LOW);  
  delay(10);           // wait for 10 ms      
} // end void loop()