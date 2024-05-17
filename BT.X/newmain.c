/* 
 * File:   newmain.c
 * Author: student
 *
 * Created on 17. maj 2024., 13.44
 */

#include <stdio.h>
#include <stdlib.h>
#include <p30fxxxx.h>
#include "BT.h"

_FOSC(CSW_FSCM_OFF & XT_PLL4);//instruction takt je isti kao i kristal
_FWDT(WDT_OFF);

unsigned char tempRX;
unsigned int broj1,broj2;

/*
 * 
 */

void __attribute__((__interrupt__)) _U1RXInterrupt(void) 
{
    IFS0bits.U1RXIF = 0;
    tempRX=U1RXREG;

} 

int main(int argc, char** argv) {

    initUART1();

	while(1)
	{

            WriteUART1('s');


            WriteUART1(tempRX);

            for(broj1=0;broj1<3000;broj1++)
            for(broj2=0;broj2<1000;broj2++);

    }//od whilea

    return (EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}

