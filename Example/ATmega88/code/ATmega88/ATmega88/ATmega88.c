/*
 * External_interrupt.c
 *
 * Created: Md.Tarikul Islam Juel
 */ 


#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "lib/AVR_INTERRUPT_MASTER_JUEL.h"


void JUEL_ISR(void);//declaration of JUEL_ISR function

uint8_t state=0x00;
int main(void)
{
	attachInterrupt(INT1,JUEL_ISR,FALLING);
	DDRC|=(1<<PC0);// OUTPUT bit set

    while(1)
    {
        if(state)
		{
			PORTC |=(1<<PC0);
		}
		else
		{
			PORTC &=~(1<<PC0);
		}
		//_delay_ms(5000);
    }
}

void JUEL_ISR(void)
{
	state ^=(1<<0);
}



