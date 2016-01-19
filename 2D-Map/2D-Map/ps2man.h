/*
 * ps2man.h
 *
 * Created: 1/16/2013 11:17:08 PM
 *  Author: AbisTarun
 */ 


#ifndef PS2MAN_H_
#define PS2MAN_H_
#define window 15


unsigned int p1, p2, p3, p4;
unsigned int pot1_1=0,pot1_2=0,fwd_rev_l=0,fwd_rev_r=0;
unsigned char i,input_1,input_2;
signed int my_speed_l,my_speed_r,max_speed_f=255,max_speed_b=255,max_speed_lt=255,max_speed_rt=255,max_speed_r=255,fine_speed_b=255,fine_speed_f=255,fine_speed_r=255;


unsigned int ADC_analog(unsigned char channel)
{
ADCSRA|=((1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
ADMUX=channel;
set(ADCSRA,ADSC);

while(chk(ADCSRA,ADSC));
glow1();
return(ADC);

}

void enable_ps2()
	{
	DDRF=0x00;
	PORTF=0x55;
	DDRD=0x00;
	PORTD=0xFF;
	}


void drive_fb_using_adc_fb(void)
{
		pot1_1=ADC_analog(7);
		pot1_2=ADC_analog(3);
//	LCDvar(0,1,pot1_1,4);
//	LCDvar(5,1,pot1_2,4);
		
		if((pot1_1<fwd_rev_l-window) && (pot1_2<fwd_rev_r-window))
		{

			my_speed_l=(fwd_rev_l - pot1_1)/2;
			my_speed_r=(fwd_rev_r - pot1_2)/2;
			if(my_speed_l > max_speed_b)
			{
				my_speed_l=max_speed_b;
			}
			if(my_speed_r>max_speed_b)
			{
				my_speed_r=max_speed_b;
			}
			

			drive_fb(-my_speed_l,-my_speed_r);
		//	LCD(1,0,"bckb");
		}


		else if((pot1_1<(fwd_rev_l+ window) && pot1_1>=(fwd_rev_l-window)) && (pot1_2<(fwd_rev_r+window) && pot1_2>=(fwd_rev_r-window)))
		{
			drive_fb(0,0);
		//	LCD(1,0,"stpb");
		}

		else if((pot1_1>=fwd_rev_l+window) && (pot1_2>=fwd_rev_r+window))
		{
			my_speed_l=(pot1_1-fwd_rev_l)/2;
			my_speed_r=(pot1_2-fwd_rev_r)/2;
			if(my_speed_l>max_speed_f)
			{
				my_speed_l=max_speed_f;
			}
			if(my_speed_r>max_speed_f)
			{
				my_speed_r=max_speed_f-15;
			}
			

			drive_fb(my_speed_l,my_speed_r);
		//	LCD(1,0,"fwdb");
		}
		
		else if((pot1_1>=fwd_rev_l+window) && (pot1_2<(fwd_rev_r+window) && pot1_2>=(fwd_rev_r-window)))
		{
			my_speed_l=(pot1_1-fwd_rev_l)/2;
			if(my_speed_l>max_speed_lt)
			{
				my_speed_l=max_speed_lt;
			}
			

			drive_fb(my_speed_l,0);
		//	LCD(1,0,"fwdl");
		}


		else if((pot1_2>=fwd_rev_r+window) && (pot1_1<(fwd_rev_l+window) && pot1_1>=(fwd_rev_l-window)))
		{
			my_speed_r=(pot1_2-fwd_rev_r)/2;
			if(my_speed_r>max_speed_rt)
			{
				my_speed_r=max_speed_rt;
			}
			

			drive_fb(0,my_speed_r);
		//	LCD(1,0,"fwdr");
		}


		else if((pot1_1<fwd_rev_l-window) && (pot1_2<(fwd_rev_r+window) && pot1_2>=(fwd_rev_r-window)))
		{
			my_speed_l=(fwd_rev_l-pot1_1)/2;
			if(my_speed_l>max_speed_b)
			{
				my_speed_l=(max_speed_b+20);
			}
			
			drive_fb(-my_speed_l,0);
		//	LCD(1,0,"bckl");
		}


		else if((pot1_2<fwd_rev_r-window) && (pot1_1<(fwd_rev_l+window) && pot1_1>=(fwd_rev_l-window)))
		{
			my_speed_r=(fwd_rev_r-pot1_2)/2;
			if(my_speed_r>max_speed_b)
			{
				my_speed_r=(max_speed_b+25);
			}
			
			drive_fb(0,-my_speed_r);
	//		LCD(1,0,"bckr");
		}

		else if((pot1_1<fwd_rev_l-window) && (pot1_2>=fwd_rev_r+window))
		{

			my_speed_l=(fwd_rev_l-pot1_1)/2;
			my_speed_r=(pot1_2-fwd_rev_r)/2;
			if(my_speed_l>max_speed_r)
			{
				my_speed_l=max_speed_r;
			}
			if(my_speed_r>max_speed_r)
			{
				my_speed_r=max_speed_r;
			}
			

			drive_fb(-my_speed_l,my_speed_r);
		//	LCD(1,0,"l-r+");
		
		}

		else if((pot1_1>=fwd_rev_l+window) && (pot1_2<fwd_rev_r-window))
		{

			my_speed_l=(pot1_1-fwd_rev_l)/2;
			my_speed_r=(fwd_rev_r-pot1_2)/2;
			if(my_speed_l>max_speed_r)
			{
				my_speed_l=max_speed_r;
			}
			if(my_speed_r>max_speed_r)
			{
				my_speed_r=max_speed_r;
			}
			

			drive_fb(my_speed_l,-my_speed_r);
	//		LCD(1,0,"l+r-");
		
		}

		else 
		{
		drive_fb(0,0);
	
//		LCD(1,0,"stpb");
		
		}
}
void drive_lr_using_adc_lr(void)
{
		pot1_1=ADC_analog(7);
		pot1_2=ADC_analog(3);
//	LCDvar(0,1,pot1_1,4);
//	LCDvar(5,1,pot1_2,4);
		
		if((pot1_1<fwd_rev_l-window) && (pot1_2<fwd_rev_r-window))
		{

			my_speed_l=(fwd_rev_l-pot1_1)/2;
			my_speed_r=(fwd_rev_r-pot1_2)/2;
			if(my_speed_l>max_speed_b)
			{
				my_speed_l=max_speed_b;
			}
			if(my_speed_r>max_speed_b)
			{
				my_speed_r=max_speed_b;
			}
			

			drive_lr(-my_speed_l,-my_speed_r);
		//	LCD(1,0,"bckb");
		}


		else if((pot1_1<(fwd_rev_l+window) && pot1_1>=(fwd_rev_l-window)) && (pot1_2<(fwd_rev_r+window) && pot1_2>=(fwd_rev_r-window)))
		{
			drive_lr(0,0);
		//	LCD(1,0,"stpb");
		}

		else if((pot1_1>=fwd_rev_l+window) && (pot1_2>=fwd_rev_r+window))
		{
			my_speed_l=(pot1_1-fwd_rev_l)/2;
			my_speed_r=(pot1_2-fwd_rev_r)/2;
			if(my_speed_l>max_speed_f)
			{
				my_speed_l=max_speed_f;
			}
			if(my_speed_r>max_speed_f)
			{
				my_speed_r=max_speed_f-15;
			}
			

			drive_lr(my_speed_l,my_speed_r);
		//	LCD(1,0,"fwdb");
		}
		
		else if((pot1_1>=fwd_rev_l+window) && (pot1_2<(fwd_rev_r+window) && pot1_2>=(fwd_rev_r-window)))
		{
			my_speed_l=(pot1_1-fwd_rev_l)/2;
			if(my_speed_l>max_speed_lt)
			{
				my_speed_l=max_speed_lt;
			}
			

			drive_lr(my_speed_l,0);
		//	LCD(1,0,"fwdl");
		}


		else if((pot1_2>=fwd_rev_r+window) && (pot1_1<(fwd_rev_l+window) && pot1_1>=(fwd_rev_l-window)))
		{
			my_speed_r=(pot1_2-fwd_rev_r)/2;
			if(my_speed_r>max_speed_rt)
			{
				my_speed_r=max_speed_rt;
			}
			

			drive_lr(0,my_speed_r);
		//	LCD(1,0,"fwdr");
		}


		else if((pot1_1<fwd_rev_l-window) && (pot1_2<(fwd_rev_r+window) && pot1_2>=(fwd_rev_r-window)))
		{
			my_speed_l=(fwd_rev_l-pot1_1)/2;
			if(my_speed_l>max_speed_b)
			{
				my_speed_l=(max_speed_b+20);
			}
			
			drive_lr(-my_speed_l,0);
		//	LCD(1,0,"bckl");
		}


		else if((pot1_2<fwd_rev_r-window) && (pot1_1<(fwd_rev_l+window) && pot1_1>=(fwd_rev_l-window)))
		{
			my_speed_r=(fwd_rev_r-pot1_2)/2;
			if(my_speed_r>max_speed_b)
			{
				my_speed_r=(max_speed_b+25);
			}
			
			drive_lr(0,-my_speed_r);
	//		LCD(1,0,"bckr");
		}

		else if((pot1_1<fwd_rev_l-window) && (pot1_2>=fwd_rev_r+window))
		{

			my_speed_l=(fwd_rev_l-pot1_1)/2;
			my_speed_r=(pot1_2-fwd_rev_r)/2;
			if(my_speed_l>max_speed_r)
			{
				my_speed_l=max_speed_r;
			}
			if(my_speed_r>max_speed_r)
			{
				my_speed_r=max_speed_r;
			}
			

			drive_lr(-my_speed_l,my_speed_r);
		//	LCD(1,0,"l-r+");
		
		}

		else if((pot1_1>=fwd_rev_l+window) && (pot1_2<fwd_rev_r-window))
		{

			my_speed_l=(pot1_1-fwd_rev_l)/2;
			my_speed_r=(fwd_rev_r-pot1_2)/2;
			if(my_speed_l>max_speed_r)
			{
				my_speed_l=max_speed_r;
			}
			if(my_speed_r>max_speed_r)
			{
				my_speed_r=max_speed_r;
			}
			

			drive_lr(my_speed_l,-my_speed_r);
	//		LCD(1,0,"l+r-");
		
		}

		else 
		{
		drive_lr(0,0);
	
//		LCD(1,0,"stpb");
		
		}
}

void init_adc_mot(void)
{
	
	pot1_1=ADC_analog(7);
	pot1_2=ADC_analog(3);

	if(pot1_1>505 && pot1_1<525)
	{
	fwd_rev_l=pot1_1;
	}
	else
	{
	fwd_rev_l=5;
	glow2();
	}

	if(pot1_2>510 && pot1_2<525)
	{
	fwd_rev_r=pot1_2;
	}
	else
	{
	fwd_rev_r=514;
	glow3();
	}

}

void displcd()
{
	LCDvar(0,1,my_speed_l,4);
	_delay_ms(20);
	LCDvar(7,1,my_speed_r,4);
	_delay_ms(20);
	
}
void manualps2()
{
	InitMotors();
	init_t0();
	init_t1();
	InitLCD(0);
	LCDClear();
	_delay_ms(20);
	//LCD(1,1,"hi");
	enable_ps2();
    init_adc_mot();
	while(1)
    {
		p2=ADC_analog(3);
		p4=ADC_analog(7);
		_delay_ms(10);
		LCDvar(0,0,p2,4);
		_delay_ms(10);
		LCDvar(7,0,p4,4);
		//_delay_ms(20);
		if(chk(PINF,0))
		drive_fb_using_adc_fb();
		else
		drive_lr_using_adc_lr();
		displcd();
        //TODO:: Please write your application code 
    }
}

#endif /* PS2MAN_H_ */