#include <msp430.h>

int main(void)
{
	/* Init */
	WDTCTL = WDTPW + WDTHOLD; /* Watchdog aus! */

	P1DIR |= 0b11111111;
	P2DIR |= 0b00000000;
	P2REN |= 0b11111111;
	P1OUT |= 0b00000000;
	P2OUT |= 0b11111111;

	int merker1 = 0;
	int merker2 = 0;

	while(1){
		merker1= P2IN;
		if(merker1 == merker2)
		{

		}
		else
		{
			if((P2IN & BIT6) != BIT6)
			{
				P1OUT ^= 0x01;
			}
			if((P2IN & BIT7) != BIT7)
						{
							P1OUT ^= 0x02;
						}
			merker2 = merker1;
		}

	}
}
