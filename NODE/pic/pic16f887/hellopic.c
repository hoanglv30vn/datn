
#INCLUDE <16F887.H>
#DEVICE ADC=10
#INCLUDE <STRING.H>
#INCLUDE <STDLIB.H>
#INCLUDE <STDIO.H>
//#INCLUDE <CONFIG_NODE.C>
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

UNSIGNED INT16 KQADC,AN0, AN1;
UNSIGNED INT8 CONFIG_FUN=0, ID_NODE = 0, STT_DEVICE=0, STT_SENSOR=0;
UNSIGNED INT8 KYTU[30], VT=0,TTNHAN=0; 
UNSIGNED INT8 ID_NODE_NHAN, ID_DEVICE_NHAN, TT_DEVICE_NHAN;
//UNSIGNED INT8 ID_SENSOR_NHAN, TT_SENSOR_NHAN;
INT1 TT_CONFIG=0, TT_CONFIG_DONE=0, TT_FUN=0, TT_STT=0;
INT1 TT_DEVICE[8]={0, 1, 1, 0, 1, 0, 1, 1};
INT1 TT_SENSOR[8]={1, 1, 1, 1, 0, 0, 0, 0};
CHAR *TT_DEVICE_CHAR[]=" ";
CHAR *TT_SENSOR_CHAR[]=" ";
CHAR *PACKAGE_NHIETDO[]={"*","ID_GW", "ID_NODE","LENGHT", "S_S" ,"TT_cambien","#"};

CHAR *PACKAGE_CONFIG[]={"*","ID_GW" ,"ID_NODE", "LENGHT","C_F", "DEVICE1234","SENSOR1234","#"};
CHAR *ID_[]="0";
CHAR *ID_GW[]= "0000";
UNSIGNED INT8 ID_GATEWAY[4] = {0,0,0,0};
CHAR *TEMP_CHAR[]="0";
CHAR *TEMP_CHAR2[]="0"; 
CHAR *TEMP_CHAR3[]="0"; 
UNSIGNED INT8 LEN_PACKAGES = 0;

CHAR NHIETDO1[]="27";
CHAR NHIETDO2[]="27";
//--------------------------------------------------------------------//
VOID CHON_ID()
{
   // TT_CONFIG_DONE;
   TT_CONFIG_DONE = 0;
   TT_STT = 1;
   LCD_GOTOXY (1, 2) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "ID:             ");

   WHILE (TT_STT)
   {
      IF (INPUT (BT2_PIN) == 0) //NEU NUT BAM DUOC BAM
      {
         ID_NODE ++;
         IF (ID_NODE > 15) ID_NODE = 0;
         DELAY_MS (300);
         ITOA (ID_NODE, 10, ID_);
         LCD_GOTOXY (9, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, ID_);
         DELAY_MS (1);
         OUTPUT_TOGGLE (PIN_D0);
      }
   }
}

VOID CONFIG_DEVICE()
{
   TT_CONFIG_DONE = 0;
   TT_STT = 1;
   LCD_GOTOXY (1, 2) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "DEVICE:           ");

   WHILE (TT_STT)
   {
      IF (!INPUT (BT2_PIN)) //NEU NUT BAM DUOC BAM
      {
         STT_DEVICE ++;
         IF (STT_DEVICE > 7) STT_DEVICE = 0;
         DELAY_MS (300);
         ITOA (STT_DEVICE, 10, TEMP_CHAR);
         LCD_GOTOXY (9, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (1);
         PRINTF (LCD_PUTC, " : ");
         DELAY_MS (1);
         ITOA (TT_DEVICE[STT_DEVICE], 10, TEMP_CHAR);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (1);
         OUTPUT_TOGGLE (PIN_D0);
      }

      ELSE IF (!INPUT (BT3_PIN))
      {
         TT_DEVICE[STT_DEVICE] = ~TT_DEVICE[STT_DEVICE];
         LCD_GOTOXY (13, 2) ;
         DELAY_MS (300);
         ITOA (TT_DEVICE[STT_DEVICE], 10, TEMP_CHAR);
         PRINTF (LCD_PUTC, TEMP_CHAR);
      }
   }
}

VOID CONFIG_SENSOR ()
{
   TT_CONFIG_DONE = 0;
   TT_STT = 1;
   LCD_GOTOXY (1, 2) ;
   DELAY_MS (10);  
   PRINTF (LCD_PUTC, "SENSOR:         ");

   WHILE (TT_STT)
   {
      IF (!INPUT (BT2_PIN)) //NEU NUT BAM DUOC BAM
      {
         STT_SENSOR ++;
         IF (STT_SENSOR > 3) STT_SENSOR = 0;
         DELAY_MS (300);
         ITOA (STT_SENSOR, 10, TEMP_CHAR);
         LCD_GOTOXY (9, 2) ;
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (1);
         PRINTF (LCD_PUTC, " : ");
         DELAY_MS (1);
         ITOA (TT_SENSOR[STT_SENSOR], 10, TEMP_CHAR);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (1);
         OUTPUT_TOGGLE (PIN_D0);
      }

      ELSE IF (!INPUT (BT3_PIN))
      {
         TT_SENSOR[STT_SENSOR] = ~TT_SENSOR[STT_SENSOR];
         LCD_GOTOXY (13, 2) ;
         DELAY_MS (300);
         ITOA (TT_SENSOR[STT_SENSOR], 10, TEMP_CHAR);
         PRINTF (LCD_PUTC, TEMP_CHAR);
      }
   }
}

