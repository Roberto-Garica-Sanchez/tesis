// Dc motor control with PIC18F4550 CCS C code
 
#include <18F4550.h>
#device ADC = 10
#fuses NOMCLR INTRC_IO
#use delay(clock = 8000000)
#use fast_io(B)
#use fast_io(C)
#use fast_io(D)
 
unsigned int16 i ;
void main(){
  setup_oscillator(OSC_8MHZ);            // Set internal oscillator to 8MHz
  port_b_pullups(TRUE);                  // Enable PORTB pull-ups
  output_b(0);                           // PORTB initial state
  set_tris_b(7);                         // Configure RB0, RB1 & RB2 as inputs
  output_c(0);                           // PORTC initial state
  set_tris_c(0);                         // Configure PORTC pins as outputs
  output_d(0);                           // PORTD initial state
  set_tris_d(0);                         // Configure PORTD pins as outputs
  setup_adc(ADC_CLOCK_DIV_8);            // Set ADC conversion time to 8Tosc
  setup_adc_ports(AN0);                  // Configure AN0 as analog input
  set_adc_channel(0);                    // Select channel AN0
  setup_timer_2(T2_DIV_BY_16, 250, 1);   // Set PWM frequency to 500Hz
  delay_ms(100);                         // Wait 100ms
  while(TRUE){
    i = read_adc();                      // leee AN0 y lo almacena en i 
    set_pwm1_duty(i);                    // Set pwm1 duty cycle
    delay_ms(10);                        // Wait 10ms
    if(input(PIN_B0) == 0){              // If RB0 button pressed[isquierda] 
      if(input(PIN_B3) == 0){            // If direction 1 not already selected[led]
            output_b(0);                     // Both LEDs OFF
            setup_ccp1(CCP_OFF);             // CCP1 OFF
            output_c(0);                     // PORTC pins low
            output_d(0);                     // PORTD pins low
            delay_ms(100);                   // Wait 100ms
            setup_ccp1(CCP_PWM | CCP_PWM_FULL_BRIDGE);
                                            // Configure CCP1 as a PWM output forward
            output_high(PIN_B3);             // RB3 LED ON
        }
    }
    if(input(PIN_B1) == 0){              // If RB1 button pressed[derecha]
      if(input(PIN_B4) == 0){            // If direction 2 not already selected[led]
            output_b(0);                     // Both LEDs OFF
            setup_ccp1(CCP_OFF);             // CCP1 OFF
            output_c(0);                     // PORTC pins low
            output_d(0);                     // PORTD pins low
            delay_ms(100);                   // Wait 100ms
            setup_ccp1(CCP_PWM | CCP_PWM_FULL_BRIDGE_REV);
                                            // Configure CCP1 para multiplexado 
            output_high(PIN_B4);             // RB4 LED ON
        }
    }
    if(input(PIN_B2) == 0){              // If RB2 button pressed[STOP]
      setup_ccp1(CCP_OFF);               // CCP1 OFF
      output_b(0);                       // Both LEDs OFF
      output_c(0);                       // PORTC pins low
      output_d(0);                       // PORTD pins low
      }
   }
}
