//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\senha\senha.h"

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

#use delay(clock=6000000)

#use i2c(Master,Fast=100000, sda=PIN_C4, scl=PIN_C3,force_sw)  
#include "i2c_Flex_LCD.c"  

void main() {  
int i=0; 
lcd_init(0x4E,16,2);
lcd_backlight_led(ON); //Enciende la luz de Fondo
  
 while (TRUE) { 
   lcd_clear();  //Limpia el LCD

   // Envio de Strings al LCD usando la funci�n printf
   printf(lcd_putc, "\f Digite a senha:"); 
   delay_ms(1000); 
   printf(lcd_putc, "\nteste"); 
   delay_ms(1000); 
   

   // Limpia el LCD 
   printf(lcd_putc, "\f"); 
   delay_ms(500); 

  
   // Ultima columna y fila  2
   //Borro la fila 2 con back space
   lcd_gotoxy(20, 2);        

   // Backspace over 2nd line. 
   for(i = 0; i < lcd_total_columns; i++) 
      { 
       printf(lcd_putc," \b\b"); 
       delay_ms(100); 
      } 

   //printf(lcd_putc,   " es GRATIS!!!!!!");  
   //delay_ms(3000); 



   }    
}