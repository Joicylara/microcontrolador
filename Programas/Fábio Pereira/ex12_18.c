// Este exemplo pode ser executado na placa PIC APLICAÇÕES II
#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7)

#include <1wire.c>

int calc_crc(int *dados, int quantidade)
{
   int shift_reg=0, data_bit, sr_lsb, fb_bit, i, j;

   for (i=0; i<quantidade; i++)  // loop de bytes
   {
      for(j=0; j<8; j++)	// loop de bits
      {
         data_bit = (dados[i]>>j)&0x01;
         sr_lsb = shift_reg & 0x01;
         fb_bit = (data_bit ^ sr_lsb) & 0x01;
         shift_reg = shift_reg >> 1;
         if (fb_bit)
         {
            shift_reg = shift_reg ^ 0x8c;
         }
      }
   }
   return(shift_reg);
}

void main(void)
{
	int buffer[9], conta;
	float temp;
	while (true)
	{
		reset_1w ();
		escreve_byte_1w (0xcc); 	// comando skip ROM
		escreve_byte_1w (0x44); 	// inicia conversão da temperatura
		reset_1w ();			// reseta o dispositivo
		escreve_byte_1w (0xcc);	// comando skip ROM
		// comando de leitura da memória de rascunho
		escreve_byte_1w (0xbe); 	
		// efetua a leitura dos nove bytes da memória de rascunho
		for (conta = 0; conta<9; conta++)
			buffer[conta]=le_byte_1w ();
		printf ("Temp LSB = %u\r\n",buffer[0]);
		printf ("Temp MSB = %u\r\n",buffer[1]);
		printf ("TH = %u\r\n",buffer[2]);
		printf ("TL = %u\r\n",buffer[3]);
		printf ("Contagem Remanescente = %u\r\n",buffer[6]);
		printf ("Contagem por grau C = %u\r\n",buffer[7]);
		printf ("CRC = %u\r\n",buffer[8]);
		printf ("CRC calculado = %u\r\n", calc_crc (buffer,8));
		reset_1w ();
		escreve_byte_1w (0xcc);
		escreve_byte_1w (0xb4);
		if (le_bit_1w()) printf ("Modo alimentado\r\n"); else printf ("Modo parasita\r\n");
		printf ("Temperatura = %Ld",((long)(buffer[1]<<8) + buffer[0])>>1);
		if (bit_test(buffer[0],0)) printf (".5");
		printf (" graus celsius (menos preciso)\r\n");
		temp = (long) (buffer[1]<<8) + buffer[0];
		temp = (temp / 2) - 0.25 + (float) ((buffer[7]-buffer[6])/buffer[7]);
		printf ("Temperatura = %3.2f graus celsius\r\n", temp);
		printf ("Proximo ?\r\n");
		while (getc()!=13);
	}
}
