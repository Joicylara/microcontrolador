//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\Prova1\Questão3_Joicy\questao3_Joicy.h"

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

#ifndef lcd_enable
 #define lcd_enable pin_E1 // pino enable do LCD
 #define lcd_rs pin_E2 // pino rs do LCD
 //#define lcd_rw pin_e2 // pino rw do LCD
 #define lcd_d4 pin_d4 // pino de dados d4 do LCD
 #define lcd_d5 pin_d5 // pino de dados d5 do LCD
 #define lcd_d6 pin_d6 // pino de dados d6 do LCD
 #define lcd_d7 pin_d7 // pino de dados d7 do LCD
#endif

#include "mod_lcd.c"



void main()
{
 unsigned int16 temperatura=0;
 float tensao=0;
 
 // configuração do AD
 setup_adc_ports(AN0);
 setup_adc(ADC_CLOCK_DIV_16);
 
 setup_psp(PSP_DISABLED);
 setup_spi(SPI_SS_DISABLED);
 setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
 setup_psp(PSP_DISABLED);
 setup_spi(SPI_SS_DISABLED);
 setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
 setup_timer_1(T1_DISABLED);
 setup_timer_2(T2_DISABLED,0,1);
 setup_comparator(NC_NC_NC_NC);
 setup_vref(FALSE);
 
 lcd_ini();
 delay_ms(50);
 
 set_adc_channel(0);

 delay_us(50);
 
 
 
 
 while(true){
    temperatura = read_adc();
    delay_us(50);
    
    tensao =(float)temperatura*5/1023.;
    printf(lcd_escreve,"\fTensao (V) = %1.2f\r\n",tensao);
    printf(lcd_escreve,"\nTemp = %Lu\n\r", temperatura);
    delay_ms(2000);
 
    
 }
}


