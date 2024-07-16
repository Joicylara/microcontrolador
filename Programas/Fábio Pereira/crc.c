int calc_crc(int *buff, int num_vals)
{
   int shift_reg=0, data_bit, sr_lsb, fb_bit, i, j;

   for (i=0; i<num_vals; i++)	// for each byte
   {
      for(j=0; j<8; j++)	// for each bit
      {
         data_bit = (buff[i]>>j)&0x01;
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

