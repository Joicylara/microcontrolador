#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
#include <rs232.c>
main()
{
	// programa de teste: ecoa o dado recebido na porta serial
	// TX = RB0 e RX = RB1
	int x = tempo_bit_dado;
	rs232_inicializa ();
	while (true)
	{
		rs232_transmite(rs232_recebe());
 	}
}
