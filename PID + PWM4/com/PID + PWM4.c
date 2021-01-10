
#include <18F4550.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000)  

int16 duty=0;
int16 temp,a,b,c;
int Timer2,Poscaler;
double map(float valor, float entradaMin, float entradaMax, float salidaMin, float salidaMax)    
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
         
            set_adc_channel(0);        //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
            delay_us(10);       
            a=read_adc();               //leer
            


            set_adc_channel(1);        //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
            delay_us(10);       
            b=read_adc();               //leer
            


            //realiza una comprobacion de el sentido de giro para configurar el pulso pwm, y evitar errores de ejecuion 
            if (a>b) {
               output_high(PIN_B0);         //led indicador de sentido de giro 
                    //setup_ccp1(CCP_OFF);             // CCP1 OFF
                    delay_us(10);                   // tiempo de espera para evitar errores en el modulo 
                    //setup_ccp1(CCP_PWM | CCP_PWM_FULL_BRIDGE);                    
                    c=b-a;
                    set_pwm1_duty(b);           //write salida de señal PWM 
                    //set_pwm2_duty(a);           //write salida de señal PWM 
            }else{output_low(PIN_B0);}
            if (a<b) {
               output_high(PIN_B1);
            }else{output_low(PIN_B1);}

    
      
         
   }
}