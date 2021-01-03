//entradas
const int pin_SETPoint = A0;    // seleccionar la entrada para el sensor
//salidas
const int left_A = 5;      //salidas control rele (NC) normal mente cerrado en OFF(salidad apagada o a GND)
const int left_B = 4;      //salidas control rele(NC) normal mente cerrado en OFF(salidad apagada o a GND)
const int left_PWM = 3;      //salidas control rele(NC) normal mente cerrado en OFF(salidad apagada o a GND)

 int value_SETPoint;           // variable que almacena el valor raw (0 a 1023)
int val;
void setup(){
  
  pinMode(pin_SETPoint,INPUT);
  pinMode(left_PWM,OUTPUT);
  pinMode(left_B,OUTPUT);
  pinMode(left_B,OUTPUT);
   Serial.begin(9600);
}
 
void loop(){
   value_SETPoint = analogRead(pin_SETPoint);   // realizar la lectura
    //Serial.print(" TIEMPO: ");
    //Serial.print(value_SETPoint);
    val = map (value_SETPoint, 0, 1023, -255, 255);
    Serial.print(val);
         //digitalWrite(left_A,HIGH);
         //digitalWrite(left_B,LOW);  
         //analogWrite(left_PWM,val);
   
   //actuador
      if(val<-50){//+          
         val=val*-1;
         Serial.print(" isqu: ");
         Serial.print(val);
         digitalWrite(left_A,LOW);
         digitalWrite(left_B,HIGH);  
         analogWrite(left_PWM,val);

      }else      
      if(val>50 ){//-
         Serial.print(" Dere: ");
         Serial.print(val);
         digitalWrite(left_A,HIGH);
         digitalWrite(left_B,LOW);  
         analogWrite(left_PWM,val);
      }else{
         
         analogWrite(left_PWM,0);
      }
      
    Serial.println("");
      
}