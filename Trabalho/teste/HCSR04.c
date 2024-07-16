/* #include <HCSR04.c>
*
* Creada por: Ing. Abiezer Hernandez O.
* Fecha de creacion: 21/02/2018
* Electronica y Circuitos
*
*/

void HCSR04_init(void)
{
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);
   output_float(P_ECHO);
   output_drive(P_TRIG);
   output_low(P_TRIG);
}

float HCSR04_get_distance(void)
{
   int16 tiempo_eco=0;
   float distancia=0;
   float tick = 0;
   tick = (4000.0 / FOSC) * 8.0;
   output_high(P_TRIG); 
   delay_us(10);
   output_low(P_TRIG);
   while(!input_state(P_ECHO));
   set_timer1(0); 
   while(input_state(P_ECHO));
   tiempo_eco = get_timer1();
   distancia = (tiempo_eco/2.0)*tick*34.0;
   return distancia;
}
