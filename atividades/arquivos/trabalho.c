#include <16F877A.h>
#device adc=8

#FUSES NOWDT, HS, NOPUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=6000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) 

#define TRIG_PIN PIN_B0
#define ECHO_PIN PIN_B1
#define COOLER_PIN PIN_C2

unsigned int16 get_distance() {
    unsigned int16 duration, distance;

    
    output_high(TRIG_PIN);
    delay_us(10);
    output_low(TRIG_PIN);

    
    while(!input(ECHO_PIN));
    set_timer1(0); 
    
    while(input(ECHO_PIN));
    duration = get_timer1();

    
    distance = duration / 58;
    return distance;
}

unsigned int16 convert_to_int(char *buffer) {
    unsigned int16 result = 0;
    int i = 0;
    
    while(buffer[i] != '\0') {
        result = result * 10 + (buffer[i] - '0');
        i++;
    }
    
    return result;
}

void main() {
    unsigned int16 distance, desired_distance;
    char input_buffer[10];

    setup_adc_ports(NO_ANALOGS);
    setup_timer_1(T1_INTERNAL | T1_DIV_BY_1);
    setup_ccp1(CCP_PWM);
    setup_timer_2(T2_DIV_BY_16, 255, 1);

    
    set_pwm1_duty(0);

    printf("Digite a altura desejada: ");
    gets(input_buffer); 
    desired_distance = convert_to_int(input_buffer); 
    printf("Altura desejada: %Lu cm\r\n", (unsigned long) desired_distance); 

    while(TRUE) {
        distance = get_distance();

        
        printf("Altura atual: %Lu cm\r\n", (unsigned long) distance);

        
        if(distance < desired_distance) {
            set_pwm1_duty(255); 
        } else {
            set_pwm1_duty(0); 
        }

        delay_ms(100); 
    }
}

