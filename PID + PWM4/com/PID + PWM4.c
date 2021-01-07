
#include <18F4520.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=4000000)  

#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)
#USE STANDARD_IO(E)
//LCD
int menu_move;
int pocision_menu=1;
int menu_select;
int menu_back;
//configuracion entradas/salidas
//entradas
    //[AN0]setpoint
    //[AN1]posicion real 
    //[]servo motor 
//salidas
    //control puenta H
        //Grupos de rotacion 
        //A
            //[P1A][RC2]
            //[P1D][RD7]
        //B
            //[P1C][RD6]
            //[P1B][RD5]


//#########     lecturas
int16 setpoint;
int16 posicion_real;    
//#########     PID
int16 duty=0;
int Timer2,Poscaler;
int16 a,b,c;            //variables temporales
int16 t=1;              //periodo de muestreo 
int16 e[100];           //error
int16 k=0;              //contrador de muestras
int16 u[100];            //Salidas
//#########    ganancias
int16 kd=1;               //Derivativa
int16 ki=0.5;               //integral
int16 kp=0.5;               //proporcional
int16 res,conversion;
//conexiones de LCD
    #define LCD_RS PIN_C4
    #define LCD_RW PIN_C5
    #define LCD_EN PIN_C6

    #define LCD_D0 PIN_B0
    #define LCD_D1 PIN_B1
    #define LCD_D2 PIN_B2
    #define LCD_D3 PIN_B3
    #define LCD_D4 PIN_B4
    #define LCD_D5 PIN_B5
    #define LCD_D6 PIN_B6
    #define LCD_D7 PIN_B7

