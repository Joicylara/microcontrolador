#include <16f628.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOMCLR,NOBROWNOUT,NOLVP
#use rs232(baud=19200, xmit=PIN_B2,rcv=PIN_B1)
#include <regs_16.h>

#bit saida_comp = 0x1F.6 // C1OUT
#bit pino_modul = 0x05.3 // RA3
#bit tris_modul = 0x85.3 // TRISA3
#byte cmcon_reg = 0x1F
#byte vrcon_reg = 0x9F

void inicializa_delta_sigma()
{
	vrcon_reg = 0xEC;
	tris_modul = 0;
	cmcon_reg = 6;
}

long int adc_delta_sigma (long int resolucao)
// Função de conversão analógico digital utilizando a técnica delta-sigma
// Para garantir que a cada ciclo possua a mesma duração, utiliza-se o
// timer 0, atuando como um contador de instruções. No início do ciclo o
// timer 0 é iniciado com o valor 247. Ao final do loop, antes de retornar
// ao seu início, o programa aguarda que o T0IF seja setado
{
	long int resultado = 0;
	t0cs = 0;  // timer 0 com clock interno
	psa = 1;  // clock tmr0 = 1Mhz
	cmcon_reg = 3;
	while (resolucao)
	{
		tmr0 = 247;  // configura o timer 0
		t0if = 0;  // apaga flag do timer 0
		if (saida_comp)
		{
			pino_modul = 1;
		} else
		{
			pino_modul = 0;
			resultado ++;  // incrementa acumulador de resultado
		}
		resolucao --; // decrementa o contador de ciclos
		while (!t0if);
	}
	cmcon_reg = 6;
	return (resultado);
}

main()
{
	long int valor;
	float val;
	printf ("\r\nADC delta sigma\r\n");
	inicializa_delta_sigma();
	while (true)
	{
		// a conversão será de 14 bits (16384)
		valor = adc_delta_sigma(16384);
		val = 5 * (float) valor / 16384;
		// se a tecla enter for pressionada
		if (kbhit()) if (getc() == 13)
		{
			// imprime os resultados na serial
			printf ("Tensao = %1.4f Volts\r\n",val);
			printf ("Valor = %lu\r\n",valor);
		}
	}
}
