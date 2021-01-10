
#include <18F4520.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000)  

//configuracion entradas/salidas
//entradas
    //[AN0]setpoint
    //[AN1]posicion real 
    //[]servo motor 
//salidas
    //control puenta H
        //Grupos de rotacion 
        //A
            //[RC2]
        //B
            //[RD6]


int Timer2,Poscaler;
int16 duty=0;
//#########     lecturas
int16 setpoint;
int16 posicion_real;
//#########     PID
float a,b,c;            //variables temporales
float t=1;              //periodo de muestreo 
float e[100];           //error
float k=0;              //contrador de muestras
float u[100];            //Salidas
//#########    ganancias
float kd=1;               //Derivativa
float ki=0.5;               //integral
float kp=0.5;               //proporcional


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
   while(1){
       
        //muestreo
            //lectura del set point
                set_adc_channel(0);            //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
                delay_us(100);       
                setpoint=read_adc();
            //lectura del set point
                set_adc_channel(1);            //selecciona el puesto en el que se ejecutarn las sigientes instruciones 
                delay_us(100);       
                posicion_real=read_adc();
        //duty=read_adc();               //leer
        //muestreo
            e[k]=posicion_real-setpoint;
            
        //calculo
            a=e[k]  *( kp + (ki*t) )+( kd/t );
            b=e[k-1]*( (-2*(kd/t) - kp) );
            c=e[k-2]*( (kd/t) +u[k-1] );
            u[k]=a+b+c;
        //incremento en contrador 
            k=k+1;
                    
        //salidas 
            set_pwm1_duty( u[k]);           //write salida
        //protecion contra desvordamiento de variables 
        if(k>=20){
            k=0; 
            for (int i = 0; i <100; i++){
                e[i]=0;
            }
            
        }
        
       
   }
}