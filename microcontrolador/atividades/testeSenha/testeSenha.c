#include <16F877A.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
//#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //High speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=20000000)

#use i2c(Master,Fast=100000, sda=PIN_C5, scl=PIN_C6,force_sw)  
#include "i2c_Flex_LCD.c" 
#include "kbd_ext_board2_ad.c"
#include "2408.C" 

long int End_HL(byte H, byte L){
   return (H<<8)+ L;
 }
char* IntToHex(int value) {
    int a;
    int b;
    char* buffer;
    a = value && 16;
    b = (value>>4)&16;
    buffer[0] = (a<10)?'0'+a:'A'-(a-10);
    buffer[1] = (b<10)?'0'+b:'A'-(b-10);
    return buffer;
}
void WRITE_FLOAT_EXT_EEPROM(long int n, float data) {
 int i;
 
 for (i = 0; i < 4; i++)
    write_ext_eeprom(i + n, *((int8*)&data + i) ) ;
}
float READ_FLOAT_EXT_EEPROM(long int n) {
    int i;
    float data;
 
 for (i = 0; i < 4; i++)
    *((int8*)&data + i) = read_ext_eeprom(i + n);
    
    return((float)data);
}
void eeprom_int16(unsigned int endereco, int16 valor_i16)
{
    write_ext_eeprom(endereco, make8(valor_i16,0));
    write_ext_eeprom(endereco+1, make8(valor_i16,1));
}

int teclaValida(char c)
{
   if (((int)c >= 48 && (int)c <= 57) || ((int)c >= 65 && (int)c <= 68) || ((int)c == 42 || (int)c == 35))
      return 1;
   else
      return 0;
}

void home(){
   printf(lcd_putc,"\fOlá, seja bem vindo(a)");
   delay_ms(1000);
   printf(lcd_putc, "\f1 - Cadastrar\n2 - Entrar");
}

void cadastrar(int id, char senha[]){
   printf(lcd_putc, "\fInsira o ID 0-9: %d\nSenha: %s", id, senha);
}

void validarSenha(char id, char senha[]){
   int a;
   int senhaCorreta=0, idExistente = 0;
   int16 j;
   int digito=0;
   
   for (j = 0; j < 1024; j = j + 5)
   {
      if (id == read_ext_eeprom((int16)j))
      {
         idExistente = 1;
         int i = 0;
         for (a = j + 1; a < j + 5; a++)
         {
            if (senha[i] == read_ext_eeprom((int16)a))
            {
               digito++;
            }
            if (digito == 4)
            {
               senhaCorreta = 1;
               break;
            }
            i++;
         }
      }
   }


if (senhaCorreta == 1 && idExistente == 1)
   {
      printf(lcd_putc, "\fPARABENS PORTA\nABERTA!!");
      delay_ms(3000);
   }
   else if (idExistente == 0)
   {
      printf(lcd_putc, "\fUsuario Nao\nExiste!");
      delay_ms(3000);
   }
   else if (idExistente == 1 && senhaCorreta == 0)
   {
      printf(lcd_putc, "\fSenha Invalida!");
      delay_ms(3000);
   }
   else
   {
      printf(lcd_putc, "\fERRO AO\nAUTENTICAR!");
      delay_ms(3000);
   }
}

int existente(char id){
   int16 i;
   for (i = 0; i < 1024; i = i + 5)
   {
      if (id == read_ext_eeprom((int16)i))
      {
         printf(lcd_putc, "\fUSER JA EXISTE");
         delay_ms(1000);
         return 0;
      }
   }

   return 1;
}


void main() {
   
    unsigned char tmp, id;
    unsigned char senha[4]= ""; // Senha com 3 caracteres + null terminator
    unsigned int16 memoria =0;

    
    setup_adc_ports(NO_ANALOGS);
    setup_adc(ADC_OFF);
    setup_psp(PSP_DISABLED);
    setup_spi(SPI_SS_DISABLED);
    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
    setup_timer_1(T1_DISABLED);
    setup_timer_2(T2_DISABLED,0,1);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
    port_b_pullups(true);
    
    lcd_init(0x4E,16,2); // Inicializa LCD
    delay_ms(10);
    init_ext_eeprom();
    delay_ms(10);
   
   // Grava ID e senha do Admin
   write_ext_eeprom(0x0, 0);
   write_ext_eeprom(0x1, '0');
   write_ext_eeprom(0x2, '0');
   write_ext_eeprom(0x3, '0');
   write_ext_eeprom(0x4, '0');
   
   int i;
   int16 j;
   for (i = 0; i < 4; i++)
   {
      senha[i] = 0;
   }

   printf(lcd_putc,"teste");
    
    while (true) {
    
      home();
      delay_ms(300);
      tmp = tc_tecla(200);

      if (teclaValida(tmp))
      {
         switch (tmp)
         {
         case '1':
            printf(lcd_putc, "\fID: ");
            tmp = tc_tecla(200);
            while (!teclaValida(tmp))
            {
               printf(lcd_putc, "\fID: ");
               tmp = tc_tecla(200);
            }
            if (!existente(tmp))
               break;
            printf(lcd_putc, "%c", tmp);
            write_ext_eeprom(memoria, tmp);
            memoria++;
            printf(lcd_putc, "\nSenha: ");
            tmp = tc_tecla(200);
            for (i = 0; i < 4; i++)
            {
               tmp = 'j';
               while (!teclaValida(tmp))
               {
                  tmp = tc_tecla(200);
               }
               senha[i] = tmp;
               printf(lcd_putc, "%c", tmp);
               write_ext_eeprom(memoria, tmp);
               memoria++;
            }
            printf(lcd_putc, "\fSenha cadastrada\ncom sucesso!");
            delay_ms(1000);
            // main();
            break;
         case '2':
            printf(lcd_putc, "\fID: ");
            tmp = tc_tecla(200);
            while (!teclaValida(tmp))
            {
               tmp = tc_tecla(200);
            }
            id = tmp;
            printf(lcd_putc, "\fStatus: FECHADA\nSenha: ");
            for (i = 0; i < 4; i++)
            {
               tmp = 'j';
               while (!teclaValida(tmp))
               {
                  tmp = tc_tecla(200);
               }
               printf(lcd_putc, "%c", tmp);
               senha[i] = tmp;
            }
            validarSenha(id, senha);
            break;
         case '*':
            printf(lcd_putc, "\fLIMPANDO MEMORIA");
            delay_ms(200);
            for (j = 0; j < 1024; j++)
            {
               write_ext_eeprom(j, 'F');
            }
            printf(lcd_putc, "\fMEMORIA LIMPA");
            delay_ms(1000);
            break;
         default:
            printf(lcd_putc, "\fERRO DESCONHECIDO");
            break;
         }
      }
   }
}


