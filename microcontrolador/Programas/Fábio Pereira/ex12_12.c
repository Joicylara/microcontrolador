#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOLVP

#int_timer0
void trata_t0 ()
{
	static boolean led;
	static int conta;
	// reinicia o timer 0 em 131 mais a contagem que já passou
	set_timer0(131+get_timer0());
	conta++;
	// se já ocorreram 125 interrupções
	if (conta == 125)
	{
		conta=0;
		led = !led;  // inverte o led
		output_bit (pin_b0,led);
	}
}

main()
{
	// configura o timer 0 para clock interno e prescaler dividindo por 64
	setup_timer_0 ( RTCC_INTERNAL | RTCC_DIV_8 );
	set_timer0(131); // inicia o timer 0 em 131
	// habilita interrupções
	enable_interrupts (global | int_timer0);
	while (true); // espera interrupção
}


















