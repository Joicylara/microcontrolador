//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\teclado\teclado.h"

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

#use i2c(Master,Fast=100000, sda=PIN_C4, scl=PIN_C3,force_sw)  
#include "i2c_Flex_LCD.c" 

#include "kbd_ext_board2.c"
void main()
{
 unsigned char tmp;
 setup_adc_ports(NO_ANALOGS);
 setup_adc(ADC_OFF);
 setup_psp(PSP_DISABLED);
 setup_spi(SPI_SS_DISABLED);
 setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
 setup_timer_1(T1_DISABLED);
 setup_timer_2(T2_DISABLED,0,1);
 setup_comparator(NC_NC_NC_NC);
 setup_vref(FALSE);
 lcd_init(0x4E,16,2); // Inicializa LCD
 delay_ms(10);
 printf (lcd_putc,"\fIFMT ... 2022");
 delay_ms(1000);
 printf (lcd_putc,"\f TECLADO ");
 delay_ms(2000);
 while (true)
 {
 
 //-------------------------------------------
 tmp = tc_tecla(1500); // ms
 //-------------------------------------------
 if(tmp!=255){
 printf (lcd_putc,"\f Botton %c",tmp);
 }
 else{ printf (lcd_putc,"\f TECLADO L");
 
 }
 
 
 } // laço infinito
}
