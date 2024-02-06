// Este programa ecoa o caractere enviado serialmente, além de imprimi-lo
// no display
#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
#include <mod_lcd.c>
#include <usart.c>
main()
{
	char k;
	setup_adc_ports(no_analogs);
	usart_inicializa (12,1); // velocidade: 19200
	usart_transmite ("Testando LCD + USART\r\n");
	lcd_ini();
	while (true)
	{
	k=usart_recebe();
	usart_transmite(k);
   		if (k)
         if(k=='*')
            lcd_escreve('\f');
         else
            lcd_escreve(k);
	}
}
