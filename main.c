/*
 * blue: data in
 * white: no idea, shorted to blue, orange, red and black
 * red and orange shorted: probably 5V in
 * black I assume ground
 */


/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F57Q43
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

#define LED0        LATFbits.LATF3
#define CHAIN0      LATAbits.LATA7
//#define SW0         PORTBbits.RB4
#define SW0         LATBbits.LATB4

/* from here:
 * http://www.szledcolor.com/download/WS2813%20LED.pdf
 */

/* high and low values */
/* 300ns-450ns so 1 tmr0_delay cycle */
int T0H = 1;

/* 750ns-1000ns so 3 tmr0_delay cycles */
int T1H = 3;

/* 300ns-100us so 1 tmr0_delay cycle */
int T0L = 1;

/* 300ns-100us so 1 tmr0_delay cycle */
int T1L = 1;

/* 300us or more so 1 tmr3 counter cycle */
int reset_time = 1;

// bit toggling timer
// current delay: 312.5ns
void tmr0_delay()
{
    TMR0_Initialize();
    while(1) {
        if(TMR0_HasOverflowOccured())
        {
            return;
        }
    }
}

// long timer
// currently 0.5s delay
void tmr1_delay()
{
    TMR1_Initialize();
    while(1) {
        if(TMR1_HasOverflowOccured())
        {
            return;
        }
    }
}

// reset timer
// currently 8ms = 8,000us delay
// so 100 refreshes per second or so
void tmr3_delay()
{
    TMR3_Initialize();
    while(1) {
        if(TMR1_HasOverflowOccured())
        {
            return;
        }
    }
}

//void ns_375_low()
//{
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    return 0;
//}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    /* init slow timer */
    //TMR0_Initialize();
    //TMR1_Initialize();
   
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    TRISFbits.TRISF3 = 0;   //LED0 as output
    TRISAbits.TRISA7 = 0;   //RA7 as output
    TRISBbits.TRISB4 = 1;   //SW0 as input
    LED0 = 1; // LED0 off
    //IO_RA7_SetHigh();
    //IO_RF3_SetHigh();
    
    int LEDs = 3;
    
    /* RGB for each LED = 3 bytes per LED */
    uint8_t string[9];
    string[0] = 255;
    string[1] = 0;
    string[2] = 0;
    
    string[3] = 0;
    string[4] = 255;
    string[5] = 0;
    
    string[6] = 0;
    string[7] = 0;
    string[8] = 255;
    
    /* RGB for each LED = 3 bytes per LED */
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    CHAIN0=1;
//    for(int m = 0; m < 11; m++) {CHAIN0=0;}
//    for(int m = 0; m < 11; m++) {CHAIN0=1;}
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=0;
//    CHAIN0=1;
//    CHAIN0=0;
//    CHAIN0=1;
    
    for(int i = 0; i < 9; i++)
    {
        /* 8 bits in a byte */
        for(int j = 0; j < 7; j++)
        {
            /* bit j of byte i of uint8_t string */
            if(((string[i] & ( 1 << j )) >> j) == 0)
            {
                // 375ns delay
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;

                // 2x 375ns delay
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
            }
            else
            {
                // 2.5 x 375ns delay
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                
                CHAIN0=1;
                CHAIN0=1;
                CHAIN0=1;
                
                // 2x 375ns delay
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
                CHAIN0=0;
            }
            
        }
    }

//    while (1)
//    {
        // flash once at the end of the cycle
        //LED0=!LED0;
        IO_RF3_SetHigh();
        IO_RA7_SetHigh();
        tmr1_delay();
        IO_RF3_SetLow();
        IO_RA7_SetLow();
        //LED0=!LED0;
        tmr1_delay();
        IO_RF3_SetHigh();
        IO_RA7_SetHigh();
        tmr1_delay();
//    }
        while (1) {}
}

//        LED0 = 0;
//        counter = 0;
//        // Clearing IF flag.
//        PIR3bits.TMR1IF = 0;
//        TMR1_Reload();
//        counter = TMR1_ReadTimer();
//        while(counter < tmr1_delay_1sec)
//        {
//            counter = TMR1_ReadTimer();
//            tmr_ctr++;
//        }
//        TMR1_WriteTimer(0);
//        TMR1_Reload();
//        tmr_ctr = 0;
/**
 End of File
*/