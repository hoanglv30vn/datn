
#INCLUDE <thuvien.c>

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
      TT_CONTROL = ~TT_CONTROL;
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

 VOID NGAT_NGOAI ()
 {
    QUET_PHIM ();
 }

 #INT_RDA
 VOID NGAT ()
 {
    KYTUCHAR[VT] = GETCH ();

    IF (KYTUCHAR[VT] == '.')
    {
       KYTUCHAR[VT] = '\0';
       VT = 0;
       TTNHAN = 1;
    }

    ELSE
    VT++;
 }

 VOID XUATLCD  ()
 {
    LCD_GOTOXY (1, 1) ;
    DELAY_MS (10);
    PRINTF (LCD_PUTC, KYTUCHAR);
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

 VOID CHUONG_TRINH_CON ()
 {
    FOR (INT I = 0; I <= 30; I++)
    {
       OUTPUT_TOGGLE (PIN_D1);
       DELAY_MS (100);
    }
 }

 VOID MAIN  ()
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
    TT_CONTROL = 1;
    OUTPUT_D (0X00);
    TTNHAN = 0;
    
    
    
    WHILE (TRUE)
    {
       //AN1 = ADC_READ (1) ;
       //AN0 = ADC_READ (0) ;

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
          WHILE (!TT_CONFIG)
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
                KYTU = 0;
                //TEMP_CHAR = 'K';
                //ID_NODE_NHAN = KYTU[1] - 48;
                //ID_DEVICE_NHAN = KYTU[2] - 48 + 64;
                //TT_DEVICE_NHAN = KYTU[3] - 48; // - 48 ASCII -- > S?. + 64 -- > PORT_D (D0 = 64)
                XUATLCD ();
                
                /* LAY TOKEN DAU TIEN */
                TEMP_CHAR = "_";
                CHAR * TOKEN;
                TOKEN = STRTOK (KYTUCHAR, TEMP_CHAR);
                
                /* DUYET QUA CAC TOKEN CON LAI */
                
                LCD_GOTOXY (1, 2) ;
                WHILE (TOKEN != NULL)
                {                
                   SWITCH(KYTU)
                   {
                     CASE 0:
                     ID_NODE_NHAN = ATOI(TOKEN);  
                     BREAK;
               
                     CASE 1:
                     ID_DEVICE_NHAN =  ATOI(TOKEN) + 64 ;
                     BREAK;
               
                     CASE 2:
                     TT_DEVICE_NHAN =  ATOI(TOKEN);                 
                     BREAK;
               
                   
                   }
                  //PRINTF (LCD_PUTC, TOKEN);   
                  DELAY_MS (1);                      
                  TOKEN = STRTOK(NULL, TEMP_CHAR);
                  KYTU++;     
                
                }
                IF (ID_NODE_NHAN == ID_NODE)
                {
                   OUTPUT_BIT (ID_DEVICE_NHAN, TT_DEVICE_NHAN);
                }
             }
          }
       }
    }
 }

