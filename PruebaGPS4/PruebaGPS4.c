#define time_offset   -18000   // define a clock offset of 3600 seconds (1 hour) ==> UTC + 1

//LCD module connections PUERTO D 
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_ENABLE_PIN PIN_D2
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7
#include <18F4550.h>
//#include <stdlib.h>
//#include <stdio.h>
#device PASS_STRINGS = IN_RAM
#fuses NOMCLR, INTRC_IO, NOWDT, NOPROTECT, NOLVP
#use delay(clock = 8MHz)
#use fast_io(D)
#use RS232(UART1, BAUD = 9600, ERRORS)   //puerto UART configuracion y iniciow
#include <lcd.c>      //incluye libreria LCD 
#include <GPS_Lib.c>  //incluye libreria LCD
//incluye librerias de tiempo 
#include <time.h>
#include <time.c> 
#include <math.h>
float lat,lon,eti,dec1,to,ws,tc1,orto,horapuesta,horaorto;
float horaocaso,horareal,ocaso,horasalida,tst,azimut,ha;
float zenit,haa, da1, N1, N2, N3, adia1;
float hor, min, sec, horare;
float hora,minutos,segundos,x,dia,mes,year;
//variable para la libreria de fechas 
time_t unix_time;
struct_tm utc_time, *my_time;
// other variables
char time_c[] = "HORA:   :  :  ";
char date_c[] = "FECHA:    -  -20  ";

