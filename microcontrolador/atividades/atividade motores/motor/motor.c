//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\motor\motor.h"

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

#int_EXT
void  EXT_isr(void) 
{
   incr = incr * (-1);
}

unsigned int8 posicao[4] =  {1, 2, 4, 8};
signed int8 passo = 0;


void main()
{

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);

   enable_interrupts(INT_EXT);
   enable_interrupts(GLOBAL);


   while(true){
      passo = passo + incr;
      if(passo > 3)passo = 0;
      if(passo < 0)passo = 3;
      
      output_D(posicao[passo]);
      delay_ms(500);
   }

}
