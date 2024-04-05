//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\testeSenha.h"

#include <16F877A.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// #device adc=8

#FUSES NOWDT     // No Watch Dog Timer
#FUSES XT        // High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT     // No Power Up Timer
#FUSES NOPROTECT // Code not protected from reading
#FUSES NODEBUG   // No Debug mode for ICD
#FUSES BROWNOUT  // Reset when brownout detected
#FUSES NOLVP     // No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD     // No EE protection
#FUSES NOWRT     // Program memory not write protected
#FUSES RESERVED  // Used to set the reserved FUSE bits

#use delay(clock = 4000000)

#ifndef lcd_enable
#define lcd_enable pin_A3 // pino enable do LCD
#define lcd_rs pin_A5     // pino rs do LCD
#define lcd_rw pin_A4     // pino rw do LCD
#define lcd_d4 pin_d4     // pino de dados d4 do LCD
#define lcd_d5 pin_d5     // pino de dados d5 do LCD
#define lcd_d6 pin_d6     // pino de dados d6 do LCD
#define lcd_d7 pin_d7     // pino de dados d7 do LCD
#endif

#include "mod_lcd.c"
#include "kbd_ext_board2.c"
#include "2408.c"

long int End_HL(byte H, byte L)
{
   return (H << 8) + L;
}

char *IntToHex(int value)
{
   int a;
   int b;
   char *buffer;

   a = value && 16;
   b = (value >> 4) & 16;
   buffer[0] = (a < 10) ? '0' + a : 'A' - (a - 10);
   buffer[1] = (b < 10) ? '0' + b : 'A' - (b - 10);

   return buffer;
}

void WRITE_FLOAT_EXT_EEPROM(long int n, float data)
{
   int i;

   for (i = 0; i < 4; i++)
      write_ext_eeprom(i + n, *((int8 *)&data + i));
}

float READ_FLOAT_EXT_EEPROM(long int n)
{
   int i;
   float data;

   for (i = 0; i < 4; i++)
      *((int8 *)&data + i) = read_ext_eeprom(i + n);

   return ((float)data);
}

void eeprom_int16(unsigned int endereco, int16 valor_i16)
{
   write_ext_eeprom(endereco, make8(valor_i16, 0));
   write_ext_eeprom(endereco + 1, make8(valor_i16, 1));
}

int1 eTeclaValida(char c)
{
   if (((int)c >= 48 && (int)c <= 57) || ((int)c >= 65 && (int)c <= 68) || ((int)c == 42 || (int)c == 35))
      return 1;
   else
      return 0;
}

void desenhaTelaInicial()
{
   printf(lcd_escreve, "\fSeja bem vindo!");
   delay_ms(1000);
   printf(lcd_escreve, "\f1 - Cadastrar\n2 - Utilizar");
}

void desenhaTelaCadastrar(int userID, char senha[])
{
   printf(lcd_escreve, "\fID User: %d\nSenha: %s", userID, senha);
}

void confereSenha(char user, char senha[])
{
   int8 c;
   int1 senhaEstaCorreta = 0, userExiste = 0;
   int8 digitosIguais = 0;
   int16 j;

   for (j = 0; j < 1024; j = j + 5)
   {
      if (user == read_ext_eeprom((int16)j))
      {
         userExiste = 1;
         int8 i = 0;
         for (c = j + 1; c < j + 5; c++)
         {
            if (senha[i] == read_ext_eeprom((int16)c))
            {
               digitosIguais++;
            }
            if (digitosIguais == 4)
            {
               senhaEstaCorreta = 1;
               break;
            }
            i++;
         }
      }
   }

   if (senhaEstaCorreta == 1 && userExiste == 1)
   {
      printf(lcd_escreve, "\fPARABENS PORTA\nABERTA!!");
      delay_ms(3000);
   }
   else if (userExiste == 0)
   {
      printf(lcd_escreve, "\fUsuario Nao\nExiste!");
      delay_ms(3000);
   }
   else if (userExiste == 1 && senhaEstaCorreta == 0)
   {
      printf(lcd_escreve, "\fSenha Invalida!");
      delay_ms(3000);
   }
   else
   {
      printf(lcd_escreve, "\fERRO AO\nAUTENTICAR!");
      delay_ms(3000);
   }
}

int1 confereUserJaExiste(char user)
{
   int16 j;
   for (j = 0; j < 1024; j = j + 5)
   {
      if (user == read_ext_eeprom((int16)j))
      {
         printf(lcd_escreve, "\fUSER JA EXISTE");
         delay_ms(1000);
         return 0;
      }
   }

   return 1;
}

void main()
{
   char senha[4] = "";
   char tmp, user;
   int16 posMemoria = 0;

   setup_adc_ports(AN0);
   setup_adc(ADC_CLOCK_DIV_2);
   setup_psp(PSP_DISABLED);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED, 0, 1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   lcd_ini(); // Inicializa LCD
   delay_ms(10);
   init_ext_eeprom();
   delay_ms(10);

   // Grava ID e senha do Admin
   write_ext_eeprom(0x0, 0);
   write_ext_eeprom(0x1, '0');
   write_ext_eeprom(0x2, '0');
   write_ext_eeprom(0x3, '0');
   write_ext_eeprom(0x4, '0');

   int8 i;
   int16 j;
   for (i = 0; i < 4; i++)
   {
      senha[i] = 0;
   }

   while (true)
   {
      desenhaTelaInicial();
      delay_ms(300);
      tmp = tc_tecla(200);

      if (eTeclaValida(tmp))
      {
         switch (tmp)
         {
         case '1':
            printf(lcd_escreve, "\fID User: ");
            tmp = tc_tecla(200);
            while (!eTeclaValida(tmp))
            {
               printf(lcd_escreve, "\fID User: ");
               tmp = tc_tecla(200);
            }
            if (!confereUserJaExiste(tmp))
               break;
            printf(lcd_escreve, "%c", tmp);
            write_ext_eeprom(posMemoria, tmp);
            posMemoria++;
            printf(lcd_escreve, "\nSenha: ");
            tmp = tc_tecla(200);
            for (i = 0; i < 4; i++)
            {
               tmp = 'j';
               while (!eTeclaValida(tmp))
               {
                  tmp = tc_tecla(200);
               }
               senha[i] = tmp;
               printf(lcd_escreve, "%c", tmp);
               write_ext_eeprom(posMemoria, tmp);
               posMemoria++;
            }
            printf(lcd_escreve, "\fSenha cadastrada\ncom sucesso!");
            delay_ms(1000);
            // main();
            break;
         case '2':
            printf(lcd_escreve, "\fID User: ");
            tmp = tc_tecla(200);
            while (!eTeclaValida(tmp))
            {
               tmp = tc_tecla(200);
            }
            user = tmp;
            printf(lcd_escreve, "\fStatus: FECHADA\nSenha: ");
            for (i = 0; i < 4; i++)
            {
               tmp = 'j';
               while (!eTeclaValida(tmp))
               {
                  tmp = tc_tecla(200);
               }
               printf(lcd_escreve, "%c", tmp);
               senha[i] = tmp;
            }
            confereSenha(user, senha);
            break;
         case '*':
            printf(lcd_escreve, "\fLIMPANDO MEMORIA");
            delay_ms(200);
            for (j = 0; j < 1024; j++)
            {
               write_ext_eeprom(j, 'F');
            }
            printf(lcd_escreve, "\fMEMORIA LIMPA");
            delay_ms(1000);
            break;
         default:
            printf(lcd_escreve, "\fERRO DESCONHECIDO");
            break;
         }
      }
   }
}
