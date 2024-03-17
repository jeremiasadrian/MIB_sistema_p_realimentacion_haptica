/*
  Puente_H_control_v2

  Programa para generar las señales de control para el puente H
  de una fuente conmutada FULL-BRIDGE elevadora para un electroestimulador
  por corriente. 
  En esta versión se le incorpora la variación de frecuencua de ambas señales
  a fin de poder relevar el comportamiento para determinar la condición óptima
  que permita mejorar el rendimiento de la fuente. 
  El programa solo stablece variación de frecuencia a "duty" constante
  del 10%.

  Creado en julio del 2023
  por Jeremías García.
*/

//Defino las salidad digitales para los pares opuestos del puente H.
const int D2=2, D3=3;
//Defino variable entera para almacenar la conversión de A0.
int dutyVAL = 0;
/*Defino variable entera para mapear el estado del Pot a los valores
extremos de tiempo de 1ms (1kHz) y 10ms (100Hz).*/
int Base_T = 0;
//Configura las salidas digitales y las inicializa en un estado bajo.
//COnfigura la entrada analógica para el control del ciclo de trabajo.
void setup() 
{
  Serial.begin(9600);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(D2, LOW); 
  digitalWrite(D3, LOW); 
}

void loop() 
{
  dutyVAL = analogRead(A0);
  Base_T = map(dutyVAL,0,1023,1000,10000);
  digitalWrite(D2, HIGH);     
  delayMicroseconds(Base_T*0.45);                        
  digitalWrite(D2, LOW);
  delayMicroseconds(Base_T*0.05); 
  digitalWrite(D3, HIGH);    
  delayMicroseconds(Base_T*0.45);         
  digitalWrite(D3, LOW);     
  delayMicroseconds(Base_T*0.05);         
}
