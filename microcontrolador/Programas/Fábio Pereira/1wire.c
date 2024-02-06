/************************************************************************/
/*  1WIRE.C - Biblioteca de comunicação 1-wire                          */
/*                                                                      */
/*  Autor: Fábio Pereira                                                */
/*                                                                      */
/************************************************************************/

// definição do pino de comunicação
// Para utilizar outro pino, basta incluir uma nova definição antes
// de incluir este arquivo na aplicação desejada
#ifndef pino_1w
	#define pino_1w pin_d0	  // define o pino RD0 como comunicação 1-wire
#endif

#inline
void seta_saida_1w (void)
// coloca a saída em la impedância
{
	output_float (pino_1w);
}

#inline
void limpa_saida_1w (void)
// coloca a saída em nível 0
{
	output_low (pino_1w);
}

boolean reset_1w(void)
// reseta os dispositivos no barramento
{
	boolean presente;
	limpa_saida_1w ();
	delay_us(480);
	seta_saida_1w ();
	delay_us(60);
	presente = input (pino_1w);
	delay_us (240);
	return (presente);
	// 0 = dispositivo presente
	// 1 = nenhum dispositivo detectado
}

void alimenta_barramento_1w (void)
// força o barramento em nível alto
// utilizado com dispositivos alimentados no modo parasita
{
	output_high (pino_1w);
	delay_ms(1000);
	seta_saida_1w();
}

boolean le_bit_1w (void)
// lê um bit do barramento 1-wire
{
	// dá um pulso na linha, inicia quadro de leitura
	limpa_saida_1w ();		// coloca saida em zero
	seta_saida_1w ();		// retorna a saída a um
	delay_us (15);			// aguarda o dispositivo colocar
					// o dado na saída
	return (input(pino_1w));	// retorna o dado
}

void escreve_bit_1w (boolean bit)
// escreve um bit no barramento 1-wire
{
	limpa_saida_1w ();
	if (bit) seta_saida_1w (); // coloca dado 1 na saida
	delay_us (120);
	seta_saida_1w ();
}

byte le_byte_1w (void)
// lê um byte do barramento 1-wire
{
	byte i, dado = 0;
	// lê oito bits iniciando pelo bit menos significativo
	for (i=0;i<8;i++)
	{
		if (le_bit_1w ()) dado|=0x01<<i;
		delay_us(90);  // aguarda o fim do quadro de leitura
				// do bit atual
	}
	return (dado);
}

void escreve_byte_1w (char dado)
// escreve um byte no barramento 1-wire
{
	byte i, temp;
	// envia o byte iniciando do bit menos significativo
	for (i=0; i<8; i++)
	{
		temp = dado>>i;	// desloca o dado 1 bit à direita
		temp &= 0x01;		// isola o bit 0 (LSB)
		escreve_bit_1w (temp);	// escreve o bit no barramento
	}
}
