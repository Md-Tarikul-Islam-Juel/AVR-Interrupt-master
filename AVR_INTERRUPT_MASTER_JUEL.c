/*
 * AVR_INTERRUPT_MASTER_JUEL.c
 *  Created: MD.Tarikul Islam Juel
 *  Email: md.tarikulislamjuel@gmail.com
 *
 *	  ====================== Register ======================
 *    Common Register :
 *				    SREG= I---T---H---S--V---N---Z---C   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[Status Register]
 *				  
 *    ATmega8,16,32,8535 :
 * 					MCUCR= SE---SM2---SM1---SM0---ISC11---ISC10---ISC01---ISC00  ~~~~~~~~~~~~~~~~~~[MCU Control Register]
 *
 *    ATmega16,32,8535 :
 *					MCUCSR= JTD---ISC2---x---JTRF---WDRF---BORF---EXTRF---PORF   ~~~~~~~~~~~~~~~~~~[MCU Control and Status Register]
 *				    GICR= INT1---INT0---INT2---x---x---x---IVSEL---IVCE ~~~~~~~~~~~~~~~~~~~~~~~~~~~[General Interrupt Control Register]
 *    
 *    ATmega8 :
 *				    GICR= INT1---INT0---x---x---x---x---IVSEL---IVCE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[General Interrupt Control Register]
 *
 *	  ATmega164,324,644,1284 :
 *					EICRA= x---x---ISC21---ISC20---ISC11---ISC10---ISC01---ISC00 ~~~~~~~~~~~~~~~~~~[External Interrupt Control Register A]
 *				    EIMSK= x---x---x---x---x---INT2---INT1---INT0   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[External Interrupt Mask Register]
 *
 *	  ATmega48,88,168,328 :
 *					EICRA= x---x---x---x---ISC11---ISC10---ISC01---ISC00 ~~~~~~~~~~~~~~~~~~[External Interrupt Control Register A]
 *				    EIMSK= x---x---x---x---x---x---INT1---INT0   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[External Interrupt Mask Register]
 *
 *
 *    ===================attachInterrupt()   step===================
 *    1) Global interrupt enable -------------------------------------sei();
 *    2) Config interrupt sense  -------------------------------------INTERRUPT_SENSE_CONTROL();
 *	  3) select external interrupt pin--------------------------------GICR
 *	  4) receive function pointer to run inside the ISR()
 *
 *
 *	  ==================== Interrupt pin supported sense ===========
 *    Atmega16,32,8535 : 
 *					   INT0(LOW,CHANGE,RISING,FALLING)
 *					   INT1(LOW,CHANGE,RISING,FALLING)
 *					   INT2(RISING,FALLING)
 *
 *    Atmega164,324,644,1284 :
 *  				   INT0(LOW,CHANGE,RISING,FALLING)
 *				   	   INT1(LOW,CHANGE,RISING,FALLING)
 *					   INT2(LOW,CHANGE,RISING,FALLING)
 *
 *    Atmega8,48,88,168,328 :
 *  				   INT0(LOW,CHANGE,RISING,FALLING)
 *				   	   INT1(LOW,CHANGE,RISING,FALLING)
 *		
 *
 */ 

#include "AVR_INTERRUPT_MASTER_JUEL.h"

void (*pointer_of_received_function_pointer)();//The purpose of this (void type function pointer) is to store the received function address from main file and run it inside the ISR()


//################################################################################################################################################################################
//==============================================================|  attachInterrupt() Start	|=====================================================================================
//################################################################################################################################################################################

//	------------possible parameter---------
//	EXTERNAL_INTERRUPT_PIN = INT0,INT1,INT2 (depends on MCU)
//  *received_function_pointer = void type function
//  INTERRUPT_SENSE = LOW,CHANGE,RISING,FALLING (depends on MCU)
//
//     Atmega16,32,8535 :
//  					   INT0(LOW,CHANGE,RISING,FALLING)
//  					   INT1(LOW,CHANGE,RISING,FALLING)
//  					   INT2(RISING,FALLING)
//
//     Atmega164,324,644,1284 :
//    					   INT0(LOW,CHANGE,RISING,FALLING)
//  				   	   INT1(LOW,CHANGE,RISING,FALLING)
//  					   INT2(LOW,CHANGE,RISING,FALLING)
//
//     Atmega8,48,88,168,328 :
//  					   INT0(LOW,CHANGE,RISING,FALLING)
//  				   	   INT1(LOW,CHANGE,RISING,FALLING)