void Active_LCD(void){
   output_high(LCD_EN);
   output_low(LCD_RS);
   output_low(LCD_RW);

   output_low(LCD_D0);
   output_low(LCD_D1);
   output_high(LCD_D2);
   output_high(LCD_D3);
   output_high(LCD_D4);
   output_high(LCD_D5);
   output_low(LCD_D6);
   output_low(LCD_D7);

   //ejecuta instrucion 
   delay_ms(5);
   output_low(LCD_EN);
   delay_ms(5);
   output_high(LCD_EN);
}
void Enciende_LCD(void){  
   output_high(LCD_EN);
   output_low(LCD_RS);
   output_low(LCD_RW);

   output_low(LCD_D0);
   output_low(LCD_D1);
   output_high(LCD_D2);
   output_high(LCD_D3);
   output_low(LCD_D4);
   output_low(LCD_D5);
   output_low(LCD_D6);
   output_low(LCD_D7);

   //ejecuta instrucion 
   delay_ms(5);
   output_low(LCD_EN);
   delay_ms(5);
   output_high(LCD_EN);

}
void Clear_LCD(){    
   output_high(LCD_EN);
   output_low(LCD_RS);
   output_low(LCD_RW);

   output_high(LCD_D0);
   output_low(LCD_D1);
   output_low(LCD_D2);
   output_low(LCD_D3);
   output_low(LCD_D4);
   output_low(LCD_D5);
   output_low(LCD_D6);
   output_low(LCD_D7);

   //ejecuta instrucion 
   delay_ms(5);
   output_low(LCD_EN);
   delay_ms(5);
   output_high(LCD_EN);
}
void write_LCD(){
   output_high(LCD_EN);
   output_high(LCD_RS);
   output_low(LCD_RW);

   output_low(LCD_D0);
   output_low(LCD_D1);
   output_high(LCD_D2);
   output_low(LCD_D3);
   output_high(LCD_D4);
   output_low(LCD_D5);
   output_high(LCD_D6);
   output_low(LCD_D7);
   
   //ejecuta instrucion 
   delay_ms(5);
   output_low(LCD_EN);
   delay_ms(5);
   output_high(LCD_EN);
}
void write_LCD3(int *Codigo){
   output_high(LCD_EN);
   output_high(LCD_RS);
   output_low(LCD_RW);

   if(Codigo[0]==1)output_high(LCD_D0); else output_low(LCD_D0);
   if(Codigo[1]==1)output_high(LCD_D1); else output_low(LCD_D1);
   if(Codigo[2]==1)output_high(LCD_D2); else output_low(LCD_D2);
   if(Codigo[3]==1)output_high(LCD_D3); else output_low(LCD_D3);
   if(Codigo[4]==1)output_high(LCD_D4); else output_low(LCD_D4);
   if(Codigo[5]==1)output_high(LCD_D5); else output_low(LCD_D5);
   if(Codigo[6]==1)output_high(LCD_D6); else output_low(LCD_D6);
   if(Codigo[7]==1)output_high(LCD_D7); else output_low(LCD_D7);
   
   //ejecuta instrucion 
   //delay_ms(2);
   output_low(LCD_EN);
   
   output_high(LCD_EN);
}
void Star_LCD(){
    Clear_LCD();
    Enciende_LCD();
    Active_LCD();
}
int  Codigo_Letras(char letra){   
    int Codigo[7];
    switch(letra){
        case 'A':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=0;Codigo[1]=0;Codigo[0]=1;  break;
        case 'B':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=0;Codigo[1]=1;Codigo[0]=0;  break; 
        case 'C':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=0;Codigo[1]=1;Codigo[0]=1;  break;

        case 'D':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=0;  break;
        case 'E':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=1;  break;
        case 'F':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=1;Codigo[0]=0;  break;        
        case 'G':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=1;Codigo[0]=1;  break;
        
        case 'H':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=0;Codigo[0]=0;  break;
        case 'I':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=0;Codigo[0]=1;  break;       
        case 'J':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=1;Codigo[0]=0;  break;
        case 'K':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=1;Codigo[0]=1;  break;

        case 'L':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=1;Codigo[1]=0;Codigo[0]=0;  break;
        case 'M':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=1;Codigo[1]=0;Codigo[0]=1;  break;
        case 'N':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=1;Codigo[1]=1;Codigo[0]=0;  break;
        case 'O':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=0;     Codigo[3]=1;Codigo[2]=1;Codigo[1]=1;Codigo[0]=1;  break;        
        
        case 'P':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=0;Codigo[1]=0;Codigo[0]=1;  break;
        case 'Q':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=0;Codigo[1]=1;Codigo[0]=0;  break; 
        case 'R':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=0;Codigo[1]=1;Codigo[0]=0;  break;
        case 'S':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=0;  break;
        case 'T':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=1;  break;
        case 'U':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=1;Codigo[0]=0;  break;
        case 'V':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=0;Codigo[2]=1;Codigo[1]=1;Codigo[0]=1;  break;
        case 'W':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=0;Codigo[0]=0;  break;
        case 'X':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=0;Codigo[0]=1;  break; 
        case 'Y':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=1;Codigo[0]=0;  break;
        case 'Z':  Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;     Codigo[3]=1;Codigo[2]=0;Codigo[1]=1;Codigo[0]=1;  break;
        

        case '/':     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=0;  Codigo[3]=1;Codigo[2]=1;Codigo[1]=1;Codigo[0]=1; break;
        case ' ':     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=0;  Codigo[3]=0;Codigo[2]=0;Codigo[1]=0;Codigo[0]=0; break;
        case '[':     Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=0; break;
        case ']':     Codigo[7]=0;Codigo[6]=1;Codigo[5]=0;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=0; break;
    }
    write_LCD3(Codigo); 
    return  Codigo;
}       
int  Codigo_numero(int numero){   
    int Codigo[7];
    switch(numero){
        case 0:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=0;Codigo[1]=0;Codigo[0]=0; break;
        case 1:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=0;Codigo[1]=0;Codigo[0]=1; break;
        case 2:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=0;Codigo[1]=1;Codigo[0]=0; break;
        case 3:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=0;Codigo[1]=1;Codigo[0]=1; break;
        case 4:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=0; break;
        case 5:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=1;Codigo[1]=0;Codigo[0]=1; break;
        case 6:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=1;Codigo[1]=1;Codigo[0]=0; break;
        case 7:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=0;Codigo[2]=1;Codigo[1]=1;Codigo[0]=1; break;
        case 8:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=1;Codigo[2]=0;Codigo[1]=0;Codigo[0]=0; break;
        case 9:     Codigo[7]=0;Codigo[6]=0;Codigo[5]=1;Codigo[4]=1;  Codigo[3]=1;Codigo[2]=0;Codigo[1]=0;Codigo[0]=1; break;
    }
    write_LCD3(Codigo); 
    return  Codigo;
}

long map(long x, long in_min, long in_max, long out_min, long out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
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
    Star_LCD();
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
                
            res=posicion_real-setpoint;
         
            //set_pwm1_duty(res);           //write salida
            if(posicion_real>setpoint){                
                Clear_LCD();
                Codigo_Letras('p');
                Codigo_Letras('m');
                Codigo_Letras('s');
                delay_ms(200);
            }
            if(setpoint>posicion_real){
                Clear_LCD();
                Codigo_Letras('s');
                Codigo_Letras('m');
                Codigo_Letras('p');
                delay_ms(200);
            }

            
        //protecion contra desvordamiento de variables 
        if(k>=20){
            k=0; 
            for (int i = 0; i <100; i++){
                e[i]=0;
            }
            
        }
        
       
   }
}
