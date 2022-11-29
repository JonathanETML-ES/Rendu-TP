/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}

void APP_UpdateState (APP_STATES NewState)  //Création fonction pour update la machine d'état
{
    appData.state = NewState;
}

void AllumageDesLeds(void)      //Création fonction pour allumer toutes les LEDs
{
    BSP_LEDOn(BSP_LED_0);
    BSP_LEDOn(BSP_LED_1);
    BSP_LEDOn(BSP_LED_2);
    BSP_LEDOn(BSP_LED_3);
    BSP_LEDOn(BSP_LED_4);
    BSP_LEDOn(BSP_LED_5);
    BSP_LEDOn(BSP_LED_6);
    BSP_LEDOn(BSP_LED_7);
}

void ExtinctionDesLeds(void)    //Création fonction pour éteindre toutes les LEDs
{
    BSP_LEDOff(BSP_LED_0);
    BSP_LEDOff(BSP_LED_1);
    BSP_LEDOff(BSP_LED_2);
    BSP_LEDOff(BSP_LED_3);
    BSP_LEDOff(BSP_LED_4);
    BSP_LEDOff(BSP_LED_5);
    BSP_LEDOff(BSP_LED_6);
    BSP_LEDOff(BSP_LED_7);
}

void GestionChenillard(uint8_t val_chenillard)  //Création fonction pour gérer le chenillard
{
    switch(val_chenillard)
        {
            case 0: 
            {
                ExtinctionDesLeds();
                break;
            }
            case 1: 
            {
                BSP_LEDOff(BSP_LED_7);
                BSP_LEDOn(BSP_LED_0);
                break;
            }
            case 2: 
            {
                BSP_LEDOff(BSP_LED_0);
                BSP_LEDOn(BSP_LED_1);
                break;
            }
            case 3: 
            {
                BSP_LEDOff(BSP_LED_1);
                BSP_LEDOn(BSP_LED_2);
                break;
            }
            case 4: 
            {
                BSP_LEDOff(BSP_LED_2);
                BSP_LEDOn(BSP_LED_3);
                break;
            }
            case 5: 
            {
                BSP_LEDOff(BSP_LED_3);
                BSP_LEDOn(BSP_LED_4);
                break;
            }
            case 6: 
            {
                BSP_LEDOff(BSP_LED_4);
                BSP_LEDOn(BSP_LED_5);
                break;
            }
            case 7: 
            {
                BSP_LEDOff(BSP_LED_5);
                BSP_LEDOn(BSP_LED_6);
                break;
            }
            case 8: 
            {
                BSP_LEDOff(BSP_LED_6);
                BSP_LEDOn(BSP_LED_7);
                break;
            }
        }
}



/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */
S_ADCResults ADCResults;

uint8_t Chenillard = 0;

void APP_Tasks ( void )
{
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:                    //état APP_STATE_INIT de la machine d'état
        {
            lcd_init();                         //Initialisation de mon LCD
            lcd_gotoxy(1,1);                    //Allez à la ligne 1 de mon affichage
            printf_lcd("Tp0 Led+AD 2022-2y");   //
            lcd_gotoxy(1,2);                    //Allez à la ligne 2 de mon affichage
            printf_lcd("Docteur Shifteh");              //
            lcd_bl_on();                        //Activation du rétroéclairage
            
            BSP_InitADC10();                    //Initialisation de mes ADCs
            
            AllumageDesLeds();                  //Appel de ma fonction pour allumer les LEDs
            
            DRV_TMR0_Start();                   //Start du Timer1
                    
            APP_UpdateState (APP_STATE_WAIT);   //Changement d'état de ma machine d'état
            break;
        }
        
        case APP_STATE_WAIT:                    //état APP_STATE_WAIT de la machine d'état
        {
            // rien à faire ici !
            break;
        }
        
        case APP_STATE_SERVICE_TASKS:           //état APP_STATE_SERVICE_TASKS de la machine d'état
        {
            ADCResults = BSP_ReadAllADC();      //Lecture des ADCs
            
            GestionChenillard(Chenillard);      //Appel de ma fonction pour gérer le chenillard
            if(Chenillard <= 7) Chenillard++;
            else Chenillard = 1;
            
            lcd_gotoxy(1,3);                    //Allez à la ligne 3 de mon affichage
            printf_lcd("Ch0 %4d Ch1 %4d", ADCResults.Chan0, ADCResults.Chan1); 
                                                //Affichage de mes deux ADCs
            
            APP_UpdateState (APP_STATE_WAIT);   //Changement d'état de ma machine d'état
            break;
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
