
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