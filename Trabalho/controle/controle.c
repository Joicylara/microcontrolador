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

#include <stdlib.h>  

#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8, stream=wireless)

int32 fosc = 6000000;
#define P_ECHO PIN_D0
#define P_TRIG PIN_D1
#include "HCSR04.c"

signed int altura = 0;



void main() { 

    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_CLOCK_DIV_2);
    setup_psp(PSP_DISABLED);
    setup_spi(SPI_SS_DISABLED);
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
    setup_timer_1(T1_DISABLED);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
    setup_timer_2(T2_DIV_BY_16, 255, 1); 
    setup_ccp1(CCP_PWM);


    lcd_init(0x4E, 16, 2);
    lcd_backlight_led(ON); // Enciende la luz de Fondo
    HCSR04_init();
    
    altura = (27 - HCSR04_get_distance()/23)*50;
    
        
    lcd_clear();
    
    printf(lcd_putc, "Alt. atual: ");
    printf(lcd_putc, "%u", altura);
    delay_ms(1000);

    char buffer[10]; // buffer para armazenar a string recebida
    int index = 0;
    int alturaDesejada = 0;
    int erro = 0;   
    int velocidadeCooler = 50;

    fprintf(wireless, "Altura desejada: ");
    
    
    do {
        buffer[index] = getc(wireless);
    } while (buffer[index++] != '\n' && buffer[index - 1] != '\r' && index < sizeof(buffer) - 1);

    buffer[index - 1] = '\0'; 

   // Converte a string para um inteiro
    alturaDesejada = atoi(buffer); 
    fprintf(wireless, "\naltura: %u", alturaDesejada);

    set_pwm1_duty(velocidadeCooler);
    delay_ms(500);

    while(true) {
        // topo 4
        // base 27
        altura = HCSR04_get_distance();
        
        if(altura < 0){
         altura = 0;
        }
        
       
        
        lcd_clear();
        printf(lcd_putc, "Alt. atual: ");
        printf(lcd_putc, "%u", altura);
        delay_ms(10);
        printf(lcd_putc, "\nAlt. desej: ");
        printf(lcd_putc, "%u", alturaDesejada);
        delay_ms(10);
        
        //velocidadeCooler = velocidadeCooler + erro;
        if (altura < alturaDesejada && velocidadeCooler<250) {
            velocidadeCooler++;
        }else if (altura < alturaDesejada && velocidadeCooler>1) {
            velocidadeCooler --;
        }
        set_pwm1_duty(velocidadeCooler);
    }
    
    
}

