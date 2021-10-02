#INCLUDE <16F887.H>
#DEVICE ADC=10
#INCLUDE <STRING.H>
#INCLUDE <STDLIB.H>
#INCLUDE <STDIO.H>
#INCLUDE <MATH.H>

/*
int atoi(const char *s) : sting --> s� nguy�n
long atol(const char *s) : string --> s� nguy�n d�i
float atof(const char *s) : string --> s� thuc
*/
#FUSES NOWDT, PUT, HS
#USE DELAY(CLOCK=20M)
#USE RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7)



UNSIGNED INT16 KQADC;
INT8 DATA=0;
CHAR NHIETDO[30]="20";
CHAR NHAN='X';

//----------------------------------------------------------------------//
#INT_RDA
VOID NGAT(){
   NHAN = GETC();
   OUTPUT_TOGGLE(PIN_D0);
}
VOID ADC_READ(){
   KQADC = 0;    
   FOR (INT I=0; I<100; I++)
   {
      KQADC=KQADC+READ_ADC();
      DELAY_MS(1);
   }
   KQADC = KQADC/(100*2.046);

}

VOID SS(){
      IF (KQADC > 26){
          OUTPUT_D(0xF0);
          PUTC('O');
          PUTC('N');
          DELAY_MS(200);
      }
      ELSE{
         OUTPUT_D(0x0F);
         PRINTF(KQADC);
         DELAY_MS(200);
         }   

}

VOID MAIN(){
   SET_TRIS_D(0X00);
   SET_TRIS_B(0XF0);
   SETUP_ADC(ADC_CLOCK_DIV_8);
   SETUP_ADC_PORTS(sAN0);
   SET_ADC_CHANNEL(0);     
   OUTPUT_LOW(PIN_D0);
   OUTPUT_D(0X00);
   ENABLE_INTERRUPTS(INT_RDA);
   ENABLE_INTERRUPTS(GLOBAL);
   ENABLE_INTERRUPTS(INT_TIMER0);
   
   
   WHILE(TRUE){
      //OUTPUT_TOGGLE(PIN_D1);
      ADC_READ();
      IF(KQADC>26){
            ITOA(KQADC, 10, NHIETDO );
            PRINTF(NHIETDO);
            DELAY_MS(200);
      }
      DELAY_MS(200);
   } 
}

