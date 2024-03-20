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
                //Used to set the reserved FUSE bits

#use delay(clock=6000000)


void notaDo();
void notaRE();
void notaMI();
void notaFA();

void main(void) {

    while(1) {
    
      delay_ms(1000);
      notaDO();
      delay_ms(300);
      notaRE();
      delay_ms(300);
      notaMI();
      delay_ms(300);
      notaFA();
      delay_ms(100);
      notaFA();
      delay_ms(100);
      notaFA();
      delay_ms(100);
      notaFA();
      
      delay_ms(1000);
      
      // segunda parte
      
      notaDO();
      delay_ms(300);
      notaRE();
      delay_ms(300);
      notaDO();
      delay_ms(300);
      notaRE();
      delay_ms(100);
      notaRE();
      delay_ms(100);
      notaRE();
      delay_ms(100);
      
      
    }
}
    
   void notaDo(){
   
      // DO D3=L4
        output_high(PIN_D3);  
        delay_ms(500);         
        output_low(PIN_D3);  

   }
   
   void notaRE(){
      // RE D3, D4 = L4, L5
        output_high(PIN_D3); 
        output_high(PIN_D4);
        delay_ms(500);         
        output_low(PIN_D3);
        output_low(PIN_D4);
   }
   
   void notaMI(){
       // MI D3, D4, D5 = L4, L5, L6
        output_high(PIN_D3); 
        output_high(PIN_D4);
        output_high(PIN_D5);
        delay_ms(500);         
        output_low(PIN_D3);
        output_low(PIN_D4);
        output_low(PIN_D5);
   
   }
   
   void notaFA(){
      // FA D3, D4, D5, D6 = L4, L5, L6, L7
        output_high(PIN_D3); 
        output_high(PIN_D4);
        output_high(PIN_D5);
        output_high(PIN_D6);
        delay_ms(500);         
        output_low(PIN_D3);
        output_low(PIN_D4);
        output_low(PIN_D5);
        output_low(PIN_D6);
   }

