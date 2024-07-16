#include <16f877a.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,NOPUT,BROWNOUT
#use delay(clock=20M)
#use standard_io(D)

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
      delay_ms(150);
   }
}
