#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOLVP

signed long int t0_conta;

#int_timer0
void trata_t0 ()
{
	static boolean led;
	t0_conta -= 256; // subtrai 256 da contagem
	if (t0_conta<=0) // se a contagem é igual ou menor que zero
	{
		// soma 15625 ao valor da contagem
		t0_conta += 2500;
		led = !led;  // inverte o led
		output_bit (pin_c2,led);
	}
}

main()
{
	t0_conta = 2500;
	// configura o timer 0 para clock interno e
	// prescaler dividindo por 64
	setup_timer_0 ( RTCC_INTERNAL | RTCC_DIV_4 );
	// habilita interrupções
	enable_interrupts (global | int_timer0);
	while (true); // espera interrupção
}
