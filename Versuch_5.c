#include <MSP430.h>
#include "hal\hal_lcd.h"

void itoc(int in, char ch[]); //INT TO CHAR
void FlashW(unsigned int wert, volatile unsigned int *flash); //FLASH beschreiben

volatile unsigned int __attribute__((section(".infoD"))) flashData; //FLASH Variable
char txt[] = "Wert: xxx"; //Ausgabe für Display
unsigned int flashDataCopy; //Kopie von FLASH

int main(void) {

	WDTCTL = WDTPW | WDTHOLD; //WDT aus

	halLcdInit(); //LCD INIT
	halLcdBackLightInit(); //LCD INIT
	halLcdSetBackLight(46); //LCD INIT
	halLcdSetContrast(95); //LCD INIT
	halLcdClearScreen(); //LCD INIT


	P2IE  = 0b00000000; //Interrupt Port2 ausschalten
	P2DIR = 0b00000000; //Port 2 als Eingang
	P2OUT = 0b11000000; //Port 2.6 && 2.7  Eingang mit Pull-Up
	P2REN = 0b11111111; //Port 2 Eingänge grounden
	P2IES = 0b11000000; //Port 2.6 && 2.7 auf steigende Flanke

	P2IFG = 0b00000000; //Interrupt Flag zurücksetzen
	P2IE  |= 0b11000000; //Interrupts aktivieren für Port 2.6 && 2.7

	flashDataCopy = flashData; // Kopie von aktuellem Wert erhalten

	if(flashDataCopy >=255) flashDataCopy = 0; //Wenn >=255, Wert zurücksetzen
	else flashDataCopy++; //sonst ++
	itoc(flashDataCopy,txt); //Txt mit Wert von flashDataCopy beschreiben

	halLcdPrintLine(txt,0,0); //Wert ausgeben

	FlashW(flashDataCopy, &flashData); //Flash mit neuem Wert beschreiben

	__bis_SR_register(0b11111000); //LPM4 + IE enable
}

void itoc(int in, char ch[]) //INT TO CHAR über Modolo und Division
{
    ch[6] = ((in - (in%10)) - ((in - (in%10))%100))/100 + '0';
    ch[7] = ((in - (in%10))%100)/10 + '0';
    ch[8] = in%10 + '0';

}

void FlashW(unsigned int wert, volatile unsigned int *flash)
{
    while(FCTL3 & BUSY){} //Ist Flash beschäftigt?

    FCTL1 = FWPW + ERASE; //Speicher zurücksetzen
    FCTL3 = FWPW; //Speicher zurücksetzen
    *flash = 0; //Speicher zurücksetzen

    while(FCTL3 & BUSY){} //Ist Flash beschäftigt?

    FCTL1 = FWPW + WRT; //Wert schreiben
    *flash = wert; //Wert schreiben

    FCTL1 = FWPW; //Speicher sperren
    FCTL3 = FWPW + LOCK; //Speicher sperren
}

__attribute__((interrupt(PORT2_VECTOR)))
void PORT2_VECTOR_ISR(void)
{
	if(P2IFG == 0b01000000)
	{
		flashDataCopy = 95;
		itoc(flashDataCopy,txt);
		FlashW(flashDataCopy, &flashData);
		halLcdClearScreen();
		halLcdPrintLine(txt,0,0);
		P2IFG &= ~0b01000000;
	}

	if(P2IFG == 0b10000000)
	{
		flashDataCopy = 253;
		itoc(flashDataCopy,txt);
		FlashW(flashDataCopy, &flashData);
		halLcdClearScreen();
		halLcdPrintLine(txt,0,0);
		P2IFG &= ~0b10000000;
	}
}

