
//Programa padrão - Chave liga LED
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//Definição de I/O
#include "dht.h" //INCLUSÃO DE BIBLIOTECA
 
const int DHT11_1 = A2; //PINO ANALÓGICO UTILIZADO PELO DHT11
 
dht DHT; //VARIÁVEL DO TIPO DHT
 
//Entradas (nome e número do pino)
#define Key_01 12
#define Key_02 13
#define Key_03 14

//Saídas (nome e número do pino)
#define LED_01 2
#define LED_02 3
#define LED_03 4

//-------------------------------------------------------------------------
void setup()
{
  pinMode(LED_01, OUTPUT); // Define o LED_01 como saída
  pinMode(LED_02, OUTPUT); // Define o LED_02 como saída
  pinMode(LED_03, OUTPUT); // Define o LED_03 como saída
  
  pinMode(Chave_01, INPUT);// Define a Chave_01 como entrada
  pinMode(Chave_02, INPUT);// Define a Chave_02 como entrada
  pinMode(Chave_03, INPUT);// Define a Chave_03 como entrada
}

//-------------------------------------------------------------------------
void liga()
{
  digitalWrite(LED_01, HIGH); //Escreve 1 (HIGH) no LED_01
  delay(1000);  //Espera 1s
  digitalWrite(LED_02, HIGH); //Escreve 1 (HIGH) no LED_02
  delay(1000);  //Espera 1s
  digitalWrite(LED_03, HIGH); //Escreve 1 (HIGH) no LED_03        
}
void pisca()
{
  digitalWrite(LED_01, HIGH); //Escreve 1 (HIGH) no LED_01
  digitalWrite(LED_02, HIGH); //Escreve 1 (HIGH) no LED_02
  digitalWrite(LED_03, HIGH); //Escreve 1 (HIGH) no LED_03
  delay(500);  //Espera 500ms
  digitalWrite(LED_01, LOW); //Escreve 0 (LOW) no LED_01
  digitalWrite(LED_02, LOW); //Escreve 0 (LOW) no LED_02
  digitalWrite(LED_03, LOW); //Escreve 0 (LOW) no LED_03
  delay(500);  //Espera 500ms
}
void conta_de_0_ate_7(){


}
void loop(){

}


 
void temperatura_umidade(){
#Fonte: https://blogmasterwalkershop.com.br/arduino/
#como-usar-com-arduino-sensor-de-umidade-e-temperatura-dht11

  DHT.read11(DHT11_1); //LÊ AS INFORMAÇÕES DO SENSOR
  Serial.print("Umidade: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.humidity); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO
  Serial.print("%"); //ESCREVE O TEXTO EM SEGUIDA
  Serial.print(" / Temperatura: "); //IMPRIME O TEXTO NA SERIAL
  Serial.print(DHT.temperature, 0); //IMPRIME NA SERIAL O VALOR DE UMIDADE MEDIDO E REMOVE A PARTE DECIMAL
  Serial.println("*C"); //IMPRIME O TEXTO NA SERIAL
  delay(2000); //INTERVALO DE 2 SEGUNDOS * NÃO DIMINUIR ESSE VALOR
}
void screen(){


}