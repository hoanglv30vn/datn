
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

UNSIGNED INT16 KQADC,AN0;
INT8 DATA=0;
CHAR *NHAN1[], *NHAN[]="HELLO";
CHAR *PACKAGE[]={"S","ID", "COMMAND" ,"LENGHT","DATA1", "DATA2","CHECKSUM","STOP *"}   ;
CHAR NHIETDO[]="27";
CHAR RCV[]="RECEIVED";
UNSIGNED INT8 KYTU[30], VT=0,TTNHAN=0;   
//--------------------------------------------------------------------//
#INT_RDA
VOID NGAT()
{
   KYTU[VT] = GETC () ;

   IF (KYTU[VT] == '.')
   {
      KYTU[VT] = '\0';
      TTNHAN = 1;
      VT = 0;
   }

   ELSE
   VT++;
}

VOID XUATLCD()
{
   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, KYTU);
   DELAY_MS (1);
}

INT ADC_READ(INT kenh)
{
   SET_ADC_CHANNEL (kenh);
   KQADC = 0;
   FOR (INT I = 0; I < 100; I++)
   {
      KQADC = KQADC + READ_ADC () ;
      DELAY_MS (1);
   }

   KQADC = KQADC / (100 * 2.046);
   RETURN KQADC;
}

VOID MAIN()
{
   SET_TRIS_D (0XF0);
   SET_TRIS_B (0);
   SET_TRIS_E (0);
   SETUP_ADC (ADC_CLOCK_DIV_8);
   SETUP_ADC_PORTS (sAN0);
   SET_ADC_CHANNEL (0);
   OUTPUT_LOW (PIN_D0);
   // OUTPUT_D (0X00);
   ENABLE_INTERRUPTS (INT_RDA);
   ENABLE_INTERRUPTS (GLOBAL);
   ENABLE_INTERRUPTS (INT_TIMER0);
   
   LCD_INIT (); // KHOI TAO LCD
   NHAN = "CHAO";

   WHILE (TRUE)
   {
      //OUTPUT_TOGGLE (PIN_D1);
      //OUTPUT_D (0x0F);
      AN0 = ADC_READ (0) ;

      IF (AN0 > 26)
      {
         //XUATLCD ();
         ITOA (AN0, 10, NHIETDO);
         PACKAGE[4] = NHIETDO;
         for (INT i = 0; i < 7; i++)
         {
            PRINTF (PACKAGE[i]);
            DELAY_MS (1);
         }

         DELAY_MS (1000);
      }

      IF (TTNHAN == 1)
      {
         
         TTNHAN = 0;
         XUATLCD () ;
         LCD_GOTOXY (2, 2) ;
         
         OUTPUT_TOGGLE (PIN_D0);
         OUTPUT_TOGGLE (PIN_D1);
         OUTPUT_TOGGLE (PIN_D2);
         OUTPUT_TOGGLE (PIN_D3);
         /*
         FOR (INT J = 0; J < 8; J++)
         {
            IF (KYTU[J] == RCV[J])
            {
               
               DATA = DATA + J;
            }

         }

         IF (DATA == 28)
         {
            DATA=0;
            PRINTF (LCD_PUTC, "OK");
            OUTPUT_TOGGLE (PIN_D0);
            OUTPUT_TOGGLE (PIN_D1);
            OUTPUT_TOGGLE (PIN_D2);
            OUTPUT_TOGGLE (PIN_D3);
         }*/
      }
   }
}

