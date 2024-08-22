//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\semafaro.h"

#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=6000000)

void passo1();
//void passo2();
void passo3();
void passo4();
void passo5();

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

   while(true){
    passo1();
      if(!input(PIN_B0)){
         output_low(PIN_D0); // Sinal verde para os carros
         output_low(PIN_D7);
         delay_ms(10000);
         passo3();
         passo4();
         passo5();
         delay_ms(10000); //passo7
      }
     
      //passo2();
      //passo1();
   

   }   
}
// CARRO

// D0 - verde
// D1 - amarelo
// D2 - vermelho

//PEDESTRE

// D6 - verde
// D7 - vermelho
// B0 - botão


void passo1(){
   
   output_low(PIN_D0); // Sinal verde para os carros
   output_low(PIN_D7); // Sinal vermelho para pedestre
}

//void passo2(){

   
//}

void passo3(){
   
   output_high(PIN_D0);  // Sinal verde para os carros
   output_low(PIN_D1); // Sinal amarelo p/ os carros
   output_low(PIN_D7); // Sinal vermelho para pedestre
   delay_ms(3000);  
}

void passo4(){

   output_high(PIN_D1); // Sinal amarelo p/ os carros
   output_low(PIN_D2); // Sinal vermelho p/ os carros
   delay_ms(1000);
   output_high(PIN_D7); // Sinal vermelho para pedestre
   output_low(PIN_D6); // Sinal verde para pedestre
}

void passo5() {
    int i;
    delay_ms(10000); 
    output_high(PIN_D6); // Sinal verde para pedestre

    // Piscar o LED de pedestre por 5 segundos
    for (i = 0; i < 5; i++) {
        output_low(PIN_D7); // Liga sinal vermelho para pedestre 
        delay_ms(200);
        output_high(PIN_D7); // Desliga sinal vermelho para pedestre
        delay_ms(800);
    }
    delay_ms(200);
    output_low(PIN_D7); 
    output_high(PIN_D2);
    output_low(PIN_D0);
}



