#include <16F877A.h>
#device adc=8

#FUSES NOWDT, HS, NOPUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT
#use delay(clock=6000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7) // Configura��o do TTL USB

#define TRIG_PIN PIN_B0
#define ECHO_PIN PIN_B1
#define COOLER_PIN PIN_C2

unsigned int16 get_distance() {
    unsigned int16 duration, distance;

    // Envia pulso de 10us ao Trigger
    output_high(TRIG_PIN);
    delay_us(10);
    output_low(TRIG_PIN);

    // Aguarda Echo
    while(!input(ECHO_PIN));
    set_timer1(0); // Reseta Timer1
    // Aguarda fim do Echo
    while(input(ECHO_PIN));
    duration = get_timer1();

    // Calcula a dist�ncia em cent�metros
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

    // Configura��o inicial
    set_pwm1_duty(0);

    printf("Digite a altura desejada: ");
    gets(input_buffer); // L� a entrada do usu�rio
    desired_distance = convert_to_int(input_buffer); // Converte a entrada para inteiro

    while(TRUE) {
        distance = get_distance();

        // Envia a dist�ncia atual ao computador via serial
        printf("Altura atual: %Lu cm\r\n", (unsigned long) distance);

        // Controle do cooler via PWM
        if(distance < desired_distance) {
            set_pwm1_duty(255); // Liga o cooler (m�ximo)
        } else {
            set_pwm1_duty(0); // Desliga o cooler
        }

        delay_ms(100); // Atraso para estabilidade
    }
}

