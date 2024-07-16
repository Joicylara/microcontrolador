/****************************************************************/
/*  SPI.C  -  Biblioteca de comunicação SPI (mestre)            */
/*  por software                                                */
/*                                                              */
/*  Autor : Fábio Pereira                                       */
/****************************************************************/

// Definições dos pinos da interface SPI
// Para utilizar outros pinos, basta incluir novas definições
// no arquivo do programa onde esta biblioteca for incluída
#ifndef spi_clk
	// Definições dos pinos de comunicação
	#define spi_clk  pin_b1	// pino de clock
	#define spi_dta  pin_b0	// pino de dados
	#define spi_cs   pin_b2	// pino de seleção
#endif

// definições de comandos SPI para memória
#define spi_read_cmd 	0x03
#define spi_write_cmd	0x02
#define spi_wren_cmd	0x06
#define spi_wrdi_cmd	0x04
#define spi_rdsr_cmd	0x05
#define spi_wrsr_cmd	0x01

void spi_escreve_bit (boolean bit)
// escreve um bit na interface SPI
{
	output_bit (spi_dta,bit);	// coloca o dado na saída
	output_high (spi_clk);		// ativa a linha de clock
	delay_us(1);
	output_low (spi_clk);		// desativa a linha de clock
}

void spi_escreve_byte (byte dado)
// escreve um byte na interface SPI
{
	int conta = 8;
	// envia primeiro o MSB
	while (conta)
	{
		spi_escreve_bit ((shift_left(&dado,1,0)));
		conta--;
	}
	output_float (spi_dta); // coloca a linha de dados em alta impedância
}

boolean spi_le_bit (void)
// le um bit na interface SPI
{
	boolean bit;
	output_high (spi_clk);
	delay_us (1);
	bit = input (spi_dta);
	output_low (spi_clk);
	return bit;
}

byte spi_le_byte (void)
// lê um byte na interface SPI
{
	int conta = 8, dado = 0;
	output_float (spi_dta);
	while (conta)
	{
		shift_left (&dado, 1, spi_le_bit());
		conta--;
	}
}

void spi_escreve_eeprom ( long int endereco, byte dado)
// escreve um dado em uma determinada posição da memória SPI
{
	output_low (spi_cs);			// seleciona a memória
	spi_escreve_byte (spi_write_cmd);	// envia comando de escrita
	spi_escreve_byte (endereco >>8);	// envia endereço MSB
	spi_escreve_byte (endereco);		// envia endereço LSB
	spi_escreve_byte (dado);		// envia dado
	output_high (spi_cs);		// desativa linha CS e inicia a escrita
	// lembre-se de aguardar 5ms antes de realizar outra escrita ou leitura
}

byte spi_le_eeprom ( long int endereco )
// lê um dado de uma determinada posição da memória SPI
{
	byte dado;
	output_low (spi_cs);
	spi_escreve_byte (spi_read_cmd);	// envia comando de leitura
	spi_escreve_byte (endereco >> 8);	// envia endereço MSB
	spi_escreve_byte (endereco);		// envia endereço LSB
	dado = spi_le_byte ();			// lê o dado
	output_high (spi_cs);		// desativa linha CS e termina leitura
}

void spi_ativa_escrita_eeprom (void)
// habilita a escrita na memória
{
	output_low (spi_cs);
	spi_escreve_byte (spi_wren_cmd);
	output_high (spi_cs);
}

void spi_desativa_escrita_eeprom (void)
// desabilita a escrita na memória SPI
{
	output_low (spi_cs);
	spi_escreve_byte (spi_wrdi_cmd);
	output_high (spi_cs);
}

byte spi_le_status_eeprom (void)
// le o registrador de estado da memória
{
	byte dado;
	output_low (spi_cs);
	spi_escreve_byte (spi_rdsr_cmd);
	dado = spi_le_byte ();
	output_high (spi_cs);
}

void spi_escreve_status_eeprom (byte dado)
// escreve o dado no registrador de estado da memória SPI
{
	output_low (spi_cs);
	spi_escreve_byte (spi_wrsr_cmd);
	spi_escreve_byte (dado);
	output_high (spi_cs);
}
