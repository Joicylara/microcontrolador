//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\Trabalho\controle\controle.h"

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

//comunicacao serial
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)

//lcd
#use i2c(Master,Fast=100000, sda=PIN_C4, scl=PIN_C3,force_sw)  
#include "i2c_Flex_LCD.c"

// ultrassonico
int32 fosc = 6000000;
#define P_ECHO PIN_D0
#define P_TRIG PIN_D1
#include "HCSR04.c"

float distancia = 0;

//pwm
unsigned int i;
void setup_pwm() {
    
    setup_timer_2(T2_DIV_BY_16, 255, 1); 
    setup_ccp1(CCP_PWM); 
}

void set_cooler_speed(unsigned int8 speed) {
    
    set_pwm1_duty(speed);
}


void main() {   

   while(true){
   //char received_char;
   float alturaSolicitada = 0;
        printf("Digite a altura desejada");
    // Espera at� receber um caractere pela serial
        alturaSolicitada = getc();

        // Envia de volta o caractere recebido
         putc(alturaSolicitada);
         printf("Altura solicitada: %c\r\n", alturaSolicitada);

         lcd_init(0x4E,16,2);
         lcd_backlight_led(ON); //Enciende la luz de Fondo
         HCSR04_init();
         setup_pwm();
  
  
      lcd_clear();  //Limpia el LCD
      distancia = HCSR04_get_distance();
      // Envio de Strings al LCD usando la funci�n printf
      printf(lcd_putc, "\fAltura atual:"); 
      printf(lcd_putc, "%.2f", distancia);

      delay_ms(1000); 
   
      if (distancia > alturaSolicitada) {
 
      // Se a altura atual for maior que a altura desejada, diminui a velocidade
      set_cooler_speed(100); // Ajuste o valor conforme necess�rio
       
      } else {           
      // Caso contr�rio, aumenta a velocidade
         set_cooler_speed(200); // Ajuste o valor conforme necess�rio
       
      }
      delay_ms(1000);
    }  
}