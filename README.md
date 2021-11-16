

# AVR-Interrupt-master Library
![](https://img.shields.io/badge/release-v%201.1.0-blue)

This library is designed for the Atmel AVR microcontroller. The most interesting part of this library is, those who are familiar with Arduino Interrupt function, they can use it like an Arduino Interrupt library function.

**Contents**

- [AVR-Interrupt-master Library](#avr-interrupt-master-library)
  * [Supported AVR chip list](#supported-avr-chip-list)
  * [Two main function:](#two-main-function)
  * [Function 1:](#function-1)
  * [Function 2:](#function-2)
  * [Example:](#example)
    + [CODE:](#code)
    + [SIMULATION:](#simulation)
  * [Interrupt Pin  Sense Map:](#Interrupt-Pin--Sense-Map)
    + [ATmega16,32,8535 :](#atmega16328535-)
    + [ATmega164,324,644,1284 :](#atmega1643246441284-)
    + [ATmega8,48,88,168,328 :](#atmega84888168328-)
    + [Atmega25,45,85,24,44,84 :](#atmega254585244484-)


 
## Supported AVR chip list

| ATmega series   | ATtiny series  |
|-----------------|----------------|
| 1\) ATmega16    | 13\) ATtiny24  |
| 2\) ATmega32    | 14\) ATtiny44  |
| 3\) ATmega164   | 15\) ATtiny84  |
| 4\) ATmega324   | 16\) ATtiny25  |
| 5\) ATmega644   | 17\) ATtiny45  |
| 6\) ATmega1284  | 18\) ATtiny85  |
| 7\) ATmega8     |                |
| 8\) ATmega48    |                |
| 9\) ATmega88    |                |
| 10\) ATmega168  |                |
| 11\) ATmega328  |                |
| 12\) ATmega8535 |                |


## Two main function:
        1) attachInterrupt(pin, function, INTERRUPT_SENSE);
        2) digitalPinToInterrupt( pin );

## Function 1: 
      attachInterrupt(pin, function, INTERRUPT_SENSE);
     
      pin:(INT0, INT2, INT2)
          INT0, INT1, INT2 pins are the external interrupt pin.
         
      function:
          this parameter takes a void function.
          please, Don't use delay function inside the void function
          
      INTERRUPT_SENSE:(LOW,CHANGE,RISING,FALLING)
          This function is an external interrupt function so, It's required 
          input sense to call interrupt service routine.
         
         
    ==================================================================================
    LOW: when external interrupt pin(INT0, INT1, INT2) will get only the low or ground
            signal then ISR() will be called.
              
    CHANGE: When external interrupt pin(INT0, INT1, INT2) will get any logic change from 
            the previous logic then ISR() will be called. Example, when the previous state 
            is 0 when interrupt pin get logic 1 ISR() will be called or vice versa.
         
    RISING: When external interrupt pin(INT0, INT1, INT2) will get a falling edge signal 
            then ISR() will be called.
                 
    FALLING:When external interrupt pin(INT0, INT1, INT2) will get a rising edge signal
             then ISR() will be called.
    ==================================================================================
      
       
       


## Function 2:
      digitalPinToInterrupt( pin );
      
       pin:(INT0, INT2, INT2)
           INT0, INT1, INT2 pins are the external interrupt pin.
      
     
      
## Example:

### CODE:

      
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
        }
    }

    void JUEL_ISR(void)
    {
        state ^=(1<<0);
    }
      
### SIMULATION:
![atmega simulation](https://user-images.githubusercontent.com/28595839/70394248-92f31780-1a1d-11ea-9929-7d0fec5164d1.png)

> Figure: ATmega32 interrupt simulation using Proteus.


## Interrupt Pin & Sense Map:

### ATmega16,32,8535 : 
|      | LOW | CHANGE |  RISING | FALLING |
|:----:|:---:|:------:|:-------:|:-------:|
| INT0 | ✔   | ✔    | ✔      | ✔       |
| INT1 | ✔   | ✔    | ✔      | ✔       |
| INT2 | ❌   | ❌     | ✔      | ✔      |


### ATmega164,324,644,1284 : 
|      | LOW | CHANGE |  RISING | FALLING |
|:----:|:---:|:------:|:-------:|:-------:|
| INT0 | ✔   | ✔    | ✔       | ✔      |
| INT1 | ✔   | ✔    | ✔       | ✔      |
| INT2 | ✔   | ✔    | ✔       | ✔      |

### ATmega8,48,88,168,328 : 
|      | LOW | CHANGE |  RISING | FALLING |
|:----:|:---:|:------:|:-------:|:-------:|
| INT0 | ✔   | ✔    | ✔       | ✔      |
| INT1 | ✔   | ✔    | ✔       | ✔      |

### Atmega25,45,85,24,44,84 : 
|      | LOW | CHANGE |  RISING | FALLING |
|:----:|:---:|:------:|:-------:|:-------:|
| INT0 | ✔   | ✔     | ✔      | ✔      |