char datee_c[] = "  ";  //MES
char dia_c[] = "  ";    //DIA
char ano_c[] ="  ";     //AÑO
char hora_c[]="  ";     //HORA
char min_c[]="  ";      //MINUTOS
char seg_c[]="  ";      //SEGUNDOS
void print_wday(int8 wday){
  lcd_gotoxy(6, 1);
  switch(wday){
    case 0:  lcd_putc(" DOMINGO ");     break;
    case 1:  lcd_putc(" LUNES ");       break;
    case 2:  lcd_putc(" MARTES ");      break;
    case 3:  lcd_putc(" MIERCOLES ");   break;
    case 4:  lcd_putc(" JUEVES ");      break;
    case 5:  lcd_putc(" VIERNES ");     break;
    default: lcd_putc(" SABADO ");
  }
 
}
void main(void) { //PROGRAMA PRINCIPAL
  setup_oscillator(OSC_8MHZ);                // Set internal oscillator to 8MHz
  lcd_init();
  delay_ms(50);
  printf(lcd_putc,"INICIANDO SISTEMA \n  ESPERE....");
  delay_ms(2000);
  lcd_putc("\f");
  while(TRUE){
    if(kbhit()){
      if(GPSRead()){
        //configura la posicion gps 
        lat = 19.0506 ;
        lon = -104.316;
        //lee y guarda las hora y fecha en formato UTC
        utc_time.tm_hour = GPSHour();
        utc_time.tm_min  = GPSMinute();
        utc_time.tm_sec  = GPSSecond();
        //ajusta las valores a un formato compatible 
        utc_time.tm_mday = GPSDay();          //numero de dia del mes en formato (1 - 31)
        utc_time.tm_mon  = GPSMonth() - 1;    //numero del mes en formato (0 - 11)
        utc_time.tm_year = GPSYear() + 100;   //Año iniciando desde 1900
        //obtiene las fechas de unix 
        unix_time = mktime(&utc_time); 
        //añade los segundos al formato unix 
        unix_time += time_offset; 
        //obtiene la hora local segun la posicion GPS 
        my_time = localtime(&unix_time); 
        time_c[6]   = my_time->tm_hour / 10 + '0';
        time_c[7]   = my_time->tm_hour % 10 + '0';
        time_c[9]   = my_time->tm_min  / 10 + '0';
        time_c[10]  = my_time->tm_min  % 10 + '0';
        time_c[12]  = my_time->tm_sec  / 10 + '0';
        time_c[13]  = my_time->tm_sec  % 10 + '0';        
        hora_c[1]   = my_time->tm_hour / 10 + '0';
        hora_c[2]   = my_time->tm_hour % 10 + '0';        
        min_c[1]    = my_time->tm_min  / 10 + '0';
        min_c[2]    = my_time->tm_min  % 10 + '0';
        seg_c[1]    = my_time->tm_sec  / 10 + '0';
        seg_c[2]    = my_time->tm_sec  % 10 + '0';        
        date_c[6]   = my_time->tm_mday / 10 + '0';
        date_c[7]   = my_time->tm_mday % 10 + '0';
        date_c[9]   = (my_time->tm_mon + 1)  / 10 + '0';
        date_c[10]  = (my_time->tm_mon + 1)  % 10 + '0';
        date_c[14]  = (my_time->tm_year / 10) % 10 + '0';
        date_c[15]  = my_time->tm_year  % 10 + '0';        
        datee_c[1]  = (my_time->tm_mon + 1)  / 10 + '0';
        datee_c[2]  = (my_time->tm_mon + 1)  % 10 + '0';
        ano_c[1]    = (my_time->tm_year / 10) % 10 + '0';
        ano_c[1]    = my_time->tm_year  % 10 + '0';        
        //presenta los datos de la fecha 
        print_wday(my_time->tm_wday);          //presenta la semana 
        lcd_gotoxy(23, 1);                     //cambio de posicion en la pantalla lcd 
        printf(lcd_putc, time_c);              //presenta la fecha en formato (HH:MM:SS)
        lcd_gotoxy(23, 2);                     //cambio de posicion en la pantalla lcd 
        printf(lcd_putc, date_c);              //presenta la fecha en formato(DD-MM-YYYY)
        mes = atof(datee_c);                    
        year = 2021;
        //Ecuacion para obtener el numero del dia en el año (0 a 356)
        if (mes==1) {da1 = dia;}  
        if (mes==2) {da1 = 31 + dia;}
        if (mes>=3) {
          N1 = (275*mes/9); 
          N2 = (mes+9)/12; 
          N3 = (1 + floor((year - 4 * floor(year / 4) + 2) / 3)); 
          da1 = N1 -(N2*N3) + dia - 30;
        } 
        //Ecuacion para obtener el numero del dia
        adia1 = ((2*pi)/365)*(da1-1); //Ecuacion de dia
        eti =(
          ((0.000073) + (0.001868*(cos(adia1)))   
          - (0.0320777*(sin(adia1))) - (0.014615 * (cos(2*adia1))) 
          - (0.04089*(sin(2*adia1)))) * (229.18)
        ); 
        //Correcion del tiempo, resultado en minutos
        to = eti + (4*lon) - (60*-5);
        //Declinacion solar
        dec1 =(
          (0.006918-(0.39912*cos(adia1)) + (0.070257*sin(adia1)) 
          - (0.006758*cos(2*adia1)) + (0.0009907*sin(2*adia1)) 
          - (0.002697*cos(3*adia1))+(0.00148*sin(3*adia1)))
        );
        //Angulo horario a la salida del sol
        ws = (acos(-tan(lat)*tan(dec1)));
        tc1 = 4*(lon+(15*5))+eti;
        orto = 12 - ((2*ws)/15) + (tc1/60) - 2; //Hora de salida del sol
        ocaso = 24 + ((2*ws)/15) + (tc1/60) - 2; //Hora de puesta del sol

        //Calculos variables, cada hora  
        //Tiempo estandar, tiempo solar verdadero 
        hor=atof(hora_c);
        minutos=atof(min_c);
        sec=atof(seg_c);
        horare = hor + (minutos/60) + (sec/3600);
        if (horare<orto){//alba (salida del sol)
          lcd_gotoxy(1,2); 
          printf(lcd_putc, "Alba: %f", orto);
        }
        if (horare>orto){
          lcd_gotoxy(1,2); 
          printf(lcd_putc, "Ocaso: %f", ocaso);
        }
        if (horare>ocaso){//(ocultamiento del sol)
          adia1 = (((2*pi)/365)*(da1-1))+1; //Ecuacion de dia
          eti =( //Resultado en minutos
            ((0.000073) + (0.001868*(cos(adia1))) 
            - (0.0320777*(sin(adia1))) - (0.014615*(cos(2*adia1))) 
            - (0.04089*(sin(2*adia1))))*(229.18)
          );
          //Correcion del tiempo, resultado en minutos
          to = eti + (4*lon) - (60*-5);
          //Declinacion solar
          dec1 =(
            (0.006918-(0.39912*cos(adia1)) + (0.070257*sin(adia1)) 
            - (0.006758*cos(2*adia1)) + (0.0009907*sin(2*adia1)) 
            - (0.002697*cos(3*adia1))+(0.00148*sin(3*adia1)))
          );
          //Angulo horario a la salida del sol
          ws = (acos(-tan(lat)*tan(dec1)));
          tc1 = 4*(lon+(15*5))+eti;
          orto = 12 - ((2*ws)/15) + (tc1/60) - 2; //Hora de salida del sol
          lcd_gotoxy(1,2); printf(lcd_putc, "Alba: %f", orto);
        }
         
        
        tst = (hor*60) + minutos + (sec/60) + to;
        //Angulo solar 
        ha = (tst/4) - (180);
        haa = ha*0.01745333;
        //Angulo Zenith
        zenit =   acos(((sin(lat))*(sin(dec1))) + ((cos(lat))*(cos(dec1))*(cos(haa))));
        //Angulo Azimutal
        if (ha<0) {azimut = (pi +  ((-acos(((sin(lat)*cos(zenit)) - sin(dec1))/(cos(lat)*sin(zenit))))))*57.2958; }
        if (ha>0) {azimut = (6.28319 - (((-acos(((sin(lat)*cos(zenit)) - sin(dec1))/(cos(lat)*sin(zenit)))))))*57.2958;}
        lcd_gotoxy(1,2); printf(lcd_putc, "Azimut Sol: %f", azimut);
        
      }
 
    }
 
  }
 
}
// End of code. Code



