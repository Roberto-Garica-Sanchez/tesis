//entradas
const int pin_SETPoint = A0;    // seleccionar la entrada para el sensor
const int pin_sensor = A1;    // seleccionar la entrada para el sensor
//salidas
const int pin_rele1 = 2;      //salidas control rele (NC) normal mente cerrado en OFF(salidad apagada o a GND)
const int pin_rele2 = 3;      //salidas control rele(NC) normal mente cerrado en OFF(salidad apagada o a GND)
int value_SETPoint;           // variable que almacena el valor raw (0 a 1023)
int value_sensor;             // variable que almacena el valor raw (0 a 1023)
float Control;
//tiempo
int tiempo=0;
//proporcional
float Kp=.75;
float error;
float Kperror;
//integral
float Ki=0.36;
float Ierror=1;
float Aerror;
//derivada
float Kd=1;
float Derror;
 
void setup(){
  pinMode(pin_SETPoint,INPUT);
  pinMode(pin_sensor,INPUT);
  
  pinMode(pin_rele1,OUTPUT);
  pinMode(pin_rele2,OUTPUT);
   Serial.begin(9600);
}
 
void loop(){
   //lecturad de sensores
   value_SETPoint = analogRead(pin_SETPoint);   // realizar la lectura
   value_sensor = analogRead(pin_sensor);   // realizar la lectura
   //calculculos del pid
   if(tiempo<=0){//inicializando el pid
      error=value_SETPoint - value_sensor;
      Aerror=error; //almacena el error actual para usarlo en el siguente calculo. Error anterior 
      tiempo++;
   }
   if(tiempo>0){
         tiempo++;
      //proporcional
         error=value_SETPoint - value_sensor;
         Kperror=Kp*error;
      //intergral(pasado)
         //Ierror=Aerror*Ki;
         if(Ierror<error){
            Ierror=Ierror*error*Ki;//Aerror*Ki;
         }else{
            Ierror=1;
         }
      //derivado(presente)
         Derror = (error - Aerror) * Kd ;
      //PID
         Control = Kperror + Ierror + Derror;
      //prepara siguiente calculo      
       Aerror=error; //almacena el error actual para usarlo en el siguente calculo. Error anterior 
   }
   //actuador
      if(Control<-50){//+          
         Serial.print(" Dere");
         digitalWrite(2,HIGH);
         digitalWrite(3,LOW);

      }
      if(Control>50 ){//-
         Serial.print(" Isqu");
         digitalWrite(2,LOW);
         digitalWrite(3,HIGH);
      }
    //presentacion de datos 
    Serial.print(" SET POINT: ");
    Serial.print(value_SETPoint);
    Serial.print(" REAL: ");
    Serial.print(value_sensor);
    Serial.print(" Error: ");
    Serial.print(error);
    Serial.print(" TIEMPO: ");
    Serial.print(tiempo);
    Serial.print(" Kperror: ");
    Serial.print(Kperror);
    Serial.print(" Ierror: ");
    Serial.print(Ierror);
    Serial.print(" Derror: ");
    Serial.print(Derror);
    
    Serial.print(" Control: ");
    Serial.println(Control);
    
   delay(500);
}