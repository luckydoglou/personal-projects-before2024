// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

// the 256 comes from the length of the sine wave table
// bus is 80 MHz
// Period =  80000000/32/Freq=2500000/Freq
#define C 4778  // 523.3 Hz
#define D 4257  // 587.3 Hz
#define E 3792  // 659.3 Hz
#define G 3189  // 784 Hz

// 4-bit 32 elements sine wave
const unsigned short wave[32] = {8, 9, 11, 12, 13, 14, 14, 15, 15, 15, 14, 14, 13, 12, 11, 9,
																8, 7, 5, 4, 3, 2, 2, 1, 1, 1, 2, 2, 3, 4, 5, 7};
unsigned char Index;	
unsigned char prevStateSW;																 

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();          			// Port B is DAC
	Index = 0;
	prevStateSW = 0;
  NVIC_ST_CTRL_R = 0;       // disable SysTick during setup
	NVIC_ST_RELOAD_R = 0;// reload value
	NVIC_ST_CURRENT_R = 0;    // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
  NVIC_ST_CTRL_R = 0x07;  // enable SysTick with core clock and interrupts
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
	// this routine sets the RELOAD and starts SysTick
  NVIC_ST_RELOAD_R = period-1;// reload value
	NVIC_ST_CURRENT_R = 0;    // any write to current clears it
}

// **************Sound_Play*********************
// Play the required note
// Input: note, the note to play
// Output: none
void Sound_Play(unsigned char note) {
	switch (note) {
		case 'C':
			if (note == 'C' && prevStateSW != 'C') {
				Sound_Tone(C);
				prevStateSW = 'C';
			}
			break;
		case 'D':
			if (note == 'D' && prevStateSW != 'D') {
				Sound_Tone(D);
				prevStateSW = 'D';
			}
			 break;
		case 'E':
			if (note == 'E' && prevStateSW != 'E') {
				Sound_Tone(E);
				prevStateSW = 'E';
			}
			break;
		case 'G':
			if (note == 'G' && prevStateSW != 'G') {
				Sound_Tone(G);
				prevStateSW = 'G';
			}
			break;
		default:
			prevStateSW = 0;
			Sound_Off();
			break;
	}
}

// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void) {
	// this routine stops the sound output
	prevStateSW = 0;
	Sound_Tone(1);
	DAC_Out(0);
}

// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){  
	Index = (Index+1)&0x1F;
	DAC_Out(wave[Index]);
		
}
