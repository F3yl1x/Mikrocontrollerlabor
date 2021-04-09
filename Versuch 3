#include <MSP430.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; //WDT aus

	TA0CTL   |= 0b0101000110; // ACLK + Teiler auf 2 + MC0 + Interrups + Clear

	P1DIR |= 0b1; //Port 1.0 als Ausgang
	P1OUT &= ~0b1; //Port 1.0 Ausschalten

	P2IE  = 0b00000000; //Interrupt Port2 ausschalten
	P2DIR = 0b00000000; //Port 2 als Eingang
	P2OUT = 0b01000000; //Port 2.6 Eingang mit Pull-Up
	P2REN = 0b11111111; //Port 2 Eingänge grounden
	P2IES = 0b01000000; //Port 2.6 auf steigende Flanke

	P2IFG = 0b00000000; //Interrupt Flag zurücksetzen
	P2IE  |= 0b01000000; //Interrupts aktivieren für Port 2.6

	__bis_SR_register(0b11111000); //LPM4 + IE enable
}


__attribute__((interrupt(PORT2_VECTOR)))
void PORT2_VECTOR_ISR(void)
{
   P1OUT  |= 0b1; //LED an
   TA0CTL |= 0b100100; //MC1 + Clear
   P2IFG &= ~0b01000000; //Flag zurücksetzen
}


__attribute__((interrupt(TIMER0_A1_VECTOR)))
void TIMER0_A1_VECTOR_ISR(void)
{
    P1OUT  &= ~0b1; //LED aus
    TA0CTL &= ~0b100001; //MC0+ flg reset
}
