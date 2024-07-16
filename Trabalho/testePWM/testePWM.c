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
 unsigned int i;
void setup_pwm() {
    
    setup_timer_2(T2_DIV_BY_16, 255, 1); 
    setup_ccp1(CCP_PWM); 
}

void set_cooler_speed(unsigned int8 speed) {
    
    set_pwm1_duty(speed);
}

void main() {
    setup_pwm();
    
     while(true) {
      for(i=1; i<255; i++ ){
        set_cooler_speed(i); 
        delay_ms(100); 
      }
      for(i=255; i>2; i-- ){
        set_cooler_speed(i); 
        delay_ms(100); 
      }
     }
}

