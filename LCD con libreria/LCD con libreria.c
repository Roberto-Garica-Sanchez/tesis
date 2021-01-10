#INCLUDE <18f4550.H>
#device adc=10
#USE DELAY(CLOCK=4000000)
#INCLUDE <LCD.C>
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,PUT,NOLVP

//configuracion entradas/salidas
//entradas
   #define PIN_SetPoint  0    //[AN0]setpoint      set_adc_channel(0); set_adc_channel(PIN_SetPoint); 
   #define PIN_PocitionReal 1 //[AN1]posicion real set_adc_channel(1); set_adc_channel(PIN_PocitionReal); 
//salidas
    //control puenta H
        //Grupos de rotacion 
            //set_pwm1_duty() [RC2]
        //B
            //set_pwm1_duty() [RC3
//bits
unsigned int16 bits_SetPoint=0;
unsigned int16 bits_PocitionReal=0;

//var PID
float Var_SetPoint=0;
float Var_PocitionReal=0;
void MAIN(){
   
   setup_adc(ADC_CLOCK_INTERNAL);   //Selecciono reloj interno para conversion    
   setup_adc_ports(ALL_ANALOG);
   LCD_INIT();       //Inicializa el LCD
   LCD_PUTC("\f");   //Borrar el contenido del LCD
   WHILE(TRUE){
      set_adc_channel(PIN_SetPoint);          //Selecciono el canal 0 (RA0)
      bits_SetPoint=read_adc();             
      delay_us(100);
      set_adc_channel(PIN_PocitionReal);          //Selecciono el canal 0 (RA0)
      bits_PocitionReal=read_adc();             
      //(voltaje*valore_real*valro de conversion )/valor de muestreo  //valor de conversion menor de 100  
      //Var_SetPoint=bits_SetPoint*4.8; 
      Var_SetPoint = (5.0*bits_SetPoint)/1024.0;
    
      LCD_GOTOXY(1,1);        //Se ubica En la columna 5 fila 1
      printf(lcd_putc,"ADC: %4Lu",bits_SetPoint);  

      //printf(lcd_putc,"e= %u",bits_SetPoint);
      LCD_GOTOXY(3,2);        //Ubicarse en la columna 3 fila 2
      printf(lcd_putc,"e= %f",Var_SetPoint);

   } //Cierra while true
}
