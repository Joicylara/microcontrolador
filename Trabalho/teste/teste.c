//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\lcdI2C\lcd.h"

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

int32 fosc = 6000000;
#define P_ECHO PIN_D0
#define P_TRIG PIN_D1
#include "HCSR04.c"

float distancia = 0;

void main() {   
   lcd_init(0x4E,16,2);
   lcd_backlight_led(ON); //Enciende la luz de Fondo
   HCSR04_init();
  
    while (TRUE) { 
      lcd_clear();  //Limpia el LCD
      distancia = HCSR04_get_distance();
      // Envio de Strings al LCD usando la funci�n printf
      printf(lcd_putc, "\fTeste sensor"); 
      delay_ms(1000); 
      printf(lcd_putc, "\fDis: ");
      printf(lcd_putc, "%.2f", distancia);

      delay_ms(1000); 
   
      
    
   
      
   
   
   }    
}
