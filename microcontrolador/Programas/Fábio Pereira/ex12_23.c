// Uma animação simples no display
#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
#include <mod_lcd.c>
main()
{
	char k;
	// desliga as entradas analógicas
	setup_adc_ports(no_analogs);
	lcd_ini();
	// configura registrador AC para o endereço inicial da CGRAM
	lcd_envia_byte(0,0x40);
	lcd_envia_byte(1,0x04);	// primeira linha do primeiro caractere
	lcd_envia_byte(1,0x0e);	// segunda linha do primeiro caractere
	lcd_envia_byte(1,0x15);	// terceira linha do primeiro caractere
	lcd_envia_byte(1,0x04);	// quarta linha do primeiro caractere
	lcd_envia_byte(1,0x04);	// quinta linha do primeiro caractere
	lcd_envia_byte(1,0x04);	// sexta linha do primeiro caractere
	lcd_envia_byte(1,0x04);	// sétima linha do primeiro caractere
	lcd_envia_byte(1,0x00);	// oitava linha do primeiro caractere
	lcd_envia_byte(1,0x00);	// primeira linha do segundo caractere
	lcd_envia_byte(1,0x04);	// segunda linha do segundo caractere
	lcd_envia_byte(1,0x0e);	// terceira linha do segundo caractere
	lcd_envia_byte(1,0x15);	// quarta linha do segundo caractere
	lcd_envia_byte(1,0x04);	// quinta linha do segundo caractere
	lcd_envia_byte(1,0x04);	// sexta linha do segundo caractere
	lcd_envia_byte(1,0x04);	// sétima linha do segundo caractere
	lcd_envia_byte(1,0x00);	// oitava linha do segundo caractere
	// registrador AC aponta para a primeira coluna da segunda linha
	lcd_envia_byte(0,0xC0);	
	while (true)
	{
	// registrador AC aponta para a primeira coluna da segunda linha
	lcd_envia_byte(0,0xC0);
	// imprime o primeiro caractere do usuário
	lcd_envia_byte(1,0x00);
	delay_ms(300);
	// registrador AC aponta para a primeira coluna da segunda linha
	lcd_envia_byte(0,0xC0);
	// imprime o segundo caractere do usuário
	lcd_envia_byte(1,0x01);
	delay_ms(300);
	}
}
