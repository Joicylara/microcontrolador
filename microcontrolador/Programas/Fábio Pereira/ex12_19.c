// Este programa transmite serialmente um código para cada tecla
// pressionada. A tecla S1 envia o número "1", S2 envia o número "2" e
// S3 envia o número "3".

#include <12f675.h>
#use delay(clock=4000000)

// Configura o PIC para clock interno, pinos GP4 e GP5 para IO
// watchdog desligado, Power-up timer ativado, Detector de Brownout
// desligado e MCLR interno (GP3 é I/O)
#fuses INTRC_IO,NOWDT,PUT,NOBROWNOUT,NOMCLR

// inclui definições dos registradores do PIC12F675
#include <regs_12f6xx.h>

// valor de calibração do dispositivo, sujeito a alteração conforme o
// lote de fabricação do chip
#rom 0x3ff = { 0x34b4 }

// configurações de comunicação serial utilizando a biblioteca de
// software descrita neste livro
#define baud_rate 19200
#include <rs232.c>
#bit pino_tx = 0x05.5
#bit pino_rx = 0x05.4
#bit dir_tx  = 0x85.5
#bit dir_rx  = 0x85.4

char tcl;
boolean tecla_pres;

char varre_teclas (void)
// verifica se alguma tecla está pressionada
{
	if (!input(pin_a0))	return('1'); // verifica a tecla S1
	if (!input(pin_a1))	return('2'); // verifica a tecla S2
	if (!input(pin_a2))	return('3'); // verifica a tecla S3
	// se nenhuma tecla está pressionada, desliga o flag
	// tecla_pres e retorna o valor 0
	tecla_pres = 0;
	return (0);
}
char teclas (void)
// Rotina principal de verificação do teclado
// Verifica se é uma nova tecla e filtra ruídos
{
	int t;
	t = varre_teclas(); // verifica se há tecla
	if ((t) && (!tecla_pres))
	// se há tecla e o flag está apagado
	{
		tecla_pres = 1; // ativa o flag
		if (t != tcl)
		// se a tecla atual é diferente da tecla
		// anterior
		{
			// filtra o ruido de contato
			delay_ms (50); // aguarda 50ms
			// lê novamente as tecla e verifica
			// se a mesma tecla ainda está pressionada
			// caso positivo, retorna a tecla
			if (varre_teclas() == t) return (t);
		}
	}
	return (0); // se não há tecla, retorna 0
}
main()
{
// primeiro, lê o valor de calibração do oscilador
// e armazena no registrador OSCCAL. As versões
// mais recentes do PCM não necessitam desta rotina.
/*
#asm
	call 0x03ff
	movwf osccal
#endasm
*/
	cmcon = 0x07; // desativa entradas do comparador analógico
	ansel = 0; // configura entradas do A/D para E/S digital
	wpu = 0x07;  // ativa os pull-ups dos pinos 0, 1 e 2
	gppu = 0; // ativa o pull-up do GPIO
	rs232_inicializa();  // inicializa pinos RS232
	rs232_transmite ("Teste de Teclas\r\n");
	tcl = 0; // limpa a tecla atual
	tecla_pres = 0; // desliga o flag de tecla pressionada
	while (true)
	{
		tcl=teclas(); // verifica se há tecla pressionada
		if (tecla_pres)
		// caso exista tecla pressionada
		{
			// verifica se é a tecla é maior que 0
			if (tcl) rs232_transmite (tcl); // envia a tecla
		}
	}
}
