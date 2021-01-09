
#include <18F4550.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000) 
#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)
#USE STANDARD_IO(E)
//configuracion entradas/salidas
//entradas
   #define PIN_SetPoint  0    //[AN0]setpoint      set_adc_channel(0); set_adc_channel(PIN_SetPoint); 
   #define PIN_PocitionReal 1 //[AN1]posicion real set_adc_channel(1); set_adc_channel(PIN_PocitionReal); 
//salidas
    //control puenta H
        //Grupos de rotacion 
            //set_pwm1_duty() [RC2]
        //B
            //set_pwm1_duty() [RC3]
//var PID
int16 Var_SetPoint=0;
int16 Var_PocitionReal=0;

//variable temporales 
int16 temp,a,b,c;
//VAR PWM
int16 duty=0;
int Timer2,Poscaler;
//VAR motor 
int cambio,giro=1;
float32 map(float32 valor, float32 entradaMin, float32 entradaMax, float32 salidaMin, float32 salidaMax)    
{                                
    return ((((valor-entradaMin)*(salidaMax-salidaMin))/(entradaMax-entradaMin))+salidaMin); 
}  
void main() { 
   // Generemos una Se�al cuadrada de 1 Khz
   Timer2=249;    //Se carga timer 2 con 249
   //Preescaler=4;  //Preescaler solo puede tomar valores de: 1 - 4 - 16
   //Para el preescaler colocamos "t2_div_by_4"
   Poscaler=1;  //Preescaler solo puede tomar valores de: 1
   
   setup_timer_2(t2_div_by_4,Timer2,Poscaler);   //Configuracion de Timer 2 para establecer frec. PWM a 1kHz
   setup_ccp1(ccp_pwm);                //Configurar modulo CCP1 en modo PWM
   setup_ccp2(ccp_pwm);                //Configurar modulo CCP2 en modo PWM
   setup_adc_ports(all_analog);        //Configurar ADC configuracion de los puertos que funcionan en analogico 
   setup_adc(adc_clock_internal);
   while(true){
      /*
      cambio=INPUT(PIN_C0);
      if(cambio==1){
            while (INPUT(PIN_C0)){}
            if(giro==1){giro=2;}else{giro=1;
         }
         
      }
      */
         set_adc_channel(PIN_SetPoint);            //selecciona valore deseado setpoint  
         delay_us(100);       
         Var_SetPoint=read_adc();                             //leer   
         set_adc_channel(PIN_PocitionReal);        //seleciona la posicion real 
         delay_us(100);       
         Var_PocitionReal=read_adc();               //leer            
         //calculos 
         c=Var_PocitionReal-Var_SetPoint;
      // EL SISGUIENTE CODIGO SE ENCARGA DE CONVERTIR el valor de salida del pid en 
      //valores validos para el puente h de dos hilos 
      //el sentido de giro se definira por el signo ->0<+
      
      if(Var_PocitionReal<Var_SetPoint){     
         c=Var_SetPoint-Var_PocitionReal;
         set_pwm1_duty(c);          //write salida de señal PWM 
         output_high(PIN_B1);       //led indicador de giro 
      }else{output_low(PIN_B1); set_pwm1_duty(0);}
      if(Var_PocitionReal>Var_SetPoint){  
         c=Var_PocitionReal-Var_SetPoint;
         set_pwm2_duty(c);          //write salida de señal PWM          
         output_high(PIN_B2);       //led indicador de giro 
      }else{output_low(PIN_B2);set_pwm2_duty(0);} //si el sentido de giro no corresponde apaga el led y PWM
      if(Var_SetPoint==Var_PocitionReal){
         set_pwm2_duty(0);
         set_pwm1_duty(0);
      }
   }
}

