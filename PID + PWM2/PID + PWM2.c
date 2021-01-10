
#include <18F4550.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000) 
#INCLUDE <LCD.C>
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
//bits
unsigned int16 bits_SetPoint=0;
unsigned int16 bits_PocitionReal=0;
unsigned int16 bits_difer=0;
unsigned int16 bits_RES=0;

//variable temporales 
//int16 temp,a,b,c;
//VAR PWM
int16 duty=0;
int Timer2,Poscaler;
//VAR motor 
int cambio,giro=1;//giro 1 si es negativos los valores 
//#########     PID
float Var_SetPoint=0;
float Var_PocitionReal=0;
float Var_error_0=0;
float Var_error_1=0;
float Var_error_2=0;
float a,b,c;            //variables temporales
float t=1;              //periodo de muestreo 
int k=0;              //contrador de muestras
float Var_res_0;            //Salidas
float Var_res_1;            //Salidas
//#########    ganancias
float kp=1;               //proporcional
float kd=0.2;               //Derivativa
float ki=0.2;               //integral


float32 map(float32 valor, float32 entradaMin, float32 entradaMax, float32 salidaMin, float32 salidaMax)    
{                                
    return ((((valor-entradaMin)*(salidaMax-salidaMin))/(entradaMax-entradaMin))+salidaMin); 
}  
void main() { 
   Timer2=249;    //Se carga timer 2 con 249
   Poscaler=1;  //Preescaler solo puede tomar valores de: 1
   
   setup_timer_2(t2_div_by_4,Timer2,Poscaler);   //Configuracion de Timer 2 para establecer frec. PWM a 1kHz
   setup_ccp1(ccp_pwm);                //Configurar modulo CCP1 en modo PWM
   setup_ccp2(ccp_pwm);                //Configurar modulo CCP2 en modo PWM
   setup_adc_ports(all_analog);        //Configurar ADC configuracion de los puertos que funcionan en analogico 
   setup_adc(adc_clock_internal);
   
   LCD_INIT();       //Inicializa el LCD
   LCD_PUTC("\f");   //Borrar el contenido del LCD
   while(true){
      //leer setpoint 
         set_adc_channel(PIN_SetPoint);            //selecciona valore deseado setpoint  
         delay_us(100);       
         bits_SetPoint=read_adc();   
      //leer posicion real 
         set_adc_channel(PIN_PocitionReal);        //seleciona la posicion real 
         delay_us(100);       
         bits_PocitionReal=read_adc();               //leer            
      //calculos 
         //convierte loas bits en voltaje 
         Var_SetPoint      = (5.0*bits_SetPoint)/1024.0;
         Var_PocitionReal  = (5.0*bits_PocitionReal)/1024.0;
         bits_difer=bits_PocitionReal-bits_SetPoint;
         //diferencia de voltaje 
         c=Var_PocitionReal-Var_SetPoint;
         //PID Calculos //muestreo
            Var_error_2=Var_error_1;
            Var_error_2=Var_error_0;  
            Var_error_0=Var_PocitionReal-Var_SetPoint;
            
        //calculo
            
            a=Var_error_0  *( kp + (ki*t) )+( kd/t );
            b=Var_error_1*( (-2*(kd/t) - kp) );
            c=Var_error_2*( (kd/t) +Var_res_1 );
            Var_res_1=Var_res_0;
            Var_res_0=a+b+c;
            
         //conversion para PWM
         if(Var_res_0<0){//control de giro 
            Var_res_0=Var_res_0*-1;
            giro=2;
         }else{giro=1;}
         if(Var_res_0>=4.90){//control contra desvordamiento 
            Var_res_0=4.99;
         }
         bits_RES      = (1024*Var_res_0)/5;
         //incremento en contrador 
            k=k+1;
                   
      //interface
      LCD_GOTOXY(1,1);       
      /*
      printf(lcd_putc," %4Lu",bits_SetPoint);  
      printf(lcd_putc," %4Lu",bits_PocitionReal);  
      printf(lcd_putc," %4Lu",bits_difer);  
      */
      printf(lcd_putc," %4Lu",bits_difer); lcd_putc("b");  
      printf(lcd_putc," %f",Var_error_0); lcd_putc("V");   
      LCD_GOTOXY(1,2);        
      printf(lcd_putc," %4Lu",bits_RES);  lcd_putc("b");      
      printf(lcd_putc," %f",Var_res_0);   lcd_putc("V");   
      delay_ms(100);
      LCD_PUTC("\f");   //Borrar el contenido del LCD  
      
      //printf(lcd_putc," %i",k);            
      //printf(lcd_putc," %f",c);            
      // EL SISGUIENTE CODIGO SE ENCARGA DE CONVERTIR el valor de salida del pid en 
      //valores validos para el puente h de dos hilos 
      //el sentido de giro se definira por el signo ->0<+
      
      
      if(Var_PocitionReal<Var_SetPoint){//valores positivos 
         c=Var_SetPoint-Var_PocitionReal;
         set_pwm1_duty(bits_RES);            //write salida de señal PWM 
         output_high(PIN_B1);                //led indicador de giro 
      }else{
         output_low(PIN_B1); 
         set_pwm1_duty(0);
         }
      if(Var_PocitionReal>Var_SetPoint){     //valores negativos 
         c=Var_PocitionReal-Var_SetPoint;
         set_pwm2_duty(bits_RES);            //write salida de señal PWM          
         output_high(PIN_B2);                //led indicador de giro 
      }else{
         output_low(PIN_B2);
         set_pwm2_duty(0);
      } //si el sentido de giro no corresponde apaga el led y PWM
      if(Var_SetPoint==Var_PocitionReal){
         set_pwm2_duty(0);
         set_pwm1_duty(0);
      }
      
     
   }
}

