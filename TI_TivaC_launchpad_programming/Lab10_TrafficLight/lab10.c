// ***** 0. Documentation Section *****
// TableTrafficLight.c for Lab 10
// Runs on LM4F120/TM4C123
// Index implementation of a Moore finite state machine to operate a traffic light.  
// Daniel Valvano, Jonathan Valvano, Xiaolou Huang (Lor)
// March 16, 2019

// east/west red light connected to PB5
// east/west yellow light connected to PB4
// east/west green light connected to PB3
// north/south facing red light connected to PB2
// north/south facing yellow light connected to PB1
// north/south facing green light connected to PB0
// pedestrian detector connected to PE2 (1=pedestrian present)
// north/south car detector connected to PE1 (1=car present)
// east/west car detector connected to PE0 (1=car present)
// "walk" light connected to PF3 (built-in green LED)
// "don't walk" light connected to PF1 (built-in red LED)

// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"

// ***** 2. Global Declarations Section *****
// for SysTick
#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018))
//--------------------

#define goN 0
#define waitN 1
#define goE 2
#define waitE 3
#define walk 4
#define dontWalk0 5
#define walkLightOff0 6
#define dontWalk1 7
#define walkLightOff1 8

#define SENSOR 	(*((volatile unsigned long *)0x4002401C)) 		// enable PE2-PE0
#define TRAFFIC_LIGHT   (*((volatile unsigned long *)0x400050FC)) // enable PB5-PB0
#define WALK_LIGHT (*((volatile unsigned long *)0x40025028)) 	// enable PF3 and PF1
	
// Linked data structure
struct State {
	unsigned long Out_TrafficLight; // 6-bit pattern to output
	unsigned long Out_WalkLight; // output to PF1 and PF3 (embedded lights on micro-controller)
	unsigned long Time; // delay in 10ms units
	unsigned long Next[8]; // next states for inputs 0-7
};
typedef const struct State STyp;
STyp FSM[9] = {
	{0x21, 0x02, 400, {goN, waitN, goN, waitN, waitN, waitN, waitN, waitN}}, // goN
	{0x22, 0x02, 50, {goE, goE, goE, goE, walk, goE, walk, goE}},	// waitN
	{0x0C, 0x02, 400, {goE, goE, waitE, waitE, waitE, waitE, waitE, waitE}}, // goE
	{0x14, 0x02, 50, {walk, walk, goN, goN, walk, walk, walk ,walk}},	// waitE
	{0x24, 0x08, 300, {walk, dontWalk0, dontWalk0, dontWalk0, walk, dontWalk0, dontWalk0, dontWalk0}}, // walk
	{0x24, 0x02, 50, {walkLightOff0, walkLightOff0, walkLightOff0, walkLightOff0, walkLightOff0, walkLightOff0, walkLightOff0, walkLightOff0}},	// dontWalk0
	{0x24, 0x00, 50, {dontWalk1, dontWalk1, dontWalk1, dontWalk1, dontWalk1, dontWalk1, dontWalk1, dontWalk1}},	// walkLightOff0
	{0x24, 0x02, 50, {walkLightOff1, walkLightOff1, walkLightOff1, walkLightOff1, walkLightOff1, walkLightOff1, walkLightOff1, walkLightOff1}},	// dontWalk1
	{0x24, 0x00, 50, {goN, goE, goN, goN, walk, goE, goN, goN}}	// walkLightOff1
	//{0x24, 0x02, 1, {dontWalk, goE, goN, goN, walk, goE, goN, goN}}	// dontWalk2 
};
unsigned long currentState; // index to the current state
unsigned long Input; // store input from buttons

// FUNCTION PROTOTYPES: Each subroutine defined
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait10ms(unsigned long delay);
void PortF_Init(void);
void PortBE_Init(void);

// ***** 3. Subroutines Section *****
int main(void){ 
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff); // activate grader and set system clock to 80 MHz
	SysTick_Init(); 
	PortF_Init();		// set output PF1(don't walk), PF3(walk)
	PortBE_Init();		// set output PB0-PB5 to NG(North Green light), NY, NR, EG, EY, ER(East Red), 
										// set input PE0(east&west sensor), PE1(north&south sensor), PE2(walk sensor)
	currentState = goN;
  EnableInterrupts();
  while(1){
		TRAFFIC_LIGHT = FSM[currentState].Out_TrafficLight; // set traffic lights
		WALK_LIGHT = FSM[currentState].Out_WalkLight; 			// set walk lights
		SysTick_Wait10ms(FSM[currentState].Time);
		Input = SENSOR; 																		// read sensors
		currentState = FSM[currentState].Next[Input];				// get next state
  }
}


void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}
// The delay parameter is in units of the 80 MHz core clock. (12.5 ns)
void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}
// 800000*12.5ns equals 10ms
void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(800000);  // wait 10ms
  }
}

void PortF_Init(void){
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x0A;           // allow changes to PF3 and PF1
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0A;          // 5) PF3 and PF1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  //GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x0A;          // 7) enable digital I/O on PF3 and PF1
}
void PortBE_Init(void) {
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x12;      // 1) B E
  delay = SYSCTL_RCGC2_R;      // 2) no need to unlock
  GPIO_PORTE_AMSEL_R &= ~0x07; // 3) disable analog function on PE2-0
  GPIO_PORTE_PCTL_R &= 0x000000FF; // 4) enable regular GPIO
  GPIO_PORTE_DIR_R &= ~0x07;   // 5) inputs on PE2-0
  GPIO_PORTE_AFSEL_R &= ~0x07; // 6) regular function on PE2-0
  GPIO_PORTE_DEN_R |= 0x07;    // 7) enable digital on PE2-0
  GPIO_PORTB_AMSEL_R &= ~0x3F; // 3) disable analog function on PB5-0
  GPIO_PORTB_PCTL_R &= 0x00000000; // 4) enable regular GPIO
  GPIO_PORTB_DIR_R |= 0x3F;    // 5) outputs on PB5-0
  GPIO_PORTB_AFSEL_R &= ~0x3F; // 6) regular function on PB5-0
  GPIO_PORTB_DEN_R |= 0x3F;    // 7) enable digital on PB5-0
}

//
//#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
//#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
//#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
//#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
//#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

//#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
//#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
//#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
//#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
//#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
//#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
//	
//#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
//#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
//#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
//#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
//#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
//#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
//#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
//#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
//#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
//#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
//