#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include <inc/hw_memmap.h>
#include <inc/hw_types.h>
#include <inc/hw_gpio.h>

/*
 * lcdlib1.c
 *
 *  Created on: 17-Jun-2019
 *      Author: harshitrathore
 */


//#define LOWNIB(x) P3OUT = (P3OUT & 0xF0) + (x & 0x0F)

void lcdInit()
{

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE , GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 );


    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6 , 0x00);


    lcdWriteCmd(0x28) ;  //4bit Mode
    lcdWriteCmd(0x01) ;  //clear LCD
    lcdWriteCmd(0x06) ;  //Auto Increment Cursor
    lcdWriteCmd(0x0C) ;  //Display On , Cursor On
}

void lcdWriteCmd (unsigned char cmd)
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5 , 0x00);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 , (cmd>>4 & 0x0F) );
    lcdTriggerEn() ;
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 , (cmd & 0x0F) );
    lcdTriggerEn() ;
    SysCtlDelay(270000);
}

void lcdWriteData (unsigned char data)
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5 , 0x20);

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 , (data>>4 & 0x0F) );

    lcdTriggerEn() ;

    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 , (data & 0x0F) );

    lcdTriggerEn() ;

    SysCtlDelay(270000);
}

void lcdWriteString (unsigned char str[])
{
    unsigned int len , i ;
    len = strlen(str);
    for(i=0;i<len;i++)
    {
        lcdWriteData (str[i]);
    }
}

void lcdWriteInt (unsigned int number)
{
    int c = 0;
    unsigned int n = number;

    while (n != 0)
    {
        n /= 10;
        c++;
    }

    unsigned char numberArray[20];

    //c = 0;
    n = number;
    numberArray[c] = '\0';
    c-- ;
    while (n != 0)
    {
        numberArray[c] =( n % 10 ) + 48 ;
        n /= 10;
        c--;
    }
    numberArray[c] = '\0';

    lcdWriteString(numberArray);
}

void lcdTriggerEn()
{
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 , 0x10);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 , 0x00);
}
