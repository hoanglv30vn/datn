
#INCLUDE <16F887.H>
#DEVICE ADC=10
#INCLUDE <STRING.H>
#INCLUDE <STDLIB.H>
#INCLUDE <STDIO.H>
#INCLUDE <MATH.H>
//#INCLUDE <TV_LCD.C>

/*
INT ATOI(CONST CHAR *S) : STING --> S� NGUY�N
LONG ATOL(CONST CHAR *S) : STRING --> S� NGUY�N D�I
FLOAT ATOF(CONST CHAR *S) : STRING --> S� THUC
*/
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

UNSIGNED INT16 KQADC,AN0, AN1;

UNSIGNED INT8 CONFIG_FUN=0, ID_NODE = 0, STT_DEVICE=0;
INT1 TT_CONFIG=0, TT_FUN=0, TT_STT=0;
INT1 TT_DEVICE[8]={0, 0, 0, 0, 0, 0, 0, 0};
//INT1 TT_SENSOR[8]={0, 0, 0, 0, 0, 0, 0, 0};
CHAR TT_DEVICE_CHAR[]=" ";
//INT1 TT_DEVICE[8]={0, 0, 0, 0, 0, 0, 0, 0};
CHAR *PACKAGE[]={"S","ID", "S_S" ,"LENGHT","DATA1", "DATA2","CHECKSUM","#"};
CHAR *PACKAGE_CONFIG[]={"S","ID", "C_F" ,"LENGHT","ID_", "DEVICE","SENSOR","#"};
CHAR NHIETDO1[]="27";
CHAR NHIETDO2[]="27";
CHAR ID_[]="0";
CHAR TEMP_CHAR[]="0";
UNSIGNED INT8 KYTU[30], VT=0,TTNHAN=0;   
//--------------------------------------------------------------------//
#INT_RDA
VOID NGAT()
{   
   KYTU[VT] = GETC ();

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
   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CHON ID: ");

   WHILE (TT_STT)
   {
      IF (INPUT (BT2_PIN) == 0) //NEU NUT BAM DUOC BAM
      {
         ID_NODE ++;
         IF (ID_NODE > 15) ID_NODE = 0;
         DELAY_MS (300);
         ITOA (ID_NODE, 10, ID_);
         LCD_GOTOXY (7, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, ID_);
         DELAY_MS (1);
         OUTPUT_TOGGLE (PIN_D0);
      }
   }
}

VOID CONFIG_DEVICE()
{
   TT_STT = 1;
   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CHON DEVICE: ");

   WHILE (TT_STT)
   {
      IF (!INPUT (BT2_PIN)) //NEU NUT BAM DUOC BAM
      {
         STT_DEVICE ++;
         IF (STT_DEVICE > 7) STT_DEVICE = 0;
         DELAY_MS (300);
         ITOA (STT_DEVICE, 10, TEMP_CHAR);
         LCD_GOTOXY (7, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (1);
         PRINTF (LCD_PUTC, " TT ");
         DELAY_MS (1);
         ITOA (TT_DEVICE[STT_DEVICE], 10, TEMP_CHAR);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (1);
         OUTPUT_TOGGLE (PIN_D0);
      }

      ELSE IF (!INPUT (BT3_PIN))
      {
         TT_DEVICE[STT_DEVICE] = ~TT_DEVICE[STT_DEVICE];
         LCD_GOTOXY (12, 2) ;
         DELAY_MS (300);
         ITOA (TT_DEVICE[STT_DEVICE], 10, TEMP_CHAR);
         PRINTF (LCD_PUTC, TEMP_CHAR);
      }

   }

}

VOID RESET_CONFIG()
{
   ID_NODE = 0;
   //TT_SENSOR = {0, 0, 0, 0, 0, 0, 0, 0};
   //TT_DEVICE = {0, 0, 0, 0, 0, 0, 0, 0};
}

VOID BUTT_OKE()
{
   TT_FUN = 0;
   TT_STT = 0;
}

VOID SELLECT_FUN()
{
   SWITCH (CONFIG_FUN)
   {
      CASE 0:
      CHON_ID ();
      BREAK;

      CASE 1:
      // CONFIG DEVICE
      CONFIG_DEVICE () ;
      BREAK;

      CASE 2:
      //CONFIG_SENSOR ();
      
      LCD_GOTOXY (10, 2) ;
      DELAY_MS (10);
      PRINTF (LCD_PUTC, "CASE1");
      BREAK;

      CASE 3:
      RESET_CONFIG ();
      BREAK;
   }
}

VOID BUTT_FUN()
{
   TT_FUN = 1;

   // HIEN THI LCD
   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CASE: ");

   WHILE (TT_FUN)
   {
      IF (INPUT (BT2_PIN) == 0) //NEU NUT BAM DUOC BAM
      {
         CONFIG_FUN ++;
         IF (CONFIG_FUN > 3) CONFIG_FUN = 0;
         DELAY_MS (300);
         
         //HIEN THI
         LCD_GOTOXY (7, 2) ;
         ITOA (CONFIG_FUN, 10, TEMP_CHAR);
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR);
      }
   }

   SELLECT_FUN ();
}

