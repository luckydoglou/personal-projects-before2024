// ***** 0. Documentation Section *****
// SwitchLEDInterface.c for Lab 8
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to toggle an LED
// while a button is pressed and turn the LED on when the
// button is released.  This lab requires external hardware
// to be wired to the LaunchPad using the prototyping board.
// January 3, 2019
//    Xiaolou Huang(Lor), Jon Valvano and Ramesh Yerraballi

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOE      0x00000010  // port E Clock Gating Control

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void Delay100ms(unsigned long time); // delay

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic
// shown in Lab8_artist.sch (PCB Artist schematic file) or 
// Lab8_artist.pdf (compatible with many various readers like Adobe Acrobat).
int main(void){ 
	unsigned long In; // input from PE0, the switch
	unsigned long Out; // output to PE1, the LED
	unsigned long volatile delay;
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  TExaS_Init(SW_PIN_PE0, LED_PIN_PE1, ScopeOn);  // activate grader and set system clock to 80 MHz

	// initialization
	// --------------
	SYSCTL_RCGC2_R |= 0x00000010; 	// active clock for port E
	delay = SYSCTL_RCGC2_R; 				// allow time for clock to start
	GPIO_PORTE_AMSEL_R = 0x00; 			// disable analog function
	GPIO_PORTE_PCTL_R = 0x00000000; // GPIO clear bit PCTL
	GPIO_PORTE_DIR_R = 0x02; 				// PF0 input, PE1 output
	GPIO_PORTE_AFSEL_R = 0x00; 			// no alternate function 
	GPIO_PORTE_DEN_R = 0x03; 				// enable digital pins PE1 and PE0
	// ---------------
  EnableInterrupts();           // enable interrupts for the grader
  while(1){
    Delay100ms(1);
		In = GPIO_PORTE_DATA_R & 0x01; // read PE0(SW4) into In
		Out = GPIO_PORTE_DATA_R & 0x02; // read PE1(LED) into Out
		if (In != 0x00) { // if PE0 is 0
			if (Out == 0x00) { // if PE1 is 0
				Out = 0x02; // toggle to 1
			} else { // if PE1 is 1
				Out = 0x00; // toggle to 0
			}
		} else { // if PE0 is 1
			Out = 0x02; // keep the LED(PE1) on
		}
		GPIO_PORTE_DATA_R = Out; // write output to PF2
  }
}

void Delay100ms(unsigned long time) {
	unsigned long count;
	while (time > 0) {
		count = 1600000;
		while (count > 0) {
			count--;
		}
		time--;
	}
}
