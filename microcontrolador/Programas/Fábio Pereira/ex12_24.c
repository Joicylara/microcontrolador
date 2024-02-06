#include <16f877.h>
// Configura o compilador para conversor A/D de 10 bits
#device adc=10
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT
#use rs232(baud=19200, xmit=PIN_C6,rcv=PIN_C7)
#include <regs_16f87x.h>
#include <mod_lcd.c>

main()
{
	long int valor;
	int32 val32;
	lcd_ini();
	setup_ADC_ports (RA0_analog);
	setup_adc(ADC_CLOCK_INTERNAL );
	set_adc_channel(0);
	while (true)
	{
		lcd_escreve ('\f');  // apaga o display
		// O escalonamento é realizado da seguinte forma:
		// resultado = (5000 * valor lido) / 1023
		// Para facilitar os cálculos, somamos um ao
		// valor lido:
		// resultado = (5000 * (valor + 1)) / 1024
		// simplificando:
		// resultado = ((valor + 1) * 4) + ((valor + 1) * 113) / 128
		// Repare que é necessário converter a segunda parte da
		// equação para 32 bits para que o compilador efetue o
		// cálculo corretamente
		valor = read_adc(); // efetua a conversão A/D
		// Se o valor é > 0, soma 1 ao valor lido
		if (valor) valor += 1;
		val32 = valor * 4 + ((int32)valor * 113)/128;
		// imprime o valor da tensão no display
		// 5000 = 5,000 Volts ou 5000 milivolts
		printf (lcd_escreve,"Tensao = %lu mV",val32);
		// se a tecla enter for pressionada
		if (kbhit()) if (getc() == 13)		
{
			// imprime os resultados na serial
			printf ("Tensao = %lu miliVolts\r\n",val32);
			printf ("Valor = %lu\r\n",valor);
		}
		delay_ms (250); // aguarda 250 ms
	}
}
