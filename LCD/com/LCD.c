#include <18f4550.h>
#use delay(clock=4000000)
#fuses XT, NOWDT
//#include <math.h>

#USE STANDARD_IO(A)
#USE STANDARD_IO(B)
#USE STANDARD_IO(C)
#USE STANDARD_IO(D)
#USE STANDARD_IO(E)
int menu_move;
int pocision_menu=1;
int menu_select;
int menu_back;
//conexiones de LCD
    #define LCD_RS PIN_C4
    #define LCD_RW PIN_C5
    #define LCD_EN PIN_C6

    #define LCD_D0 PIN_D0
    #define LCD_D1 PIN_D1
    #define LCD_D2 PIN_D2
    #define LCD_D3 PIN_D3
    #define LCD_D4 PIN_D4
    #define LCD_D5 PIN_D5
    #define LCD_D6 PIN_D6
    #define LCD_D7 PIN_D7

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
void main(){   
    Star_LCD();

    while (1){
        menu_move=INPUT(PIN_B0); //cambia entre las diferentes obciones del menu 
        menu_select=INPUT(PIN_B1);   //seleciona actual del menu 
        menu_back=INPUT(PIN_B2);   //regresar en el menu 
        if (menu_move==1)   {
            output_high(PIN_B7);
            pocision_menu++;
            while (INPUT(PIN_B0)){
            }
            delay_ms(100);
            
            
        }else{
            output_low(PIN_B7);
        }
        if (menu_select==1) {output_high(PIN_B6);}else{output_low(PIN_B6);}
        if (menu_back==1)   {output_high(PIN_B5);}else{output_low(PIN_B5);}
                Clear_LCD();
                Codigo_numero(pocision_menu);
                Codigo_Letras('/');
                Codigo_numero(2);
   
    }
    
}
