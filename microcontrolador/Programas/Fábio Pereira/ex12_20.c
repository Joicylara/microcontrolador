// Este programa transmite serialmente o caractere pressionado no teclado
// além de apresentá-lo no display LCD. O teclado inclui facilidades de
// auto-repetição e função shift
#include <16f876.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT
#include <regs_16F87X.h>

// Configurações de comunicação serial utilizando a biblioteca de
// software descrita neste livro
#define baud_rate 19200
#include <rs232.c>
#bit pino_tx = 0x07.6
#bit pino_rx = 0x07.7
#bit dir_tx  = 0x87.6
#bit dir_rx  = 0x87.7

// configuração dos pinos do LCD
#define lcd_enable 	pin_c1		// pino enable do LCD
#define lcd_rs		pin_c0		// pino rs do LCD
#define lcd_d4		pin_a0		// pino de dados d4 do LCD
#define lcd_d5		pin_a1		// pino de dados d5 do LCD
#define lcd_d6		pin_a2		// pino de dados d6 do LCD
#define lcd_d7		pin_a3		// pino de dados d7 do LCD
#include <mod_lcd.c>

// Definições da matriz do teclado
#define COL1	pin_b4
#define COL2	pin_b5
#define COL3	pin_b6
#define LIN1	pin_b3
#define LIN2	pin_b2
#define LIN3	pin_b1
#define LIN4	pin_b0

struct stecla
{
	int cod_tecla : 7;
	int nova : 1;
} tecla;

char varre_teclas (void)
// Realiza a varredura do teclado e retorna o
// valor da tecla pressionada.
// O teclado está conectado da seguinte forma:
//
//		COL1	COL2	COL3
// LIN1	1	2	3
// LIN2	4	5	6
// LIN3	7	8	9
// LIN4	S	0	E
//
// S - Shift   E - Enter
//
// Os valores decimais retornados são:
// 	Sem shift	Com shift
// 0	48		80
// 1	49		81
// 2	50		82
// 3	51		83
// 4	52		84
// 5	53		85
// 6	54		86
// 7	55		87
// 8	56		88
// 9	57		89
// E	13		13
// Esta função possui caracter genérico
// e pode ser reescrita para otimizar
// casos específicos
{
	int tecla;
	boolean shift;
	shift = 0;
	output_high(COL1); // ativa a primeira coluna
	output_low(COL2);
	output_low(COL3);
	if (input(LIN1)) tecla = 49;
	if (input(LIN2)) tecla = 52;
	if (input(LIN3)) tecla = 55;
	if (input(LIN4)) shift = 1;
	output_low(COL1);
	output_high(COL2); // ativa a segunda coluna
	if (input(LIN1)) tecla = 50;
	if (input(LIN2)) tecla = 53;
	if (input(LIN3)) tecla = 56;
	if (input(LIN4)) tecla = 48;
	output_low(COL2);
	output_high(COL3); // ativa a terceira coluna
	if (input(LIN1)) tecla = 51;
	if (input(LIN2)) tecla = 54;
	if (input(LIN3)) tecla = 57;
	if (input(LIN4)) tecla = 13;
	if ((shift) && (tecla!=13)) tecla += 32;
	return (tecla);
}

struct stecla trata_teclas (void)
{
	// constantes de temporização do teclado
	// ciclos de filtragem de tecla
	const int c_filtro = 10; 
	// ciclos antes de iniciar a auto-repetição
	const int c_ini_autorep = 50;
	// ciclos entre cada repetição de tecla
	const int c_autorep = 20;
	static boolean filtro, ini_autorep;
	static int tempo_filtro, tempo_ini_autorep, tempo_autorep;
static int tecla_anterior;
	int tecla_atual;
	struct stecla tecla_pres;
	tecla_atual = varre_teclas();
	if (tecla_atual)
	{
		if (tecla_atual == tecla_anterior)
		{
			if (filtro)
			{
				tempo_filtro --;
				if (!tempo_filtro)
				{
					tempo_filtro = c_filtro;
					filtro = 0;
					tecla_pres.cod_tecla = tecla_atual;
					tecla_pres.nova = 1;
					ini_autorep = 1;
				}
			} else if (ini_autorep) // se filtro = 0
			{
				tempo_ini_autorep --;
				if (!tempo_ini_autorep)
				{
					tempo_ini_autorep = c_ini_autorep;
					ini_autorep = 0;
				}
			} else  // se ini_autorep = 0
			{
				tempo_autorep --;
				if (!tempo_autorep)
				{
					tecla_pres.cod_tecla = tecla_atual;
					tecla_pres.nova = 1;
					tempo_autorep = c_autorep;
				} else tecla_pres.nova = 0;
			}
		} else // tecla_atual != tecla_anterior
		{
			tecla_anterior = tecla_atual;
			filtro = 1;
			ini_autorep = 0;
		}
	} else
	{
		tecla_pres.nova = 0;
		tecla_anterior = 0;
		filtro = 0;
		ini_autorep = 0;
		tempo_autorep = c_autorep;
		tempo_filtro = c_filtro;
		tempo_ini_autorep = c_ini_autorep;
	}
	return (tecla_pres);
}

main()
{
	// O registrador CMCON somente está implementado nas versões "A"
	//CMCON = 7;		// desabilita comparadores analógicos
	ADCON1 = 7;		// desabilita entradas analógicas
	lcd_ini ();		// inicializa display
	rs232_inicializa();  	// inicializa pinos RS232
	while (true)
	{
		tecla = trata_teclas();
		if (tecla.nova)
		// caso exista tecla pressionada
		{
			rs232_transmite (tecla.cod_tecla); // envia a tecla
			// apresenta no display LCD
			switch (tecla.cod_tecla)
			{
				// shift + 0 apaga o display
				case 80	:	lcd_escreve ('\f');
								break;
				// ... outros comandos podem ser adicionados aqui
				default	:	lcd_escreve (tecla.cod_tecla);
			}
		}
		delay_ms(10);	// tempo entre varreduras
	}
}
