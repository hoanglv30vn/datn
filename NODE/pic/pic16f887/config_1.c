
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
   TEMP_CHAR = "0";
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
         ITOA (ID_GATEWAY[NUM], 10, TEMP_CHAR);
         LCD_GOTOXY (9 + NUM, 2);
         DELAY_MS (10);
         PRINTF (LCD_PUTC, TEMP_CHAR);
         DELAY_MS (300);
      }
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
   *TEMP_CHAR = '\0';
   *TT_DEVICE_CHAR = '\0';
   FOR (INT I = 0; I < 8; I++)
   {
      IF (TT_DEVICE[I])
      {
         ITOA (I, 10, TEMP_CHAR);
         DELAY_MS (1);
         STRCAT (TT_DEVICE_CHAR, TEMP_CHAR);
      }
   }

   // PACKAGE_CONFIG[6] = TT_DEVICE_CHAR;
}

VOID XULYSENSOR_CF()
{
   *TEMP_CHAR = '\0';
   *TEMP_CHAR2 = '\0';
   FOR (INT J = 0; J < 5; J++)
   {
      IF (TT_SENSOR[J])
      {
         ITOA (J, 10, TEMP_CHAR);
         DELAY_MS (1);
         STRCAT (TEMP_CHAR2, TEMP_CHAR);
      }
   }

   //PACKAGE_CONFIG[7] = TEMP_CHAR3;
}

VOID CONFIG_DONE()
{
   TT_FUN = 0;
   TT_STT = 0;
   *TEMP_CHAR3 = "\0";
   FOR (int j = 0; j < 4; j++)
   {
      ITOA (ID_GATEWAY[j], 10, TEMP_CHAR);
      DELAY_MS (1);
      STRCAT (TEMP_CHAR3, TEMP_CHAR);
   }   
   
   PACKAGE_CONFIG[1] = TEMP_CHAR3;
   DELAY_MS (2);
   PACKAGE_CONFIG[2] = ID_;
   DELAY_MS (2);
   TT_DEVICE_CHAR = "";
   XULYDEVICE_CF ();
   XULYSENSOR_CF ();
   PACKAGE_CONFIG[5] = TT_DEVICE_CHAR;
   DELAY_MS (2);
   PACKAGE_CONFIG[6] = TEMP_CHAR2;
   //TINH DO DAI -->
   LEN_PACKAGES = 0;
   PACKAGE_CONFIG[3] = "12"; //DO DAI CUA LENGHT C? ?? DAI = 2
   FOR (J = 0; J < 9; J++)
   {
      LEN_PACKAGES += strlen(PACKAGE_CONFIG[J]);
   }   
   LEN_PACKAGES = LEN_PACKAGES+7; //7 @
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