VOID CONFIG_DONE()
{
   IF ( ! TT_CONFIG)
   {
      TT_DEVICE_CHAR = "";
      FOR (INT I = 0; I < 8; I++)
      {
         IF (TT_DEVICE[I])
         {
            ITOA (I, 10, TEMP_CHAR);
            STRCAT (TT_DEVICE_CHAR, TEMP_CHAR);
         }

      }

      TEMP_CHAR = " * ";
      STRCAT (TT_DEVICE_CHAR, TEMP_CHAR);
      PACKAGE_CONFIG[5] = TT_DEVICE_CHAR;
      PACKAGE_CONFIG[1] = ID_;
      
      FOR (INT J = 0; J < 8; J++)
      {
         PRINTF (PACKAGE_CONFIG[J]);
         DELAY_MS (1);
      }

      
      LCD_GOTOXY (1, 1) ;
      DELAY_MS (10);
      PRINTF (LCD_PUTC, "CONFIG DONE");
      LCD_GOTOXY (1, 2) ;
      DELAY_MS (10);
      PRINTF (LCD_PUTC, TT_DEVICE_CHAR);
      PACKAGE[1] = ID_;
   }
}

VOID QUET_PHIM()
{
   
   IF (INPUT (BT1_PIN) == 0) //NEU NUT BAM DUOC BAM
   {
      LCD_GOTOXY (1, 1) ;
      DELAY_MS (10);
      PRINTF (LCD_PUTC, "BT1");
      FOR (INT I = 0; I < 5; I++) // SAU 10S VAN CON NHAN NUT
      {
         IF (INPUT (BT1_PIN) == 0)
         {
            DELAY_MS (1000);

            IF (I == 4)
            {
               //CONFIG NODE
               TT_CONFIG = ~TT_CONFIG; // VAO TRANG THAI CONFIG
               PRINTF (LCD_PUTC, "-- > CONFIG");
               CONFIG_DONE ();
            }
         }

         ELSE // NHAN NUT < 10S
         {
            BUTT_OKE (); //OKE
            I = 10; // THOAT FOR
         }
      }
   }
}

#INT_EXT
 VOID NGAT_NGOAI  ()
 {
    //QUET_PHIM ();
   INT I=0;
 }

 VOID XUATLCD ()
 {
    LCD_GOTOXY (1, 1) ;
    DELAY_MS (10);
    PRINTF (LCD_PUTC, KYTU);
    DELAY_MS (1);
 }

 INT ADC_READ (INT KENH)
 {
    SET_ADC_CHANNEL (KENH);
    KQADC = 0;
    FOR (INT I = 0; I < 100; I++)
    {
       KQADC = KQADC + READ_ADC () ;
       DELAY_MS (1);
    }

    KQADC = KQADC / (100 * 2.046);
    RETURN KQADC;
 }

 VOID CHUONG_TRINH_CON  ()
 {
    FOR (INT I = 0; I <= 30; I++)
    {
       OUTPUT_TOGGLE (PIN_D1);
       DELAY_MS (100);
    }
 }

 VOID MAIN ()
 {
    SET_TRIS_D (0X00);
    SET_TRIS_B (0XFF);
    SET_TRIS_E (0);
    SET_TRIS_C (0X80);
    SETUP_ADC (ADC_CLOCK_DIV_8);
    SETUP_ADC_PORTS (SAN0);
    ENABLE_INTERRUPTS (INT_TIMER0);
    ENABLE_INTERRUPTS (INT_EXT); //CHO PHEP NGAT NGOAI
    ENABLE_INTERRUPTS (INT_EXT_H2L); //NGAT XAY RA KHI CO XUNG TU CAO XUONG THAP
    ENABLE_INTERRUPTS (INT_RDA);
    ENABLE_INTERRUPTS (GLOBAL);
    LCD_INIT (); // KHOI TAO LCD
    ID_NODE = 0;
    TT_CONFIG = 0;
    OUTPUT_D (0X00) ;
    TTNHAN = 0;

    WHILE (TRUE)
    {
       //AN1 = ADC_READ (1) ;
       AN0 = ADC_READ (0) ;

       IF (TT_CONFIG)
       {
          BUTT_FUN (); // GOI HAM CHON LENH (SWITCH CASE)
       }

       CHUONG_TRINH_CON ();

       IF (AN0 > 26)
       {
          ITOA (AN0, 10, NHIETDO1);
          PACKAGE[4] = NHIETDO1;
          ITOA (AN1, 10, NHIETDO2);
          PACKAGE[5] = NHIETDO2;
          
          FOR (INT I = 0; I < 8; I++)
          {
             PRINTF (PACKAGE[I]);
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