VOID NHAPID_GW()
{
   UNSIGNED INT8 NUM = 0;
   ID_GW = "\0";
   TEMP_CHAR3 = "0";
   TT_CONFIG_DONE = 0;
   TT_STT = 1;
   LCD_GOTOXY (1, 2) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "ID_GW:  0000 ");
   LCD_GOTOXY (1, 1) ;
   PRINTF (LCD_PUTC, "        _    ");
   //ID_GW = "1234";    

   WHILE (TT_STT)
   {
      IF (!INPUT (BT2_PIN)) //NEU NUT BAM DUOC BAM
      {
         
         NUM++;
         NUM = NUM % 4;
         LCD_GOTOXY (5 + NUM, 1);
         PRINTF (LCD_PUTC, "    _    ");
         DELAY_MS (300); 
      }

      ELSE IF (!INPUT (BT3_PIN))
      {
         ID_GATEWAY[NUM]++;
         ID_GATEWAY[NUM] = ID_GATEWAY[NUM] % 10;
         ITOA (ID_GATEWAY[NUM], 10, TEMP_CHAR3);
         LCD_GOTOXY (9 + NUM, 2);
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR3);
         DELAY_MS (300);
      }
   }

   FOR (NUM = 0; NUM < 4; NUM++)
   {
      ITOA (ID_GATEWAY[NUM], 10, TEMP_CHAR3);
      DELAY_MS (1);
      STRCAT (ID_GW, TEMP_CHAR3);
   }
}

VOID BUTT_OKE()
{
   TT_CONFIG_DONE = 0;
   TT_FUN = 0;
   TT_STT = 0;
}

VOID SELLECT_FUN()
{
   TT_CONFIG_DONE = 0;

   SWITCH (CONFIG_FUN)
   {
      CASE 0:
      CHON_ID ();
      BREAK;

      CASE 1:
      // CONFIG DEVICE
      CONFIG_DEVICE ();
      BREAK;

      CASE 2:
      CONFIG_SENSOR ();
      BREAK;

      CASE 3:
      NHAPID_GW ();
      BREAK;
   }
}

VOID BUTT_FUN()
{
   TT_FUN = 1;
   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CONFIG:        ");

   // HIEN THI LCD
   LCD_GOTOXY (1, 2) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CASE:          ") ;

   WHILE (TT_FUN)
   {
      IF (INPUT (BT2_PIN) == 0) //NEU NUT BAM DUOC BAM
      {
         CONFIG_FUN ++;
         CONFIG_FUN = CONFIG_FUN % 4; //IF (CONFIG_FUN > 3) CONFIG_FUN = 0;
         DELAY_MS (300);

         //HIEN THI
         LCD_GOTOXY (6, 2) ;
         ITOA (CONFIG_FUN, 10, TEMP_CHAR);
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR);

         SWITCH (CONFIG_FUN)
         {
            CASE 0:
            PRINTF (LCD_PUTC, " - ID         ");
            BREAK;

            CASE 1:
            PRINTF (LCD_PUTC, " - DEVICES    ");
            BREAK;
            
            CASE 2:
            PRINTF (LCD_PUTC, " - SENSORS    ");
            BREAK;
            
            CASE 3:
            PRINTF (LCD_PUTC, " - ID - GW:    ");
            BREAK;
         }
      }
   }

   //////
   IF (!TT_CONFIG_DONE)
   {
      SELLECT_FUN ();
   }
}

VOID XULYDEVICE_CF()
{
   * TEMP_CHAR2 = '\0';
   * TT_DEVICE_CHAR = '\0';
   FOR (INT I = 0; I < 8; I++)
   {
      IF (TT_DEVICE[I])
      {
         ITOA (I, 10, TEMP_CHAR2);
         DELAY_MS (1);
         STRCAT (TT_DEVICE_CHAR, TEMP_CHAR2);
      }
   }

   // PACKAGE_CONFIG[6] = TT_DEVICE_CHAR;
}

VOID XULYSENSOR_CF()
{
   * TEMP_CHAR2 = '\0';
   * TEMP_CHAR3 = '\0';
   FOR (INT J = 0; J < 5; J++)
   {
      IF (TT_SENSOR[J])
      {
         ITOA (J, 10, TEMP_CHAR2);
         DELAY_MS (1);
         STRCAT (TEMP_CHAR3, TEMP_CHAR2);
      }
   }

   //PACKAGE_CONFIG[7] = TEMP_CHAR3;
}

