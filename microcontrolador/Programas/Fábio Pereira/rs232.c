/************************************************************************/
/*  RS232.C     Biblioteca de Comunicação serial assíncrona por         */
/*					 software                               */
/*                                                                      */
/*  Autor: Fabio Pereira                                                */
/*                                                                      */
/*  Velocidade : 9600 Bps, 1 Start, 1 Stop, Sem paridade                */
/*                                                                      */
/*  Estas rotinas funcionam sem modificação para velocidades de 9600 e  */
/*  19200 Bps.                                                          */
/*                                                                      */
/************************************************************************/

// Definições de comunicação
/* 
   Para alterar a velocidade de comunicação, basta alterar o valor da
   constante baud_rate
*/
#ifndef baud_rate
const long int baud_rate = 9600;
#endif
const int tempo_bit_dado = 1000000/baud_rate-10; // tempo do bit de dado
const int tempo_bit_start = 1500000/baud_rate;  // tempo do bit de start

// Definições dos pinos de comunicação
// Para utilizar outros pinos, basta incluir novas definições
// no arquivo do programa onde esta biblioteca for incluída
#bit pino_tx = 0x06.0	// pino de transmissão é o RB0
#bit pino_rx = 0x06.1	// pino de recepção é o RB1
#bit dir_tx  = 0x86.0	// direção do pino de tx
#bit dir_rx  = 0x86.1	// direção do pino de rx

void rs232_inicializa (void)
{
	dir_tx = 0;	// pino de tx como saída
	pino_tx = 1;	// coloca o pino de tx em nível 1
	dir_rx = 1;	// configura o pino de rx como entrada
}
void rs232_transmite (char dado)
{
	boolean result;
	int conta;
	// primeiro o bit de start
	pino_tx = 0;
	delay_us(tempo_bit_dado);	// aguarda o tempo de start
	conta = 8;			// são 8 bits de dados
	while (conta)
	{
		// desloca o dado à direita e dependendo do resultado
		// seta ou não a saída
		if (shift_right ( &dado, 1, 0)) pino_tx=1; else pino_tx=0;
		delay_us ( tempo_bit_dado);	// aguarda o tempo do bit de dado
		conta--;	// decrementa um no número de bits a transmitir
	}
	pino_tx = 1;			// seta a saída TX (bit de stop)
	delay_us(tempo_bit_dado);	// aguarda o tempo de 1 bit
}

char rs232_recebe (void)
{
	int conta,dado;
	while (pino_rx);		// aguarda o bit de start
	delay_us(tempo_bit_start);	// aguarda o tempo de start
	conta = 8;			// são 8 bits de dados
	dado = 0;			// apaga o dado recebido
	while (conta)
	{
		shift_right( &dado, 1, pino_rx);	// insere o bit recebido
							// deslocando à direita a
// variável com o dado 
// recebido
		delay_us(tempo_bit_dado);		// aguarda o tempo de 1 bit
		conta--;			// decrementa o número de bits
	}
	delay_us(tempo_bit_dado);		// aguarda o tempo de 1 bit
	return dado;				// retorna o dado recebido
}
