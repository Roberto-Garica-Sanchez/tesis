
#include <18F4550.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000) 
#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)
#USE STANDARD_IO(E)

float32 duty=0;
float32 temp,a,b,c;
int Timer2,Poscaler;
int cambio,giro=1;
float32 map(float32 valor, float32 entradaMin, float32 entradaMax, float32 salidaMin, float32 salidaMax)    
{                                
    return ((((valor-entradaMin)*(salidaMax-salidaMin))/(entradaMax-entradaMin))+salidaMin); 
}  
void main() { 
   // Generemos una Señal cuadrada de 1 Khz
   Timer2=249;    //Se carga timer 2 con 249 como lo vimos en la pagina
   //Preescaler=4;  //Preescaler solo puede tomar valores de: 1 - 4 - 16
   //Para el preescaler colocamos "t2_div_by_4"
   Poscaler=1;  //Preescaler solo puede tomar valores de: 1
   
   setup_timer_2(t2_div_by_4,Timer2,Poscaler);   //Configuracion de Timer 2 para establecer frec. PWM a 1kHz
   setup_ccp1(ccp_pwm);                //Configurar modulo CCP1 en modo PWM
   setup_ccp2(ccp_pwm);                //Configurar modulo CCP1 en modo PWM
   setup_adc_ports(all_analog);        //Configurar ADC configuracion de los puertos que funcionan en analogico 
   setup_adc(adc_clock_internal);
   while(true){
      cambio=INPUT(PIN_C0);
      if(cambio==1){
            while (INPUT(PIN_C0)){}
            if(giro==1){giro=2;}else{giro=1;
         }
         
      }
      if(giro==1){  
         set_adc_channel(0);        //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
         delay_us(100);       
         a=read_adc();               //leer         
         set_pwm1_duty(a);           //write salida de señal PWM 
         output_high(PIN_B1);
      }else{output_low(PIN_B1); set_pwm1_duty(0);}
      if(giro==2){
         set_adc_channel(1);        //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
         delay_us(100);       
         a=read_adc();               //leer         
         set_pwm2_duty(a);           //write salida de señal PWM          
         output_high(PIN_B2);
      }else{output_low(PIN_B2);set_pwm2_duty(0);}
   }
}
