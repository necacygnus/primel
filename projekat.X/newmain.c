#include<p30fxxxx.h>
#include "timer1.h"
#include <stdlib.h>


_FOSC(CSW_FSCM_OFF & XT_PLL4);///instruction takt je isti kao i kristal
_FWDT(WDT_OFF);
_FGS(CODE_PROT_OFF);




int period,ms,sekund,stoperica,vreme,brojac_ms;
int n, p, pom;


/*******************************************************************
//funkcija za kasnjenje u milisekundama
*********************************************************************/
void Delay_ms (int vreme)//funkcija za kasnjenje u milisekundama
	{
		stoperica = 0;
		while(stoperica < vreme);
	}

void initTIMER1(int period)//konfiguracija Timer1
{
	unsigned int match_value;//vrednost koja se stavlja u period

	ConfigIntTimer1(T1_INT_PRIOR_1 & T1_INT_ON);//prioritet i ukljucivanje tajmera
	WriteTimer1(0);
	match_value = period ;
	OpenTimer1(T1_ON & T1_GATE_OFF & T1_IDLE_CON & T1_PS_1_1 & T1_SYNC_EXT_OFF & T1_SOURCE_INT,match_value );

}



void __attribute__((__interrupt__)) _T1Interrupt(void)
{

   	TMR1 =0;
   // ms=1;//fleg za milisekundu ili prekid;potrebno ga je samo resetovati u funkciji

	brojac_ms++;//brojac milisekundi
    //stoperica++;//brojac za funkciju Delay_ms

    if (brojac_ms == 1000)//sek
        {
          brojac_ms=0;
         // sekund=1;//fleg za sekundu
          if (PORTFbits.RF0) {
              for (pom = 0; pom < 21; pom++);
              if (PORTFbits.RF0)
        n++;
          }
       }
    
    if (PORTFbits.RF0 == 0 && n != 0) {
        for (pom = 0; pom < 21; pom++);
        if (PORTFbits.RF0 == 0 && n != 0)
    {
        p = n;
        n = 0;
    }
    }
    /*if (PORTFbits.RF0)
        n++;
    else if (n != 0)
    {
        p = n;
        n = 0;
    }*/
    
    
    
    IFS0bits.T1IF = 0;   

}  



int main(void)
	{

	ADPCFGbits.PCFG4=1;//defini?emo da pin B4 nije analogni vec digitalni
	ADPCFGbits.PCFG5=1;//defini?emo da pin B5 nije analogni vec digitalni
    ADPCFGbits.PCFG6=1;
    ADPCFGbits.PCFG7=1;

	TRISBbits.TRISB4=0;//konfigurisemo kao izlaz
	TRISBbits.TRISB5=0;//konfigurisemo kao izlaz
    TRISBbits.TRISB6=0;
    TRISBbits.TRISB7=0;
    
    TRISFbits.TRISF0=1;

	//TRISDbits.TRISD0=0;//izlaz

    initTIMER1(10000);// Fosc = 10MHz = Ftakta(ukljucen _PLLX4) => na svakih 10000 dobijam 1000Hz = 1ms


	while(1)
	{

		if (p > 3) {
            p = 0;
            LATBbits.LATB5 = ~LATBbits.LATB5;
        }
        /*else if (p > 4) {
            p = 0;
            LATBbits.LATB6 = ~LATBbits.LATB6;
        }
        else if (p > 1){
            p = 0;
            LATBbits.LATB7 = ~LATBbits.LATB7;
        }*/
		
		
		

	}//od whilea
return 0;
}//od maina









