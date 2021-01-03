
#include <18F4520.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000)  

int16 duty=0;
int Timer2,Poscaler;

void main() { 
   // Generemos una Señal cuadrada de 1 Khz
   Timer2=249;    //Se carga timer 2 con 249 como lo vimos en la pagina
   //Preescaler=4;  //Preescaler solo puede tomar valores de: 1 - 4 - 16
   //Para el preescaler colocamos "t2_div_by_4"
   Poscaler=1;  //Preescaler solo puede tomar valores de: 1
   
   setup_timer_2(t2_div_by_4,Timer2,Poscaler);   //Configuracion de Timer 2 para establecer frec. PWM a 1kHz
   setup_ccp1(ccp_pwm);                //Configurar modulo CCP1 en modo PWM
   setup_adc_ports(all_analog);        //Configurar ADC configuracion de los puertos que funcionan en analogico 
   setup_adc(adc_clock_internal);
   while(1)
   {
        set_adc_channel(0);            //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
        delay_us(100);       
        duty=read_adc();               //leer
        set_pwm1_duty(duty);           //write salida
   }
}
/*
# include <18F4520.h>             //incluimos el codigo del pic
#device adc=8                    //Habilitamos el disppositivos a 8bits
#fuses hs, wdt, brownout,NOWDT   //incluimos los fusibles necesarios
#use delay (clock = 8M)          //usamos reloj de 8Mhz
#use standard_io (a,b,c,d)       //usamos la configuracion estandar
float  bits_analog;               
void main (){
   setup_adc_ports (AN0);  // habilitamos los puetos analogicos
   setup_adc(adc_clock_div_16);           // habilitamos los puetos analogicos
   setup_ccp1(CCP_PWM);                   // habilitamos el puerto ccp1 del pic
   setup_timer_2(T2_DIV_BY_16, 255,1);    // usamos el timer2 
      while (true){
      set_adc_channel(0);    
      delay_ms (2);                    // Selecciono el canal 0 (RA0)
      bits_analog = read_adc();     
         delay_ms (2);
         set_pwm1_duty (bits_analog);  // manifestamos los valores de AN0 en cc_pwm)
         delay_ms (2);
      }
}
*/