void attachInterrupt(uint8_t EXTERNAL_INTERRUPT_PIN, void (*received_function_pointer)(), uint8_t INTERRUPT_SENSE)
{	
	#if defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
		|| defined(__AVR_ATmega8535__)
	
		sei();// To enable Global interrupt bit I 
		INTERRUPT_SENSE_CONTROL(digitalPinToInterrupt(EXTERNAL_INTERRUPT_PIN), INTERRUPT_SENSE);//this function set the interrupt sense mode(LOW,CHAGNE,RISING,FALLING)		GICR |= (1<<digitalPinToInterrupt(EXTERNAL_INTERRUPT_PIN));// External interrupt pin select (INT0,INT1,INT2)//NB: dont take it before INTERRUPT_SENSE_CONTROL() function because when you will use pull down network initally it call ISR() to take main action. 
		pointer_of_received_function_pointer=received_function_pointer;//here we send the address of (received_function_pointer) from main file to (address_of_receive_function) which is a void type function pointer [NB: the purpose is to run the received function inside the ISR() ]
	#endif
	
	#if defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
		sei();// To enable Global interrupt bit I 
		INTERRUPT_SENSE_CONTROL(digitalPinToInterrupt(EXTERNAL_INTERRUPT_PIN), INTERRUPT_SENSE);//this function set the interrupt sense mode(LOW,CHAGNE,RISING,FALLING)
		EIMSK |= (1<<digitalPinToInterrupt(EXTERNAL_INTERRUPT_PIN));// External interrupt pin select (INT0,INT1,INT2)//NB: dont take it before INTERRUPT_SENSE_CONTROL() function because when you will use pull down network initally it call ISR() to take main action. 
		pointer_of_received_function_pointer=received_function_pointer;//here we send the address of (received_function_pointer) from main file to (address_of_receive_function) which is a void type function pointer [NB: the purpose is to run the received function inside the ISR() ]
	#endif
	
}
//################################################################################################################################################################################
//==============================================================|  attachInterrupt() end  |=======================================================================================
//################################################################################################################################################################################



//################################################################################################################################################################################
//==============================================================| digitalPinToInterrupt() Start	|=================================================================================
//################################################################################################################################################################################
uint8_t digitalPinToInterrupt(uint8_t pin)// This function for to check the right interrupt pin has been selected
{
	#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
	    || defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
	    || defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
		|| defined(__AVR_ATmega8535__)
			switch(pin)
			{
				case INT0: return INT0;  //by default for atmega16,32=INT0=6-----atmega164=INT0=0
								break;
				case INT1: return INT1;  //by default for atmega16,32=INT1=7-----atmega164=INT1=1
								break;
				case INT2: return INT2;  //by default for atmega16,32=INT2=5-----atmega164=INT2=2
								break;
				default: printf("Error: please choose the right sense mode");
			}
	#endif
	
	
	#if defined(__AVR_ATmega8__)\
		|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
			switch(pin)
			{
				case INT0: return INT0;  //by default for atmega8=INT0=6
						   break;
				case INT1: return INT1;  //by default for atmega8=INT1=7
						   break;
				default: printf("Error: please choose the right sense mode");
			}
	#endif
}
//################################################################################################################################################################################
//==============================================================| digitalPinToInterrupt() End	|=================================================================================
//################################################################################################################################################################################



//################################################################################################################################################################################
//==============================================================| INTERRUPT_SENSE_CONTROL() Start	|=============================================================================
//################################################################################################################################################################################

//This function will control and config MCUCR & MCUCSR register to select the Interrupt sense
//This function select the sense mode according to the interrupt pin  

//	------------possible parameter---------
//	EXTERNAL_INTERRUPT_PIN = INT0,INT1,INT2  (depends on MCU)
//  INTERRUPT_SENSE = LOW,CHANGE,RISING,FALLING  (depends on MCU)
//
//     Atmega16,32,8535 :
//  					   INT0(LOW,CHANGE,RISING,FALLING)
//  					   INT1(LOW,CHANGE,RISING,FALLING)
//  					   INT2(RISING,FALLING)
//
//     Atmega164,324,644,1284 :
//    					   INT0(LOW,CHANGE,RISING,FALLING)
//  				   	   INT1(LOW,CHANGE,RISING,FALLING)
//  					   INT2(LOW,CHANGE,RISING,FALLING)
//
//     Atmega8,48,88,168,328 :
//  					   INT0(LOW,CHANGE,RISING,FALLING)
//  				   	   INT1(LOW,CHANGE,RISING,FALLING)

