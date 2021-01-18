
#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)
#USE STANDARD_IO(E)
//#######################################################################
//programa diseñado para controlar un motor mediante el uso de una puente H 
//Control de giro, velocidad 
//inplementando un PID para mejorar la precision

#define PIN_SetPoint  0    //[AN0]setpoint      set_adc_channel(0);
#define PIN_PocitionReal 1 //[AN1]posicion real set_adc_channel(1);
//variables tipo bits
unsigned int16 bits_SetPoint=0;
unsigned int16 bits_PocitionReal=0;
unsigned int16 bits_difer=0;
unsigned int16 bits_RES=0;
//variable control PWM
int16 duty=0;
int Timer2=249;         //Se carga timer 2 con 249
int Poscaler=1;         //Preescaler solo puede tomar valores de: 1
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
int   k=0;                 //contrador de muestras
float Var_res_0;           //Salidas
float Var_res_1;           //Salidas
//#########    ganancias
float kp=1;                //proporcional
float kd=0.2;              //Derivativa
float ki=0.2;              //integral
void star_PWM_2HILOS(void){    
   setup_timer_2(t2_div_by_4,Timer2,Poscaler);   
   setup_ccp1(ccp_pwm);      //Configurar modulo CCP1 en modo PWM
   setup_ccp2(ccp_pwm);      //Configurar modulo CCP2 en modo PWM
   //Configurar ADC configuracion 
   //de los puertos que funcionan en analogico 
   setup_adc_ports(all_analog);        
   setup_adc(adc_clock_internal);      
}
int16 read_SetPoint(){   
      //leer setpoint 
      set_adc_channel(PIN_SetPoint);//selecciona valore deseado setpoint  
      delay_us(100);       
      return bits_SetPoint=read_adc(); 
}
int16 read_PocitionReal(){     
   //leer posicion real 
   set_adc_channel(PIN_PocitionReal);  //seleciona la posicion real 
   delay_us(100);       
   return bits_PocitionReal=read_adc();       //leer         
}
float conver_bits_to_vol_SetPoint(){
   return Var_SetPoint      = (5.0*bits_SetPoint)/1024.0; 
}
float conver_bits_to_vol_PocitionReal(){
   return Var_PocitionReal  = (5.0*bits_PocitionReal)/1024.0;
}
void calculos_PID(){   
   Var_error_2=Var_error_1;
   Var_error_1=Var_error_0;  
   Var_error_0=Var_PocitionReal-Var_SetPoint;            
   //calculo               
      a=Var_error_0  *( kp + (ki*t) )+( kd/t );
      b=Var_error_1*( (-2*(kd/t) - kp) );
      c=Var_error_2*( (kd/t) +Var_res_1 );
      Var_res_1=Var_res_0;
      Var_res_0=a+b+c;     
}
void control_sentido_giro(){//incluse un proceso para evitar un desvordamiento de valor por el PWM
   //conversion para PWM
   if(Var_res_0<0){//control de giro 
      Var_res_0=Var_res_0*-1;
      giro=2;
   }else{giro=1;}
   if(Var_res_0>=4.95){//control contra desbordamiento  
      Var_res_0=4.99;
   }
}
void conver_vol_to_bits_res_PID(){        
   bits_RES      = (1024*Var_res_0)/5;
}
void salidas_PWM(){       
   if(Var_PocitionReal<Var_SetPoint){//valores positivos 
      set_pwm1_duty(bits_RES);   //write salida de señal PWM 
      output_high(PIN_B1); //led indicador de giro 
   }else{
      output_low(PIN_B1); 
      set_pwm1_duty(0);
   }
   if(Var_PocitionReal>Var_SetPoint){  //valores negativos          
      set_pwm2_duty(bits_RES);         //write salida de señal PWM          
      output_high(PIN_B2);             //led indicador de giro 
   }else{
      output_low(PIN_B2);
      set_pwm2_duty(0);
   } //si el sentido de giro no corresponde apaga el led y PWM
   if(Var_SetPoint==Var_PocitionReal){
      set_pwm2_duty(0);
      set_pwm1_duty(0);
   }       
}