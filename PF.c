#include <mega16.h>
#include <stdlib.h>
#include <stdio.h>
#include <delay.h>
#include <math.h>


//definition of sensor
bit i_ok;
#define c  PINA.7
#define c1 PINB.0

#define l1 PINA.6
#define l2 PINA.5
#define l3 PINA.4
#define l4 PINA.3
#define l5 PINA.2
#define l6 PINA.1
#define l7 PINA.0
#define r1 PINB.1
#define r2 PINB.2
#define r3 PINB.3
#define r4 PINB.4
#define r5 PINB.5
#define r6 PINB.6
#define r7 PINB.7

#define right r1 + (r2 * 2) + (r3 * 4) + (r4 * 8) + (r5 * 16) + (r6 * 32) + (r7 * 64)  
#define left  l1 + (l2 * 2) + (l3 * 4) + (l4 * 8) + (l5 * 16) + (l6 * 32) + (l7 * 64)


#define stop 15

bit f=0,k=1;

int pwm[8]={70,30,0,0,0,-120,-140,-200};

//definition of Motor Control Function
void rightm(int pwm_r)
{
  if (pwm_r > 0)
    {
 OCR1BH = 0x00;
 OCR1BL = pwm_r;
 PORTD.2 = 0;
 PORTD.3 = 1;
    }
  if(pwm_r < 0)
    {
 OCR1BH = 0x00;
 OCR1BL = abs(pwm_r);
 PORTD.2 = 1;
 PORTD.3 = 0;
    }
  if(pwm_r == 0)
    {
 OCR1BH = 0x00;
 OCR1BL = 0x00;
 PORTD.2 = 0;
 PORTD.3 = 0;
    }
}

void leftm(int pwm_l)
{
  if (pwm_l > 0)
   {
   OCR1AH = 0x00;
   OCR1AL = pwm_l;
   PORTD.7 = 0;
   PORTD.6 = 1;
   }
   if(pwm_l < 0)
   {
   OCR1AH = 0x00;
   OCR1AL = abs(pwm_l);
   PORTD.7 = 1;
   PORTD.6 = 0;
   }
   if(pwm_l == 0)
   {
   OCR1AH = 0x00;
   OCR1AL = 0x00;
   PORTD.7 = 0;
   PORTD.6 = 0;
   }
}


bit invert=0;



void move(int pwm_l,int pwm_r)
    {
    if(pwm_l>0)
        {
        OCR1AH=0x00;
        OCR1AL=pwm_l;
        PORTD.6=0;
        PORTD.7=1;
        }
    if(pwm_l<0)
        {
        OCR1AH=0x00;
        OCR1AL=abs(pwm_l);
        PORTD.6=1;
        PORTD.7=0;
        }
    if(pwm_l==0)
        {
        OCR1AH=0x00;
        OCR1AL=0x00;
        PORTD.6=0;
        PORTD.7=0;
        }
    if(pwm_r>0)
        {
        OCR1BH=0x00;
        OCR1BL=pwm_r;
        PORTD.2=1;
        PORTD.3=0;
        }
    if(pwm_r<0)
        {
        OCR1BH=0x00;
        OCR1BL=abs(pwm_r);
        PORTD.2=0;
        PORTD.3=1;
        }
    if(pwm_r==0)
        {
        OCR1BH=0x00;
        OCR1BL=0x00;
        PORTD.2=0;
        PORTD.3=0;
        }

    }
    
    
    
    unsigned char scan_invert (void)
{
if (( r5 && r6 && r7) && (l5 && l6  && l7))

    {
    if  (!c || !r1 || !r2 || !l1 ||!l2 || !l1 || !r3) invert=1;
    }
else if((right<=4 && left<=4)&&(c || r1 || r2)) invert=0;

return invert;
}





void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTB=0x00;
DDRB=0x00;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTC=0x00;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
PORTD=0x00;
DDRD=0xFC;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Ph. correct PWM top=00FFh
// OC1A output: Non-Inv.
// OC1B output: Non-Inv.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0xA1;
TCCR1B=0x0D;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=FFh
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// LCD module initialization


