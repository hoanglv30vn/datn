#INCLUDE <16F887.H>
#DEVICE ADC=10
#INCLUDE <STRING.H>
#INCLUDE <STDLIB.H>
#INCLUDE <STDIO.H>
#FUSES NOWDT, PUT, HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)
#DEFINE BT1_PIN PIN_B1
#DEFINE BT2_PIN PIN_B2
#DEFINE BT3_PIN PIN_B3
#DEFINE LCD_ENABLE_PIN  PIN_E0                                   
#DEFINE LCD_RS_PIN      PIN_E1                                
#DEFINE LCD_RW_PIN      PIN_E2  
#DEFINE LCD_DATA4       PIN_C0                               
#DEFINE LCD_DATA5       PIN_C1                                 
#DEFINE LCD_DATA6       PIN_C2                                   
#DEFINE LCD_DATA7       PIN_C3  
#INCLUDE <LCD.C>
#BIT TMR1IF = 0x0C.0 //bit thu 0 (TMR1IF) cua PIR1

#INCLUDE <khaibaobien.c> // VARIABLE.

//#INCLUDE <CONFIG_NODE.C> // C?U HINH NODE.
#INCLUDE <config_1.C> // C?U HINH NODE.