VOID CONFIG_DONE()
{
   TT_FUN = 0;
   TT_STT = 0;
   PACKAGE_CONFIG[1] = ID_GW;
   DELAY_MS (2);
   PACKAGE_CONFIG[2] = ID_;
   DELAY_MS (2);
   TT_DEVICE_CHAR = "";
   TT_SENSOR_CHAR = "";
   XULYDEVICE_CF ();
   XULYSENSOR_CF ();
   PACKAGE_CONFIG[5] = TT_DEVICE_CHAR;
   DELAY_MS (2);
   PACKAGE_CONFIG[6] = TEMP_CHAR3;
   //TINH DO DAI -->
   LEN_PACKAGES = 0;
   PACKAGE_CONFIG[3] = "12"; //DO DAI CUA LENGHT C� �� DAI = 2
   FOR (INT J = 0; J < 9; J++)
   {
      LEN_PACKAGES += strlen(PACKAGE_CONFIG[J]);
   }   
   LEN_PACKAGES = LEN_PACKAGES+6; //7 @
   ITOA (LEN_PACKAGES, 10, TEMP_CHAR);
   PACKAGE_CONFIG[3] = TEMP_CHAR;
   
   FOR ( J = 0; J < 8; J++)
   {
      PRINTF (PACKAGE_CONFIG[J]);
      PRINTF ("@");
   }

   /*
   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   FOR (J = 0; J < 9; J++)
   {
      PRINTF (LCD_PUTC, PACKAGE_CONFIG[J]);
   }
   */

   LCD_GOTOXY (1, 1) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CONFIG DONE        ") ;
   LCD_GOTOXY (1, 2) ;
   DELAY_MS (10);
   PRINTF (LCD_PUTC, "CONFIG DONE        ") ;
   PACKAGE_NHIETDO[1] = ID_;
   TT_CONFIG_DONE = 0;
}

//--------------------------------------------------------------------//
VOID QUET_PHIM()
{
   INT BDT = 0;

   WHILE (!INPUT (BT1_PIN)) //NEU NUT BAM DUOC BAM
   {
      IF (TMR1IF)
      {
         OUTPUT_TOGGLE (PIN_D2);
         TMR1IF = 0; SET_TIMER1 (3036); BDT++;
      }
   }

   IF (BDT > 20)
   {
      //CONFIG NODE
      TT_CONFIG = ~TT_CONFIG; // VAO TRANG THAI CONFIG
      //CONFIG_DONE ();
      TT_CONFIG_DONE = 1;
      TT_FUN = 0;
   }

   ELSE
   {
      BUTT_OKE (); //OKE
   }
}

#INT_EXT

 VOID NGAT_NGOAI  ()
 {
    QUET_PHIM ();
 }

 #INT_RDA
 VOID NGAT  ()
 {
    KYTU[VT] = GETCH ();

    IF (KYTU[VT] == '.')
    {
       KYTU[VT] = '\0';
       VT = 0;
       TTNHAN = 1;
    }

    ELSE
    VT++;
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
    
    SETUP_TIMER_1 (T1_INTERNAL|T1_DIV_BY_8);
    //SET_TIMER1 (0);
    SET_TIMER1 (3036);
    TMR1IF = 0;
    LCD_INIT (); // KHOI TAO LCD
    ID_NODE = 0;
    TT_CONFIG = 0;
    TT_CONFIG_DONE = 0;
    OUTPUT_D (0X00);
    TTNHAN = 0;
    
    
    
    WHILE (TRUE)
    {
       //AN1 = ADC_READ (1) ;
       AN0 = ADC_READ (0) ;

       IF (TT_CONFIG)
       {
          BUTT_FUN (); // GOI HAM CHON LENH (SWITCH CASE)
       }

       ELSE IF (TT_CONFIG_DONE)
       {
          CONFIG_DONE ();
       }

       
       ELSE
       {

          WHILE ( ! TT_CONFIG)
          {
             CHUONG_TRINH_CON ();

             IF (AN0 > 26)
             {
                ITOA (AN0, 10, NHIETDO1);
                PACKAGE_NHIETDO[4] = NHIETDO1;
                ITOA (AN1, 10, NHIETDO2);
                PACKAGE_NHIETDO[5] = NHIETDO2;
                
                FOR (INT I = 0; I < 8; I++)
                {
                   PRINTF (PACKAGE_NHIETDO[I]);
                   DELAY_MS (1);
                }

                
                DELAY_MS (1000);
             }

             
             IF (TTNHAN == 1)
             {
                TTNHAN = 0;
                //TEMP_CHAR = 'K';
                ID_NODE_NHAN = KYTU[1] - 48;
                ID_DEVICE_NHAN = KYTU[2] - 48 + 64;
                TT_DEVICE_NHAN = KYTU[3] - 48; // - 48 ASCII -- > S?. + 64 -- > PORT_D (D0 = 64)
                XUATLCD ();
                
                IF (ID_NODE_NHAN == ID_NODE)
                {
                   OUTPUT_BIT (ID_DEVICE_NHAN, TT_DEVICE_NHAN);
                }
             }
          }
       }
    }
 }


