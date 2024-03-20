#include <16F877A.h>
#device adc=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES XT                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES NOPUT                    //No Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES BROWNOUT                 //Reset when brownout detected
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#FUSES RESERVED                 //Used to set the reserved FUSE bits

#use delay(clock=8000000)

byte const unidade[10]={
    0b11111100, //0
    0b01100000, //1
    0b11011010, //2
    0b11110010, //3
    0b01100110, //4
    0b10110110, //5
    0b10111110, //6
    0b11100000, //7
    0b11111110, //8
    0b11100110  //9
};

byte const dezena[10]={
    0b11111110, //0
    0b00110000, //1
    0b11011010, //2
    0b01111010, //3
    0b00110100, //4
    0b01101110, //5
    0b11101110, //6
    0b00111000, //7
    0b11111110, //8
    0b01111110  //9
};

void main()
{
    int8 cont = 0;
    int8 d, u;
 
    while(true)
    {
        d = cont / 10;
        u = cont % 10;

        output_B(dezena[d]);
        delay_ms(500);
        output_B(unidade[u]);
        delay_ms(500); 
        
        cont++;
        if (cont > 10)
            cont = 0;
    }
}

