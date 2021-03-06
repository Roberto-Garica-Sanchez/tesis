
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
#include <PID_PWM2.h>
/*
//configuracion entradas/salidas
//entradas
   #define PIN_SetPoint  0    //[AN0]setpoint      set_adc_channel(0);
   #define PIN_PocitionReal 1 //[AN1]posicion real set_adc_channel(1);
//salidas
   //control puenta H
      //comando de control de giro del motor
            //set_pwm1_duty() [RC2]
            //set_pwm1_duty() [RC3]
//variables tipo bits
unsigned int16 bits_SetPoint=0;
unsigned int16 bits_PocitionReal=0;
unsigned int16 bits_difer=0;
unsigned int16 bits_RES=0;
//variable control PWM
int16 duty=0;
int Timer2,Poscaler;
//variable control giro motor 
int cambio,giro=1;//giro 1 si es negativos los valores 
//#########     PID
float Var_SetPoint=0;
float Var_PocitionReal=0;
float Var_error_0=0;
float Var_error_1=0;
float Var_error_2=0;
float a,b,c;               //variables temporales
float t=1;                 //periodo de muestreo 
int k=0;                   //contrador de muestras
float Var_res_0;           //Salidas
float Var_res_1;           //Salidas
//#########    ganancias
float kp=1;                //proporcional
float kd=0.2;              //Derivativa
float ki=0.2;              //integral
*/
void main() { 
   /*
   Timer2=249;    //Se carga timer 2 con 249
   Poscaler=1;  //Preescaler solo puede tomar valores de: 1
   //Configuracion de Timer 2 para establecer frec. PWM a 1kHz
   setup_timer_2(t2_div_by_4,Timer2,Poscaler);   
   setup_ccp1(ccp_pwm);      //Configurar modulo CCP1 en modo PWM
   setup_ccp2(ccp_pwm);      //Configurar modulo CCP2 en modo PWM
   //Configurar ADC configuracion 
   //de los puertos que funcionan en analogico 
   setup_adc_ports(all_analog);        
   setup_adc(adc_clock_internal);      
   */
   star_PWM_2HILOS();
   LCD_INIT();       //Inicializa el LCD
   LCD_PUTC("\f");   //Borrar el contenido del LCD
   while(true){
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
      /*
         //leer setpoint 
         set_adc_channel(PIN_SetPoint);//selecciona valore deseado setpoint  
=======
<<<<<<< HEAD:PID + PWM2/PID + PWM2.c
      //leer setpoint 
         set_adc_channel(PIN_SetPoint);            //selecciona valore deseado setpoint  
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
         delay_us(100);       
         bits_SetPoint=read_adc();   
         //leer posicion real 
         set_adc_channel(PIN_PocitionReal);  //seleciona la posicion real 
         delay_us(100);       
         bits_PocitionReal=read_adc();       //leer
      */   
      read_SetPoint();
      read_PocitionReal();
      conver_bits_to_vol_SetPoint();
      conver_bits_to_vol_PocitionReal();
      calculos_PID();
      control_sentido_giro();
      conver_vol_to_bits_res_PID();
      salidas_PWM();
      //calculos 
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
=======
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
            
=======
      /*
         //leer setpoint 
         set_adc_channel(PIN_SetPoint);//selecciona valore deseado setpoint  
         delay_us(100);       
         bits_SetPoint=read_adc();   
         //leer posicion real 
         set_adc_channel(PIN_PocitionReal);  //seleciona la posicion real 
         delay_us(100);       
         bits_PocitionReal=read_adc();       //leer
      */   
      read_SetPoint();
      read_PocitionReal();
      conver_bits_to_vol_SetPoint();
      conver_bits_to_vol_PocitionReal();
      calculos_PID();
      control_sentido_giro();
      conver_vol_to_bits_res_PID();
      salidas_PWM();
      //calculos 
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
      //convierte los bits en voltaje 
      /*
      Var_SetPoint      = (5.0*bits_SetPoint)/1024.0; 
      Var_PocitionReal  = (5.0*bits_PocitionReal)/1024.0;
      */
      ///  bits_difer=bits_PocitionReal-bits_SetPoint; //ningun uso 
      //diferencia de voltaje 
      //c=Var_PocitionReal-Var_SetPoint;
      //PID Calculos 
      /*
      Var_error_2=Var_error_1;
      Var_error_1=Var_error_0;  
      Var_error_0=Var_PocitionReal-Var_SetPoint;            
      //calculo               
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
=======
>>>>>>> d4c717e... conversion 90 %:PID_PWM2/PID_PWM2.c
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
            a=Var_error_0  *( kp + (ki*t) )+( kd/t );
            b=Var_error_1*( (-2*(kd/t) - kp) );
            c=Var_error_2*( (kd/t) +Var_res_1 );
            Var_res_1=Var_res_0;
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
            Var_res_0=a+b+c;               
      */
     /*
=======
<<<<<<< HEAD:PID + PWM2/PID + PWM2.c
            Var_res_0=a+b+c;
            
=======
            Var_res_0=a+b+c;               
      */
     /*
>>>>>>> d4c717e... conversion 90 %:PID_PWM2/PID_PWM2.c
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
         //conversion para PWM
         if(Var_res_0<0){//control de giro 
            Var_res_0=Var_res_0*-1;
            giro=2;
         }else{giro=1;}
         if(Var_res_0>=4.90){//control contra desbordamiento  
            Var_res_0=4.99;
         }
         bits_RES      = (1024*Var_res_0)/5;
         */
         //incremento en contrador 
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
            //k=k+1;                     
=======
<<<<<<< HEAD:PID + PWM2/PID + PWM2.c
            k=k+1;
                   
=======
            //k=k+1;                     
>>>>>>> d4c717e... conversion 90 %:PID_PWM2/PID_PWM2.c
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
      //interface
      LCD_GOTOXY(1,1);       
      printf(lcd_putc," %4Lu",bits_difer); lcd_putc("b");  
      printf(lcd_putc," %f",Var_error_0); lcd_putc("V");   
      LCD_GOTOXY(1,2);        
      printf(lcd_putc," %4Lu",bits_RES);  lcd_putc("b");      
      printf(lcd_putc," %f",Var_res_0);   lcd_putc("V");   
      delay_ms(100);
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
      LCD_PUTC("\f");   //Borrar el contenido del LCD           
      // EL SISGUIENTE CODIGO SE ENCARGA DE CONVERTIR
      // el valor de salida del pid en valores validos
      // para el puente h de dos hilos el sentido
      // de giro se definira por el signo ->0<+
      
      /*
      if(Var_PocitionReal<Var_SetPoint){//valores positivos 
         set_pwm1_duty(bits_RES);   //write salida de señal PWM 
         output_high(PIN_B1); //led indicador de giro 
      }else{
         output_low(PIN_B1); 
         set_pwm1_duty(0);
=======
      LCD_PUTC("\f");   //Borrar el contenido del LCD  
      
      //printf(lcd_putc," %i",k);            
      //printf(lcd_putc," %f",c);            
      // EL SISGUIENTE CODIGO SE ENCARGA DE CONVERTIR el valor de salida del pid en 
      //valores validos para el puente h de dos hilos 
      //el sentido de giro se definira por el signo ->0<+
      
      /*
      if(Var_PocitionReal<Var_SetPoint){//valores positivos 
<<<<<<< HEAD:PID + PWM2/PID + PWM2.c
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
=======
         set_pwm1_duty(bits_RES);   //write salida de señal PWM 
         output_high(PIN_B1); //led indicador de giro 
      }else{
         output_low(PIN_B1); 
         set_pwm1_duty(0);
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
      }
      if(Var_PocitionReal>Var_SetPoint){  //valores negativos          
         set_pwm2_duty(bits_RES);         //write salida de señal PWM          
         output_high(PIN_B2);             //led indicador de giro 
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
=======
>>>>>>> d4c717e... conversion 90 %:PID_PWM2/PID_PWM2.c
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
      }else{
         output_low(PIN_B2);
         set_pwm2_duty(0);
      } //si el sentido de giro no corresponde apaga el led y PWM
      if(Var_SetPoint==Var_PocitionReal){
         set_pwm2_duty(0);
         set_pwm1_duty(0);
<<<<<<< Updated upstream:PID_PWM2/PID_PWM2.c
      }       
      */
=======
<<<<<<< HEAD:PID + PWM2/PID + PWM2.c
      }
      
     
=======
      }       
      */
>>>>>>> d4c717e... conversion 90 %:PID_PWM2/PID_PWM2.c
>>>>>>> Stashed changes:PID + PWM2/PID + PWM2.c
   }
}

