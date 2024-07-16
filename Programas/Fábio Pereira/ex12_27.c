#include <18f452.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT
#use rs232(baud=19200, xmit=PIN_C6,rcv=PIN_C7)
#include <regs_18fxx2.h>

main()
{
	long int ciclo=0;
	printf ("\r\nTeste do PWM\r\n");
	setup_timer_2 (T2_DIV_BY_4, 248, 1);  // timer 2 = 1,004 khz
	setup_ccp1 (ccp_pwm);  // configura CCP1 para modo PWM
	set_pwm1_duty ( 0 );  // configura o ciclo ativo em 0 (desligado)
	while (true)
	{
		if (kbhit())  // se uma tecla for pressionada
		{
			switch (getc())  // verifica a tecla
			{
				case '1' :	ciclo = 50;
						break;
				case '2' :	ciclo = 100;
						break;
				case '3' :	ciclo = 255;
						break;
				case '4' :	ciclo = 350;
						break;
				case '5' :	ciclo = 500;
						break;
				case '6' :	ciclo = 700;
						break;
				case '7' :	ciclo = 900;
						break;
				case '8' :	ciclo = 1023;
						break;
				case '0' :	ciclo = 0;
						break;
				case '-' :	ciclo -= 10;
						break;
				case '=' :	ciclo += 10;
						break;
			}
			if (ciclo>1023) ciclo = 1023;
			printf ("Ciclo ativo = %lu\r\n",ciclo);
			set_pwm1_duty (ciclo);  // configura o ciclo ativo
			// imprime o estado do CCPR1L
			printf ("CCPR1L = %u\r\n", ccpr1l);
			// imprime o estado do bit CCP1X
			printf ("CCP1X = %u\r\n", ccp1x);
			// imprime o estado do bit CCP1Y
			printf ("CCP1Y = %u\r\n", ccp1y);
		}
	}
}