while (1)
      {
        while(c || c1)
        {
        //if (scan_invert()==1) invert_sens();
        rightm(255);
        leftm(255);
        k=1;
        }
        while (scan_invert()==1)
            {
        rightm(0);
        leftm(0);

            }
        rightm(230);
        leftm(230);
        
        
        while (left>=1 && right<2)
        {
              while (scan_invert()==1)
            {
        rightm(0);
        leftm(0);

            }
            if(left>=4) k=0;
            else k=1;
            
          if(left == 1)
             {
               if(f==0)
                {
             rightm(200);
             leftm(-200);
             delay_ms(stop);
                }
                //f=1;              
             if(c || c1) break;
             rightm(255);
             if(k==0) leftm(pwm[0]);
             else leftm(150);
             }
           if(left==2)
               {
               if(f==0)
                  {
                  rightm(200);
                  leftm(-200);
                  delay_ms(stop);
                  }
               //f=1;
               rightm(255);
               if (k==0) leftm(pwm[1]);
               else leftm(100);
               }
               
           else if (left<=4)
               {
               if(f==0)
                 {
                  rightm(200);
                  leftm(-200);
                  delay_ms(stop);
                 }
              //f=1;
              rightm(255);
              leftm(pwm[2]);
              }
              
           else if(left<=8)
           {
           //f=1;
           rightm(255);
           leftm(pwm[3]);
           }
           
           
           else if(left<=31)
           {
           //f=1;
           rightm(255);
           leftm(pwm[4]);
           }
           
           
        else
        {
        //f=0;
        rightm(230);
        leftm(230);
        }
        
        if(left==32 && f==0)
        {
        rightm(-200);
        leftm(-200);
        rightm(150);
        leftm(pwm[5]);
        while(!l1 && !c && !c1);
        rightm(-255);
        leftm(255);
        delay_ms(stop);
        rightm(255);
        leftm(255);
        }
        
        
      if (left<=64 && left>=32 && f==0);
         {
         rightm(-200);
         leftm(-200);
         rightm(200);
         leftm(pwm[6]);
         while (!l1 && !c && !c1);
         rightm(-255);
         leftm(255);
         delay_ms(stop);
         rightm(255);
         leftm(255);
         }
         
       if (left<=128 && left>64 && f==0)
          {
           rightm(-200);
           leftm(-200);
           delay_ms(7);
           rightm(200);
           leftm(pwm[7]);
           while(!l1 && !c && !c1);
           rightm(-255);
           leftm(255);
           delay_ms(stop+15);
           rightm(255);
           leftm(255);
           }
           
    }
     
              
       while (right>=1 && left<2)
         {
         if (right>=3) k=0;
         else k=1;
         
        while (scan_invert()==1)
            {
        rightm(0);
        leftm(0);
            }
        if(right==1)
           {
        if(f==0)
           {
           rightm(-200);
           leftm(200);
           delay_ms(stop);
           }
          //f=1;
          if(c || c1) break;
          if(k==0) rightm(pwm[0]);
          else rightm(150);
          leftm(255);
          }
          
         if(right==2)
            {
            if(f==0)
               {
               rightm(-200);
               leftm(200);
               delay_ms(stop);
               }
            //f=1;
            if(k==0) rightm(pwm[1]);
            else rightm(80);
            leftm(255);
            }
            
            
        else if(right<=4)
           {
           if(f==0)
               {
               rightm(-200);
               leftm(200);
               delay_ms(stop);
               }
               
           //f=1;
           rightm(pwm[2]);
           leftm(255);
           }
           
        else if (right<=8)
           {
           //f=1;
           rightm(pwm[3]);
           leftm(255);
           }
           
        else if(right<=31)
            {
            //f=1;
            rightm(pwm[4]);
            leftm(255);
            }
        else
            {
            //f=0;
            rightm(230);
            leftm(230);
            }
            
        if(right==32 && f==0)
            {
            rightm(-200);
            leftm(200);
            rightm(pwm[5]);
            leftm(150);
            while(!r1 && !c && !c1);
            rightm(255);
            leftm(-255);
            delay_ms(stop);
            rightm(255);
            leftm(255);
            }
            
       if (right<=64 && right>32 && f==0)
           {
           rightm(-200);
           leftm(-200);
           rightm(pwm[6]);
           leftm(200);
           while (!r1 && !c && !c1);
           rightm(255);
           leftm(-255);
           delay_ms(stop);
           rightm(255);
           leftm(255);
           }
           
       if (right<=128 && right>64 && f==0);
          {                    
          rightm(-200);
          leftm(-200);
          delay_ms(7);
          rightm(pwm[7]);
          leftm(200);
          while (!r1 && !c && !c1);
          rightm(255);
          leftm(-255);
          delay_ms(stop+15);
          rightm(255);
          leftm(255);
          }
          
    }
          
           
           
            
        
                   
               
                  
                        
        
      };
}
