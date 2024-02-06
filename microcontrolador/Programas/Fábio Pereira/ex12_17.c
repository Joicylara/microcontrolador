// Este programa utiliza o circuito descrito na figura 12.10 e permite
// o acesso a até 8 memórias 24LC256 ligadas ao barramento I2C
#include <16f877.h>
#use delay(clock=4000000)
#fuses HS,NOWDT,PUT,NOBROWNOUT,NOLVP
#use rs232(baud=19200, xmit=PIN_C6, rcv=PIN_C7)
#include <input.c>

// define os pinos de comunicação
#define scl pin_d1
#define sda pin_d0
// inclui a biblioteca I2C
#include <i2c.c>

main()
{
   byte valor, dispositivo, tecla;
   long int endereco;
   do
	{
      do
		{
         printf("\r\nLeitura ou Escrita: ");
         tecla = toupper(getc());
         putc(tecla);
      } while ( (tecla!='L') && (tecla!='E') );

      printf("\n\rDispositivo: ");
		dispositivo = gethex1();
		printf("\n\rEndereco: ");
      endereco = gethex();
      endereco = (endereco<<8)+gethex();
      if(tecla=='L') printf("\r\nValor: %X\r\n",le_eeprom( dispositivo, endereco ) );
      if(tecla=='E')
		{
         printf("\r\nNovo valor: ");
         valor = gethex();
         printf("\n\r");
         escreve_eeprom( dispositivo, endereco, valor );
      }
   } while (TRUE);
}
