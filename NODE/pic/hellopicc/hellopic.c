
#INCLUDE <16F887.H>
#DEVICE ADC=10
#INCLUDE <STRING.H>
#INCLUDE <STDLIB.H>
#INCLUDE <STDIO.H>
#INCLUDE <MATH.H>
//#INCLUDE <TV_LCD.C>

/*
int atoi(CONST char *s) : sting --> s� nguy�n
long atol(CONST char *s) : string --> s� nguy�n d�i
float atof(CONST char *s) : string --> s� thuc
*/
#FUSES NOWDT, PUT, HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)
#define BT1_PIN PIN_B1
#define BT2_PIN PIN_B2
#define BT3_PIN PIN_B3
#define LCD_ENABLE_PIN  PIN_E0                                   
#define LCD_RS_PIN      PIN_E1                                
#define LCD_RW_PIN      PIN_E2                              
#define LCD_DATA4       PIN_C0                               
#define LCD_DATA5       PIN_C1                                 
#define LCD_DATA6       PIN_C2                                   
#define LCD_DATA7       PIN_C3  
#INCLUDE <LCD.C>

UNSIGNED INT16 KQADC,AN0, AN1;

UNSIGNED INT8 CONFIG_FUN=0, CONFIG_STT=0, ID_NODE = 0;
INT1 TT_CONFIG=0, TT_FUN=0, TT_STT=0;
INT1 TT_DEVICE[8]={0, 0, 0, 0, 0, 0, 0, 0};
INT1 TT_SENSOR[8]={0, 0, 0, 0, 0, 0, 0, 0};
//INT1 TT_DEVICE[8]={0, 0, 0, 0, 0, 0, 0, 0};
INT8 DATA1 = 2;
CHAR *NHAN1[], *NHAN[]="HELLO";
CHAR *PACKAGE[]={"S","ID", "COMMAND" ,"LENGHT","DATA1", "DATA2","CHECKSUM","#"};
CHAR NHIETDO1[]="27";
CHAR NHIETDO2[]="27";
char id_[]="0";
CHAR RCV[]="RECEIVED";
UNSIGNED INT8 KYTU[30], VT=0,TTNHAN=0;   
//--------------------------------------------------------------------//
#INT_RDA
VOID NGAT()
{
   KYTU[VT] = GETC ();

   IF (KYTU[VT] == id_[0])
   {
      TTNHAN = 1;
   }

   IF (KYTU[VT] == '.')
   {
      
      KYTU[VT] = '\0';
      VT = 0;
      TTNHAN = 1;
   }

   ELSE
   VT++;
}

VOID CHON_ID()
{
   TT_STT = 1;

   WHILE (TT_STT)
   {
      IF (input (BT3_PIN) == 0) //neu nut bam duoc bam
      {
         ID_NODE ++;
         IF (ID_NODE > 15) ID_NODE = 0;
         DELAY_MS (200) ;
         ITOA (ID_NODE, 10, id_);
         LCD_GOTOXY (1, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, id_);
         DELAY_MS (1);
         OUTPUT_TOGGLE (PIN_D0);         
      }
   }

   

   PACKAGE[1] = id_;
}

VOID RESET_CONFIG()
{
   ID_NODE = 0;
   //TT_SENSOR ={0, 0, 0, 0, 0, 0, 0, 0};
   //TT_DEVICE ={0, 0, 0, 0, 0, 0, 0, 0};
}

VOID BUTT_OKE()
{
   TT_FUN = 0;
   TT_STT = 0;
}

VOID CONFIG_NODE()
{
   SWITCH (CONFIG_FUN)
   {
      CASE 0:
      CHON_ID () ;
      BREAK;

      CASE 1:
      //CONFIG_DEVICE () ;
      NHAN="CASE1";
      LCD_GOTOXY (10, 2) ;
      DELAY_MS (10);
      PRINTF (LCD_PUTC, NHAN);
      BREAK;

      CASE 2:
      //CONFIG_SENSOR () ;
      BREAK;

      CASE 3:
      RESET_CONFIG () ;
      BREAK;
   }
}