void INTERRUPT_SENSE_CONTROL(uint8_t pin, uint8_t DETECT_SENSE)
{
		#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
		|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
		|| defined(__AVR_ATmega8535__)
			
			if(pin==INT0)
			{
				if(DETECT_SENSE==LOW)
				{
					MCUCR &= ~(1<<ISC01);					MCUCR &= ~(1<<ISC00);
				}
				else if(DETECT_SENSE==CHANGE)
				{
					MCUCR &= ~(1<<ISC01);					MCUCR |= (1<<ISC00);
				}
				else if(DETECT_SENSE==FALLING)
				{
					MCUCR |= (1<<ISC01);
					MCUCR &= ~(1<<ISC00);
				}
				else if(DETECT_SENSE==RISING)
				{
					MCUCR |= (1<<ISC01);
					MCUCR |= (1<<ISC00);
				}
				else
				{
					//static_assert(0, "please choose the right sense mod");
				}
			}
	
			else if(pin==INT1)
			{
				if(DETECT_SENSE==LOW)
				{
					MCUCR &= ~(1<<ISC11);					MCUCR &= ~(1<<ISC10);
				}
				else if(DETECT_SENSE==CHANGE)
				{
					MCUCR &= ~(1<<ISC11);					MCUCR |= (1<<ISC10);
				}
				else if(DETECT_SENSE==FALLING)
				{
					MCUCR |= (1<<ISC11);
					MCUCR &= ~(1<<ISC10);
				}
				else if(DETECT_SENSE==RISING)
				{
					MCUCR |= (1<<ISC11);
					MCUCR |= (1<<ISC10);
				}
				else
				{
					//static_assert(0, "please choose the right sense mode");
				}
			}
	
			else if(pin==INT2)
			{
				if(DETECT_SENSE==LOW)
				{	
					//static_assert(0, "please choose the right sense mode (FALLING/RISING)");
				}
				else if(DETECT_SENSE==CHANGE)
				{
					//static_assert(0, "please choose the right sense mode (FALLING/RISING)");
				}
				else if(DETECT_SENSE==FALLING)
				{
					MCUCSR &= ~(1<<ISC2);
				}
				else if(DETECT_SENSE==RISING)
				{
					MCUCSR |= (1<<ISC2);
				}
				else
				{
					//static_assert(0, "please choose the right sense mode");
				}
			}
			else
			{
				//static_assert(0, "write something");
			}
	#endif
	
	
	
	#if defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
		|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
		|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
		|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)
		
		if(pin==INT0)
		{
			if(DETECT_SENSE==LOW)
			{
				EICRA &= ~(1<<ISC01);				EICRA &= ~(1<<ISC00);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				EICRA &= ~(1<<ISC01);				EICRA |= (1<<ISC00);
			}
			else if(DETECT_SENSE==FALLING)
			{
				EICRA |= (1<<ISC01);
				EICRA &= ~(1<<ISC00);
			}
			else if(DETECT_SENSE==RISING)
			{
				EICRA |= (1<<ISC01);
				EICRA |= (1<<ISC00);
			}
			else
			{
				//static_assert(0, "please choose the right sense mod");
			}
		}
		
		else if(pin==INT1)
		{
			if(DETECT_SENSE==LOW)
			{
				EICRA &= ~(1<<ISC11);				EICRA &= ~(1<<ISC10);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				EICRA &= ~(1<<ISC11);				EICRA |= (1<<ISC10);
			}
			else if(DETECT_SENSE==FALLING)
			{
				EICRA |= (1<<ISC11);
				EICRA &= ~(1<<ISC10);
			}
			else if(DETECT_SENSE==RISING)
			{
				EICRA |= (1<<ISC11);
				EICRA |= (1<<ISC10);
			}
			else
			{
				//static_assert(0, "please choose the right sense mode");
			}
		}
		
		else if(pin==INT2)
		{
			if(DETECT_SENSE==LOW)
			{
				EICRA &= ~(1<<ISC21);				EICRA &= ~(1<<ISC20);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				EICRA &= ~(1<<ISC21);				EICRA |= (1<<ISC20);
			}
			else if(DETECT_SENSE==FALLING)
			{
				EICRA |= (1<<ISC21);
				EICRA &= ~(1<<ISC20);
			}
			else if(DETECT_SENSE==RISING)
			{
				EICRA |= (1<<ISC21);
				EICRA |= (1<<ISC20);
			}
			else
			{
				//static_assert(0, "please choose the right sense mode");
			}
		}
		else
		{
			//static_assert(0, "write something");
		}
	#endif
	
	
	
	#if defined(__AVR_ATmega8__)
		if(pin==INT0)
		{
			if(DETECT_SENSE==LOW)
			{
				MCUCR &= ~(1<<ISC01);				MCUCR &= ~(1<<ISC00);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				MCUCR &= ~(1<<ISC01);				MCUCR |= (1<<ISC00);
			}
			else if(DETECT_SENSE==FALLING)
			{
				MCUCR |= (1<<ISC01);
				MCUCR &= ~(1<<ISC00);
			}
			else if(DETECT_SENSE==RISING)
			{
				MCUCR |= (1<<ISC01);
				MCUCR |= (1<<ISC00);
			}
			else
			{
				//static_assert(0, "please choose the right sense mod");
			}
		}
		
		else if(pin==INT1)
		{
			if(DETECT_SENSE==LOW)
			{
				MCUCR &= ~(1<<ISC11);				MCUCR &= ~(1<<ISC10);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				MCUCR &= ~(1<<ISC11);				MCUCR |= (1<<ISC10);
			}
			else if(DETECT_SENSE==FALLING)
			{
				MCUCR |= (1<<ISC11);
				MCUCR &= ~(1<<ISC10);
			}
			else if(DETECT_SENSE==RISING)
			{
				MCUCR |= (1<<ISC11);
				MCUCR |= (1<<ISC10);
			}
			else
			{
				//static_assert(0, "please choose the right sense mode");
			}
		}
		
		else
		{
			//static_assert(0, "write something");
		}
    #endif
	
	
	
	#if defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
		|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
		|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
		|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
		if(pin==INT0)
		{
			if(DETECT_SENSE==LOW)
			{
				EICRA &= ~(1<<ISC01);				EICRA &= ~(1<<ISC00);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				EICRA &= ~(1<<ISC01);				EICRA |= (1<<ISC00);
			}
			else if(DETECT_SENSE==FALLING)
			{
				EICRA |= (1<<ISC01);
				EICRA &= ~(1<<ISC00);
			}
			else if(DETECT_SENSE==RISING)
			{
				EICRA |= (1<<ISC01);
				EICRA |= (1<<ISC00);
			}
			else
			{
				//static_assert(0, "please choose the right sense mod");
			}
		}
		
		else if(pin==INT1)
		{
			if(DETECT_SENSE==LOW)
			{
				EICRA &= ~(1<<ISC11);				EICRA &= ~(1<<ISC10);
			}
			else if(DETECT_SENSE==CHANGE)
			{
				EICRA &= ~(1<<ISC11);				EICRA |= (1<<ISC10);
			}
			else if(DETECT_SENSE==FALLING)
			{
				EICRA |= (1<<ISC11);
				EICRA &= ~(1<<ISC10);
			}
			else if(DETECT_SENSE==RISING)
			{
				EICRA |= (1<<ISC11);
				EICRA |= (1<<ISC10);
			}
			else
			{
				//static_assert(0, "please choose the right sense mode");
			}
		}
		else
		{
			//static_assert(0, "write something");
		}
	#endif
	
}
//################################################################################################################################################################################
//==============================================================| INTERRUPT_SENSE_CONTROL() End	|=================================================================================
//################################################################################################################################################################################




