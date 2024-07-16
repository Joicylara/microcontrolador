#include <16f877a.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,NOPUT,BROWNOUT
#use delay(clock=20M)
#use standard_io(A)
#use standard_io(D)

#define led_1 PIN_A0
#define led_2 PIN_A1
#define led_3 PIN_A2
#define led_4 PIN_A3

int32 fosc = 20000000;
#define P_ECHO PIN_D0
#define P_TRIG PIN_D1

#define LCD_DB4  PIN_D4
#define LCD_DB5  PIN_D5
#define LCD_DB6  PIN_D6
#define LCD_DB7  PIN_D7
#define LCD_RS   PIN_D2
#define LCD_E    PIN_D3
#include <LCD_16X2.c>
#include <HCSR04.c>

float distancia = 0;                                     // Variable para almacenar la distancia

void main()
{
   output_low(led_1);
   output_low(led_2);
   output_low(led_3);
   output_low(led_4);
   HCSR04_init();                                        // Inicializa el sensor ultrasonico
   lcd_init();                                           // Inicializa la LCD
   
   while(true)
   {
      distancia = HCSR04_get_distance();                 // Obtiene la distancia y la almacena
      lcd_clear();
      lcd_gotoxy(1,1);
      lcd_putc("Sensor HC-SR04");
      lcd_gotoxy(1,2);
      printf(lcd_putc,"Dist: %0.2f cm", distancia);      // Imprime la distancia
      
      output_low(led_1);
      output_low(led_2);
      output_low(led_3);
      output_low(led_4);
      
      if(distancia <= 15)
      {
         output_high(led_1);
      }
      if(distancia <= 12)
      {
         output_high(led_2);
      }
      if(distancia <= 8)
      {
         output_high(led_3);
      }
      if(distancia <= 4)
      {
         output_high(led_4);
      }
      delay_ms(150);
   }
}
