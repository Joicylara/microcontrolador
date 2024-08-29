//#include "C:\Users\IFMT\OneDrive\Faculdade\microcontrolador\atividades\testeTesteLed.h"

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

  
    TRISB.F1 = 0;  // Configura o RB1 como sa�da

    while(1) {
        PORTB.F1 = 1;   // Liga o LED (RB1)
        delay_ms(500);  // Aguarda 500 milissegundos
        PORTB.F1 = 0;   // Desliga o LED (RB1)
        delay_ms(500);  // Aguarda mais 500 milissegundos
    }

}
