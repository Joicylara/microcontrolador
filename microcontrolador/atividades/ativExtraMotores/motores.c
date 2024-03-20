//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\ativExtraMotores\motores.h"

#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=20000000)


signed int8 incr = 1;
signed int8 cont = 0;
unsigned int8 posicao[4] =  {1, 2, 4, 8};
signed int8 passo = 0;
unsigned int16 valor_p;

#int_EXT
void  EXT_isr(void) 
{
   incr = incr * (-1);
}

#int_TIMER1
void  TIMER1_isr(void) 
{
   if(cont > valor_p){
      
   }
}

 
/*void Rotation0() //0 Degree
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(800); // pulse of 800us
         output_low(PIN_D0);
         delay_us(19200);
         }
    }
    
    void Rotation90() //90 Degree
   {            
   unsigned int i;
   for(i=0;i<50;i++)
      {                         //  180o   0o
         output_high(PIN_D0);    // 2200 - 800 = 1400     90o =  700
         delay_us(1500); // pulse of 1500us
         output_low(PIN_D0);
         delay_us(18500);
      }
   }

void Rotation180() //180 Degree
   {
   unsigned int i;
   for(i=0;i<50;i++)
      {
         output_high(PIN_D0);
         delay_us(2200); // pulse of 2200us
         output_low(PIN_D0);
         delay_us(17800);
      }
   }
   
   void motorServo(){
      Rotation180(); // 180 graus
      delay_ms(4000);
      Rotation90();  // 90 graus
      delay_ms(4000);
      Rotation0();   // 0 graus
      delay_ms(4000);
   }*/
   

void main()
{

   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   //enable_interrupts(INT_TIMER0);
   enable_interrupts(INT_TIMER1);
   //enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);
  

   set_adc_channel(0);
   delay_us(10);

   while(true){
      //motorServo();
      passo = passo + incr;
      if(passo > 3)passo = 0;
      if(passo < 0)passo = 3;
      
      output_D((posicao[passo] << 4) & 0xF0);
      valor_p = read_adc();
      //delay_us(10);
      delay_ms(valor_p);
      
      
      
      
      
    
   }

}
