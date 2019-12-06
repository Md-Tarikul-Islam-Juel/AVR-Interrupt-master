/*
 * AVR_INTERRUPT_MASTER_JUEL.h
 *
 * Created: 12/2/2019 10:25:14 AM
 *  Author: juel
 */ 


#ifndef AVR_INTERRUPT_MASTER_JUEL_H_
#define AVR_INTERRUPT_MASTER_JUEL_H_


//----------------------------------This preprocessor ensure before compiling for the right MCU-----------------------------//
#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)
#elif defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)
#elif defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)
#elif defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)
#elif defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
#elif defined(__AVR_ATmega8535__)
#elif defined(__AVR_ATmega8__)
#elif defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)
#elif defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)
#elif defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)
#elif defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#elif defined(__AVR_ATtiny25__ )
#elif defined(__AVR_ATtiny45__ )
#elif defined(__AVR_ATtiny85__ )
#elif defined(__AVR_ATtiny24__ ) || defined(__AVR_ATtiny24A__ )
#elif defined(__AVR_ATtiny44__ ) || defined(__AVR_ATtiny44A__ )
#elif defined(__AVR_ATtiny84__ ) || defined(__AVR_ATtiny84A__ )
#else
	#error "no definitions available for this AVR"
#endif
//--------------------------------------------------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#define LOW 0
#define CHANGE 51
#define RISING 52
#define FALLING 53

void (*pointer_of_received_function_pointer)();//The purpose of this (void type function pointer) is to store the received function address from main file and run it inside the ISR() which is located at this file (AVR_INTERRUPT_MASTER_JUEL.c)
//---------------------------------------------------------------------------------------------------------------------------//



//---------------------------------------------------------------------------------------------------------------------------//
void attachInterrupt(uint8_t EXTERNAL_INTERRUPT_PIN, void (*received_function_pointer)(), uint8_t INTERRUPT_SENSE);
uint8_t digitalPinToInterrupt(uint8_t pin);
void INTERRUPT_SENSE_CONTROL(uint8_t pin, uint8_t DETECT_SENSE);
//---------------------------------------------------------------------------------------------------------------------------//



#endif /* AVR_INTERRUPT_MASTER_JUEL_H_ */