VOID BUTT_FUN()
{
   TT_FUN = 1;

   WHILE (TT_FUN)
   {
      IF (input (BT2_PIN) == 0) //neu nut bam duoc bam
      {
         CONFIG_FUN ++;
         IF (CONFIG_FUN > 3) CONFIG_FUN = 0;
         DELAY_MS (200) ;
         
         //HIEN THI
         ITOA (CONFIG_FUN, 10, id_);
         LCD_GOTOXY (1, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, id_);         
      }
   }

   CONFIG_NODE () ;
}

VOID quet_phim()
{
/*   IF (TT_CONFIG)
   {
      IF (input (BT2_PIN) == 0) //neu nut bam duoc bam
      {
         LCD_GOTOXY (1, 1) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, "BT2");
         BUTT_FUN () ;
         CONFIG_NODE () ;
      }

      
      else IF (input (BT3_PIN) == 0) //neu nut bam duoc bam
      {
         LCD_GOTOXY (1, 1) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, "BT3");
         //BUTT_TT () ;
      }
   }
   */

   
   IF (input (BT1_PIN) == 0) //neu nut bam duoc bam
   {
      LCD_GOTOXY (1, 1) ;
      DELAY_MS (10);
      PRINTF (LCD_PUTC, "BT1");
      FOR (INT I = 0; I < 10; I++)
      {
         IF (input (BT1_PIN) == 0)
         {
            DELAY_MS (1000) ;

            IF (I == 9)
            {
               //CONFIG NODE
               TT_CONFIG = ~TT_CONFIG;
               PRINTF (LCD_PUTC, "config");
            }
         }

         ELSE
         {
            BUTT_OKE () ;
            I = 10;
         }
      }
   }

}

#INT_EXT
 VOID ngat_ngoai  ()
 {
    quet_phim ();
 }

 VOID XUATLCD ()
 {
    LCD_GOTOXY (1, 1) ;
    DELAY_MS (10);
    PRINTF (LCD_PUTC, KYTU);
    DELAY_MS (1);
 }

 INT ADC_READ (INT kenh)
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

 VOID chuong_trinh_con  ()
 {
    for (INT i = 0; i <= 30; i++)
    {
       OUTPUT_TOGGLE (PIN_D1);
       delay_ms (100);
    }
 }

 VOID MAIN ()
 {
    SET_TRIS_D (0XF0);
    SET_TRIS_B (0xFF);
    SET_TRIS_E (0);
    SET_TRIS_C (0x80);
    SETUP_ADC (ADC_CLOCK_DIV_8);
    SETUP_ADC_PORTS (sAN0);
    ENABLE_INTERRUPTS (INT_RDA);
    ENABLE_INTERRUPTS (GLOBAL);
    ENABLE_INTERRUPTS (INT_TIMER0);
    enable_interrupts (INT_EXT); //Cho phep ngat ngoai
    enable_interrupts (INT_EXT_H2L); //Ngat xay ra khi co xung tu cao xuong thap
    LCD_INIT (); // KHOI TAO LCD
    ID_NODE = 0;
    TT_CONFIG = 0;

    WHILE (TRUE)
    {
       //AN1 = ADC_READ (1) ;
       AN0 = ADC_READ (0) ;

       IF (TT_CONFIG)
       {
          BUTT_FUN () ;
       }

       chuong_trinh_con ();

       IF (AN0 > 26)
       {
          ITOA (AN0, 10, NHIETDO1);
          PACKAGE[4] = NHIETDO1;
          ITOA (AN1, 10, NHIETDO2);
          PACKAGE[5] = NHIETDO2;
          
          for (INT i = 0; i < 8; i++)
          {
             PRINTF (PACKAGE[i]);
             DELAY_MS (1);
          }

          
          DELAY_MS (1000);
       }

       IF (TTNHAN == 1)
       {
          
          TTNHAN = 0;
          XUATLCD ();
          
          OUTPUT_TOGGLE (PIN_D0);
          OUTPUT_TOGGLE (PIN_D1);
          OUTPUT_TOGGLE (PIN_D2);
          OUTPUT_TOGGLE (PIN_D3);
       }
    }
 }

