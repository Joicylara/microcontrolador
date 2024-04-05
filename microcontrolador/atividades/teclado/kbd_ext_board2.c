//#include "C:\Users\JOICE\OneDrive\Documentos\Faculdade\microcontrolador\atividades\kbd_ext_board2\kbd_ext_board2.h"



/*###################################################################### 
 Rotina utilizaçãoo do teclado da placa PicSim board4
 Adaptada para o compilador CCS
 Autor: Alberto Willia Mascarenhas (adaptou para o compilador)
 For e-mail suggestions : awmascarenhas@gmail.com
######################################################################## */

unsigned char tc_tecla(unsigned int timeout)
{
 unsigned int to=0;
 unsigned char k = 0; 
 while(((to < timeout)||(!timeout))&&(!k)){
 
 
 //-------------------------------------------------------------------------
 //inicio do programa de varredura do teclado matricial
 //--------------------------------------------------------------------------
 //habilita primeira coluna do teclado
 input_high(PIN_B0);input_low(PIN_B1);input_low(PIN_B2);input_low(PIN_B3);
 delay_ms(20);
 if (output(PIN_D0) == 0){while(output(PIN_D0) == 0);k='1';};
 if (output(PIN_D1) == 0){while(output(PIN_D1) == 0);k='4';};
 if (output(PIN_D2) == 0){while(output(PIN_D2) == 0);k='7';};
 if (output(PIN_D3) == 0){while(output(PIN_D3) == 0);k='*';};
 //habilita segunda coluna do teclado
 input_low(PIN_B0);input_high(PIN_B1);input_low(PIN_B2);input_low(PIN_B3);
 delay_ms(20); 
 if (output(PIN_D0) == 0){while(output(PIN_D0) == 0);k='2';};
 if (output(PIN_D1) == 0){while(output(PIN_D1) == 0);k='5';};
 if (output(PIN_D2) == 0){while(output(PIN_D2) == 0);k='8';};
 if (output(PIN_D3) == 0){while(output(PIN_D3) == 0);k='0';};
 
 //habilita terceira coluna do teclado
 input_low(PIN_B0);input_low(PIN_B1);input_high(PIN_B2);input_low(PIN_B3);
 delay_ms(20); 
 if (output(PIN_D0) == 0){while(output(PIN_D0) == 0);k='3';};
 if (output(PIN_D1) == 0){while(output(PIN_D1) == 0);k='6';};
 if (output(PIN_D2) == 0){while(output(PIN_D2) == 0);k='9';};
 if (output(PIN_D3) == 0){while(output(PIN_D3) == 0);k='#';};
 //habilita quarta coluna do teclado
 input_low(PIN_B0);input_low(PIN_B1);input_low(PIN_B2);input_high(PIN_B3);
 delay_ms(20); 
 if (output(PIN_D0) == 0){while(output(PIN_D0) == 0);k='A';};
 if (output(PIN_D1) == 0){while(output(PIN_D1) == 0);k='B';};
 if (output(PIN_D2) == 0){while(output(PIN_D2) == 0);k='C';};
 if (output(PIN_D3) == 0){while(output(PIN_D3) == 0);k='D';};
 
 delay_ms(5);
 to+=5;
 }
 if(!k)k=255;
 return k; 
}
