#include <msp430.h>

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;

	    P1DIR |= 0b11111111;
	    P1OUT |= 0b00000000;

	    P8DIR |= 0b1000;
	    P8SEL |= 0b1000;

	    P2REN |= 0b11111111;
	    P2OUT |= 0b11111111;

	    TA0CTL |= 0b0100010000;
	    TA0CCR0 = 300;

	    TA0CCR3 = 150;
	    TA0CCTL3 |= 0b11100000;

	    WDTCTL = WDT_ARST_1000;

	    while(1)
	    {

	    	WDTCTL = WDT_ARST_1000;

	    	if(((P2IN & BIT6) != BIT6) && (TA0CCR3 > 1))
	    		{
	    		TA0CCR3--;
	    		}

	    	if(((P2IN & BIT7) != BIT7) && (TA0CCR3 < 299))
	    		{
	    		TA0CCR3++;
	    		}

	    	if(TA0CCR3 == 299)
	    		P1OUT |= 0b10;
	    	else if(TA0CCR3 == 1)
	    		P1OUT |= 0b1;
	    	else P1OUT = ~(0b11);


	    	for(int z=0;z<1000;z++){}
	    }

	    return 0;
}

