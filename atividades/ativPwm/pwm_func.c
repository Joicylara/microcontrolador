

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

unsigned int8 ton[50]={
    0,8,16,24,32,40,48,56,63,71,79,86,94,101,109,116,123,130,137,143,150,156,163,
    169,175,180,186,191,196,201,206,211,215,219,223,227,231,234,237,240,243,255};

unsigned int8 ton2[50]={
    255,243,240,237,234,231,227,223,219,215,211,206,201,196,191,186,180,175,169,
    163,156,150,143,137,130,123,116,109,101,94,86,79,71,63,56,48,40,32,24,16,8,0};
        

void main()
{

   unsigned int8 i;
   unsigned int16 t;
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_4,249,1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(0);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   while(true){
      for(i=0;i<50;i++){
        set_pwm1_duty(ton[i]);
        delay_us(250);
      }
      for(i=0;i<50;i++){
        set_pwm1_duty(ton2[i]);
        delay_us(250);
     }
   }
}
