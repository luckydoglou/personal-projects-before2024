// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x30;      // 1) activate port E, F
  delay = SYSCTL_RCGC2_R;      // 2) no need to unlock
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
	
  GPIO_PORTE_AMSEL_R &= ~0x0F; // 3) disable analog function on PE3-0
  GPIO_PORTE_PCTL_R &= 0x0000FFFF; // 4) enable regular GPIO
  GPIO_PORTE_DIR_R &= ~0x0F;   // 5) inputs on PE3-0
  GPIO_PORTE_AFSEL_R &= ~0x0F; // 6) regular function on PE3-0
  GPIO_PORTE_DEN_R |= 0x0F;    // 7) enable digital on PE3-0
}

// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  return GPIO_PORTE_DATA_R & 0x0F;
}
