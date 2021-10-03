
#INCLUDE <16F887.H>
#DEVICE ADC=10
#INCLUDE <STRING.H>
#INCLUDE <STDLIB.H>
#INCLUDE <STDIO.H>
#INCLUDE <MATH.H>
#INCLUDE <TV_LCD.C>
/*
int atoi(CONST char *s) : sting --> s� nguy�n
long atol(CONST char *s) : string --> s� nguy�n d�i
float atof(CONST char *s) : string --> s� thuc
*/
#FUSES NOWDT, PUT, HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)


#define LCD_ENABLE_PIN  PIN_E0                                   
#define LCD_RS_PIN      PIN_E1                                
#define LCD_RW_PIN      PIN_E2                              
#define LCD_DATA4       PIN_D4                               
#define LCD_DATA5       PIN_D5                                 
#define LCD_DATA6       PIN_D6                                   
#define LCD_DATA7       PIN_D7  
#INCLUDE <LCD.C>

UNSIGNED INT16 KQADC;
INT8 DATA=4;
CHAR *NHAN1[], *NHAN[]="HELLO";
CHAR *PACKAGE[]={"S","ID", "COMMAND" ,"LENGHT","DATA","CHECKSUM","STOP *"}   ;
CHAR NHIETDO[]="27";
CHAR RCV='A';
   
//--------------------------------------------------------------------//
#INT_RDA
VOID NGAT()
{
   DATA = 3;
   NHAN = "HEALLA";
   
   //RCV = GETC();
   OUTPUT_TOGGLE (PIN_D0);
   //GETS (NHAN) ;
   /*
   OUTPUT_TOGGLE (PIN_D1) ;
   NHAN1 = "hello";
   NHAN2 = "owe";
   GETS (NHAN) ;
   DATA = STRCMP (NHAN, NHAN1);
   IF (DATA == 0)
   {
      OUTPUT_TOGGLE (PIN_D0);
   }
   */
}

VOID XUATLCD()
{
   LCD_GOTOXY(1,1);
   DELAY_MS(10);
   PRINTF(LCD_PUTC, NHAN);
   DELAY_MS(10);
}


VOID ADC_READ()
{
   KQADC = 0;
   FOR (INT I = 0; I<100; I++)
   {
      KQADC = KQADC + READ_ADC () ;
      DELAY_MS (1) ;
   }

   KQADC = KQADC / (100 * 2.046);
}



VOID MAIN()
{
   SET_TRIS_D (0XF0) ;
   SET_TRIS_B (0) ;
   SET_TRIS_E (0) ;
   SETUP_ADC (ADC_CLOCK_DIV_8) ;
   SETUP_ADC_PORTS (sAN0) ;
   SET_ADC_CHANNEL (0);
   OUTPUT_LOW (PIN_D0) ;
   OUTPUT_D (0X00) ;
   ENABLE_INTERRUPTS (INT_RDA) ;
   ENABLE_INTERRUPTS (GLOBAL) ;
   ENABLE_INTERRUPTS (INT_TIMER0) ;
   
     LCD_INIT(); // KHOI TAO LCD
     NHAN="CHAO";
   WHILE (TRUE)
   {
      //OUTPUT_TOGGLE (PIN_D1) ;
      OUTPUT_D (0x0F) ;
      ADC_READ () ;
      IF (KQADC > 26)
      {
      XUATLCD();
         ITOA (KQADC, 10, NHIETDO);    
         PACKAGE[4]=NHIETDO;
         for (int i=0; i<7; i++){
             PRINTF (PACKAGE[i]) ;
             DELAY_MS (1) ;              
           }  
                 DELAY_MS (1000) ;
      }   


   }
}



