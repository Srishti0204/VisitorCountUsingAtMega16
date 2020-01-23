#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#define lcd PORTD
#include<library/lcd.h>
void lcd_string(unsigned char *str)
{    int i=0;
     while(str[i]!='\0')
	 {   lcd_data(str[i]);
	     i++;
     }
}
void main()
{    
	DDRA=0b01111110;
     DDRD=0b11111111;
     lcd_ini();
	 static int i=0,j=0;
	 
     while(1)
	 {    lcd_command(0x80);
	 	  lcd_string("IN");
		  lcd_command(0x8d);
		  lcd_string("OUT");
          //if(PINA==0b00000001)
		  if(PINA==0x01)
		  {     i=i+1;
		        while(PINA&0x01);
				if(i<10)
	 	        { 	lcd_command(0xc1);
				    lcd_data(48+i);
					_delay_ms(200);
                }
				else
				{   lcd_command(0xc1);
				    lcd_data(48+(i/10));
					lcd_command(0xc2);
					lcd_data(48+(i%10));
					_delay_ms(200);
                }
           }
          
		  
	      //else if(PINA==0b10000000)
		  
		   if((PINA==0x80)&&(j<=i-1))
		   {     
	            j=j+1;
	            while(PINA&0x80);       //empty loop to hold the sensor i.e even if the person keeps standing 
				                        //the counter doesnt increase
				if(j<10)
				{   lcd_command(0xcd);
				    lcd_data(48+j);
					_delay_ms(200);
                }
				else
				{   lcd_command(0xcd);
				    lcd_data(48+(j/10));
					lcd_command(0xce);
					lcd_data(48+(j%10));
					_delay_ms(200);
                }
          }
     }


}