//################################################################################################################################################################################
//==============================================================| ISR() Start |=================================================================================
//################################################################################################################################################################################

// All the interrupt service routing are here
#if defined(__AVR_ATmega16__) || defined(__AVR_ATmega16A__) || defined(__AVR_ATmega16P__) || defined(__AVR_ATmega16PA__)\
	|| defined(__AVR_ATmega32__) || defined(__AVR_ATmega32A__)\
	|| defined(__AVR_ATmega164__) || defined(__AVR_ATmega164A__) || defined(__AVR_ATmega164P__) || defined(__AVR_ATmega164PA__)\
	|| defined(__AVR_ATmega324__) || defined(__AVR_ATmega324A__) || defined(__AVR_ATmega324P__) || defined(__AVR_ATmega324PA__)\
	|| defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)\
	|| defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__)\
	|| defined(__AVR_ATmega8535__)
	ISR(INT0_vect)
	{
		pointer_of_received_function_pointer();
	}

	ISR(INT1_vect)
	{
		pointer_of_received_function_pointer();
	}

	ISR(INT2_vect)
	{
		pointer_of_received_function_pointer();
	}
#endif

#if defined(__AVR_ATmega8__)\
	|| defined(__AVR_ATmega48__) || defined(__AVR_ATmega48A__) || defined(__AVR_ATmega48P__) || defined(__AVR_ATmega48PA__) || defined(__AVR_ATmega48PB__)\
	|| defined(__AVR_ATmega88__) || defined(__AVR_ATmega88A__) || defined(__AVR_ATmega88P__) || defined(__AVR_ATmega88PA__) || defined(__AVR_ATmega88PB__)\
	|| defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega168A__) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega168PB__)\
	|| defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
	ISR(INT0_vect)
	{
		pointer_of_received_function_pointer();
	}

	ISR(INT1_vect)
	{
		pointer_of_received_function_pointer();
	}
#endif
//################################################################################################################################################################################
//==============================================================| ISR() End |=================================================================================
//################################################################################################################################################################################

