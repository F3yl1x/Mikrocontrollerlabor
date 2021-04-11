#include "msp430.h"
#include "hal\hal_lcd.h"

int Page = 0;
int PagePos=0;
int Pos[8] = {0,0,0,0,0,0,0,0};
char* Texte[]={"Einstellungen","Telefonbuch","Anrufe","Klingelton", "Lautstaerke",
					 "Seppi", "Karl Heinz","Carlo", "24.03.21", "Tutut","BeepBeep",
					 "0 Prozent","50 Prozent","100 Prozent","0162-123235","0163-143235",
					 "07243-123665","07212-213665","Zurueck"};
int Select[][4]= { {0,1,2,-1}, //Hauptmenue 0
				   {3,4,-1}, //Einstellungen 1
				   {5,6,-1}, //Telefonbuch 2
				   {7,8,-1}, //Anrufe 3
				   {9,10,-1}, //Klingeltöne 4
				   {11,12,13,-1}, //Lautstärke 5
				   {14,-1}, //Seppi 6
				   {15,16,17,-1} //Karl-Heinz 7
				 };

char js;


void PrintMenue(char JS)
{

    halLcdClearScreen();
    halLcdPrintLine("Auswahl:",0,0);

    if(JS=='o')
    {
    	if(PagePos > 0)
    	{
    		PagePos --;
    	}
    }

    if(JS=='u')
        {
        	if(Select[Page][PagePos+1] > -1)
        	{
        		PagePos ++;
        	}
        }

    if(JS=='l')
            {
    			Pos[Page] = 0;

            	if(Page==1 || Page==2 || Page==3) Page=0;
            	else if(Page==4 || Page==5) Page=1;
            	else if(Page==6 || Page==7) Page=2;

            	PagePos = Pos[Page];
            }

    if(JS=='r')
                {
    				Pos[Page] = PagePos;

                	if(Page==0)
                		{
                		if(PagePos==0) Page = 1;
                		else if(PagePos==1) Page = 2;
                		else if(PagePos==2) Page = 3;
                		}
                	else if(Page==1)
                		{
                		if(PagePos==0) Page = 4;
                		else if(PagePos==1) Page = 5;
                		}
                	else if(Page==2)
                		{
                		if(PagePos==0) Page = 6;
                		else if(PagePos==1) Page = 7;
                		}

                	PagePos = Pos[Page];
                }

    for(int z=0; Select[Page][z] > -1; z++)
    {
    	if(z==PagePos)
    	{
    	halLcdPrintLineCol(Texte[Select[Page][z]],(z+1),1,1);
    	}
    	else halLcdPrintLine(Texte[Select[Page][z]],(z+1),0);
    }

}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    halLcdInit();
    halLcdBackLightInit();
    halLcdSetBackLight(46);
    halLcdSetContrast(95);

    halLcdPrintLine("Auswahl:",0,0);

    for(int z=0; z < 3; z++)
    	{
    	if(z==PagePos)
    	{
    	    	    		halLcdPrintLineCol(Texte[Select[Page][z]],(z+1),1,1);
    	    	    	}
    	    	    	else halLcdPrintLine(Texte[Select[Page][z]],(z+1),0);
    	}


    P1DIR |= 0b11; //Port 1.0 als Ausgang
    P1OUT &= ~0b11; //Port 1.0 Ausschalten

    P2IE  = 0b00000000; //Interrupt Port2 ausschalten
    P2DIR = 0b00000000; //Port 2 als Eingang
    P2OUT = 0b00111110; //Port 2.6 Eingang mit Pull-Up
    P2REN = 0b11111111; //Port 2 Eingänge grounden
    P2IES = 0b00111110; //Port 2.6 auf steigende Flanke

    P2IFG = 0b00000000; //Interrupt Flag zurücksetzen
    P2IE  |= 0b00111110; //Interrupts aktivieren für Port 2.6

	__bis_SR_register(LPM4_bits + GIE); // Globale Interruptfreigabe + Energiesparen
}



__attribute__((interrupt(PORT2_VECTOR)))
void PORT2_VECTOR_ISR(void)
{
   if((P2IFG == 0b00000010)) //links
   	   {
	   js= 'l';
	   P2IFG &= ~0b00000010;
   	   }

   if((P2IFG == 0b00000100)) //rechts
       {
	   js= 'r';
   	   P2IFG &= ~0b00000100;
       }

   if((P2IFG == 0b00001000)) //mitte
       {
	   js= 'm';
       P2IFG &= ~0b00001000;
       halLcdPrintLine("Die Mitte hat",6,1);
       halLcdPrintLine("keine Funktion",7,1);
       goto stop;
       }

   if((P2IFG == 0b00010000)) //oben
       {
	   js= 'o';
       P2IFG &= ~0b00010000;
       }

   if((P2IFG == 0b00100000)) //unten
       {
       js= 'u';
       P2IFG &= ~0b00100000;
       }

   	   PrintMenue(js);
   	   stop:;
}
