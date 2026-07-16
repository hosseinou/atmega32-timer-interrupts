#include <mega32.h> 
#include <lcd.h>
#include <delay.h>
#include <stdio.h>
#asm
     .equ __lcd_port=0x1B ;PORTA
#endasm
bit pulse_enable=1;
 // External Interrupt 0 service routine
interrupt [EXT_INT1] void ext_int0_isr(void) 
{
  // Place your code here 
   pulse_enable=0; 
}
 // Timer1 output compare A interrupt service routine 
 interrupt [TIM1_COMPA] void timer1_compa_isr(void)
 {
     if(!pulse_enable){
                       DDRB=0x04;
                       PORTB.2=1;
                       }
     else{
        if (PORTB.2==1)PORTB.2=0;
        else PORTB.2=1; 
        }
 }       
 
void main(void)
{
char lcd_buffer[16];                 
unsigned char timer0;
 // Input/Output Ports initialization
 // Port B initialization
 PORTB=0x00;
 DDRB=0x04;
 // Timer/Counter 0 initialization
 // Clock source: T0 pin Falling Edge
 // Mode: Normal top=0xFF
 // OC0 output: Disconnected
 TCCR0=0xFF;
 TCNT0=0x00;
 OCR0=0x00;
 // Timer/Counter 1 initialization
 // Clock source: System Clock
 // Clock value: 1000.000 kHz
 // Mode: Normal top=0xFFFF
 // OC1A output: Discon.
 // OC1B output: Discon.
 // Noise Canceler: Off
 // Input Capture on Falling Edge
 // Timer1 Overflow Interrupt: Off 
 // Input Capture Interrupt: Off
 // Compare A Match Interrupt: On 
 // Compare B Match Interrupt: Off 
 TCCR1A=0x00;
 TCCR1B=0x01;
 TCNT1H=0x00;
 TCNT1L=0x00;
 ICR1H=0x00;
 ICR1L=0x00;
 OCR1AH=0x01;
 OCR1AL=0xF3;
 OCR1BH=0x00;
 OCR1BL=0x00;
 // External Interrupt(s) initialization
 // INT0: On
 // INT0 Mode: Falling Edge
 // INT1: Off
 // INT2: Off
 GICR|=0x40;
 MCUCR=0x02;
 MCUCSR=0x00;
 GIFR=0x40;
 // Timer(s)/Counter(s) Interrupt(s) initialization
 TIMSK=0x10;
 TWCR=0x00;
 lcd_init(16);
 // Global enable interrupts
 #asm("sei")
 while (1)
 {
 // Place your code here
 timer0=TCNT0;
 lcd_clear();
 sprintf(lcd_buffer,"Timer0 Value: %d",timer0);
 lcd_gotoxy(0,0);
 lcd_puts(lcd_buffer);
 delay_ms(500);
 }
 }