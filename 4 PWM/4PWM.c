// PIC18F4550 Full-Bridge mode EPWM example CCS C code
 
#include <18F4550.h>
#device ADC = 10
#fuses NOMCLR INTRC_IO
#use delay(clock = 4000000)
 
short mode;
unsigned int16 i ;
void main(){
  setup_oscillator(OSC_8MHZ);            // Set internal oscillator to 8MHz
  setup_adc(ADC_CLOCK_DIV_8);            // Set ADC conversion time to 8Tosc
  setup_adc_ports(AN0);                  // Configure AN0 as analog input
  set_adc_channel(0);                    // Select channel AN0
  setup_timer_2(T2_DIV_BY_16, 250, 1);   // Set PWM frequency to 500Hz
  delay_ms(100);        
  setup_ccp1(CCP_PWM | CCP_PWM_FULL_BRIDGE);                  // Wait 100ms
  while(TRUE){
    if(input(PIN_B0) == 0){
      mode = ~mode;                      // Toggle mode variable
      if(mode == 1){
        setup_ccp1(CCP_PWM | CCP_PWM_FULL_BRIDGE); // Forward output mode
      }else{
        setup_ccp1(CCP_PWM | CCP_PWM_FULL_BRIDGE_REV); // Reverse output mode
      }
      delay_ms(500);
    }
    i = read_adc();                      // Read from AN0 and store in i
    set_pwm1_duty(i);                    // Set pwm1 duty cycle to i
    delay_ms(10);                         // Wait 1ms
   }
}