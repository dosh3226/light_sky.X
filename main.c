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

/* trying to sort out a timer function 
 * copying this from the demo file 
 */
/**
 * @brief This clears IF flag, stops, reloads, and starts TMR1
 * @return None
 * @param [in] 16-bit TMR1H:L value
 * @example TMR1_StopAndStartTimer(DELAY_3s);
 */
inline void TMR1_StopAndStartTimer(uint16_t delay)
{
    // Clearing IF flag.
    PIR3bits.TMR1IF = 0;
    
    // Stop, reload, start
    TMR1_StopTimer();
    TMR1_WriteTimer(delay);
    TMR1_StartTimer();
}


void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

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
    
    while (1)
    {
        // Add your application code
        //LED0 = 0;    //LED1 turns on when SW0 is pressed
        if(SW0 == 1)
        {
            LED0 = 0;    //LED1 turns on when SW0 is pressed
        }
        //LED0 = !SW0;    //LED1 turns on when SW1 is pressed
    }
}
/**
 End of File
*/