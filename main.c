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
//#define SW0         PORTBbits.RB4
#define SW0         LATBbits.LATB4

/* high and low values */
/* 220-420ns */
int T0H = 0;
/* 750ns-1.6us */
int T1H = 0;
/* 750ns-1.6us */
int T0L = 0;
/* 220-420ns */
int T1L = 0;

uint16_t tmr1_delay_1sec = 0xB1E0;

void flash_led()
{    
    int counter = 0;
    while (1)
    {
        LED0 = 1;
        TMR1_Reload();
        while(TMR1_ReadTimer() < tmr1_delay_1sec)
        {
            counter++;
        }
        // Clearing IF flag.
        PIR3bits.TMR1IF = 0;
        LED0 = 0;
        TMR1_Reload();
        while(TMR1_ReadTimer() < tmr1_delay_1sec)
        {
            counter++;
        }
        // Clearing IF flag.
        PIR3bits.TMR1IF = 0;
        counter++;
    }
}
//
//void send_1()
//{
//    LATCbits.LATC3 = 1;
//    TMR2_Period8BitSet(0xF000);
//    TMR2_Start();
//    while(TMR2_HasOverflowOccured() == 0);
//    LATCbits.LATC3 = 1;
//    TMR2_Stop();
//}

void TMR0_Initialize_custom(void)
{
    // Set TMR0 to the options selected in the User Interface

    // T0CS HFINTOSC; T0CKPS 1:8192; T0ASYNC synchronised; 
    T0CON1 = 0x6D;

    // TMR0H 121; 
    TMR0H = 0x3C;

    // TMR0L 0; 
    TMR0L = 0x79;

    // Clearing IF flag
    PIR3bits.TMR0IF = 0;

    // T0OUTPS 1:16; T0EN enabled; T016BIT 8-bit; 
    T0CON0 = 0x8F;
}

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    /* init slow timer */
    TMR0_Initialize();
    TMR1_Initialize();
    /* init the nanosecond timer */
    //TMR2_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    TRISFbits.TRISF3 = 0;   //LED0 as output
    TRISBbits.TRISB4 = 1;   //SW0 as input
    LED0 = 1; // LED0 off
    
    // string 1
    //TRISCbits.TRISC3 = 0;
    
    uint16_t counter = 0;
//    uint16_t tmr_ctr = 0;
    //TMR1_StartTimer();
    while (1)
    {
        // timer 0
//        for(int i = 0; i < 5; i++)
//        {
//            if(TMR0_HasOverflowOccured())
//            {
//                LED0=!LED0;
//                TMR0H = 0x79;
//                TMR0L = 0x10;
//                PIR3bits.TMR0IF = 0;
//            }
//        }
//        for(int i = 0; i < 5; i++)
//        {
//            if(TMR0_HasOverflowOccured())
//            {
//                LED0=!LED0;
//                TMR0H = 0x10;
//                TMR0L = 0x79;
//                PIR3bits.TMR0IF = 0;
//            }
//        }
        
        // timer 1
        for(int i = 0; i < 5; i++)
        {
            if(TMR1_HasOverflowOccured())
            {
                LED0=!LED0;
                //TMR1H 133; 
                TMR1H = 0x85;
                //TMR1L 238; 
                TMR1L = 0xEE;
                PIR3bits.TMR1IF = 0;
            }
        }
        for(int i = 0; i < 5; i++)
        {
            if(TMR1_HasOverflowOccured())
            {
                LED0=!LED0;
                //TMR1H 133; 
                TMR1H = 0x85;
                //TMR1L 238; 
                TMR1L = 0xEE;
                PIR3bits.TMR1IF = 0;
            }
        }
//        LED0 = 0;
//        TMR0_Reload(0xFF);
//        while(PIR3bits.TMR0IF == 0);
//        LED0 = 1;
//        TMR0_Reload(0xFF);
//        while(PIR3bits.TMR0IF == 0);
    }
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