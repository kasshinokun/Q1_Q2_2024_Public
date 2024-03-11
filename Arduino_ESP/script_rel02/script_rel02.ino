//-------------------------------------------------------------------------
//Relatório 02 - IoT - Gabriel da Silva Cassino 
//INCLUSÃO DE BIBLIOTECA
#include "DHT.h" //DHT11

//Para o Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



//################################################################
//Variaveis para o projeto

const int DHT11_1 = 0; //PINO ANALÓGICO UTILIZADO PELO DHT11

#define DHTTYPE DHT11  //VARIAVEL TIPO A SER UTILIZADA PELO DHT11(PRECISO ADAPTAR)

DHT dht(DHT11_1, DHTTYPE);

const int PINO_BUZZER_0 = 23; // Pino D23 conectado ao buzzer passivo
const int PINO_BUZZER_1 = 25;// Pino D24 conectado ao buzzer passivo(VALOR GENERICO PRECISO DEFINIR CORRETAMENTE)

const int CANAL_PWM = 0;   // Canal PWM utilizado para o buzzer

//Pinos dos LEDs
int LED_01 = 8;
int LED_02 = 12;
int LED_03 = 13;

// Pino do botão
int KEY_01 = 7;
int KEY_02 = 4;
int KEY_03 = 2;

// contador
int count = 0;

//variavel para tempo(generica)
int initial_time=0;
int final_time=5000;


//Definições para o display
#define LARGURA_OLED 128
#define ALTURA_OLED 64
 
#define RESET_OLED -1
 
Adafruit_SSD1306 display(LARGURA_OLED, ALTURA_OLED, &Wire, RESET_OLED);


//Procedimentos
//##########Referentes a tela##############################################################
//From:https://www.makerhero.com/blog/controlando-um-display-oled-com-a-biblioteca-ssd1306/
void tela_print_1(String texto){
  display.setTextSize(1);//tamanho da fonte
  display.setTextColor(WHITE);//cor da fonte
  display.setCursor(0,10);//posição do texto na tela
  display.print(texto);//texto-alvo
  display.display();//habilita a tela para exibir

}
//From:https://www.makerhero.com/blog/controlando-um-display-oled-com-a-biblioteca-ssd1306/
void tela_print_2(String texto){
  display.drawRoundRect(10, 10, 108, 44, 3, WHITE);//Configurações para Primeira exibição
  display.setTextSize(1);//tamanho da fonte
  display.setTextColor(WHITE);//cor da fonte
  display.setCursor(32, 30);//posição do texto na tela
  display.print(texto);//texto-alvo
  display.display();//habilita a tela para exibir
  display.invertDisplay(true);//Primeira exibição
  delay(2000);//aguarda 2s
  display.invertDisplay(false);//Inverte as cores da Primeira exibição
  delay(2000);//aguarda 2s
}
//Demais procedimentos
void on_off(){//Apaga os Led's
  if(digitalRead (LED_01) == HIGH||
     digitalRead (LED_02) == HIGH||
     digitalRead (LED_03) == HIGH){
    digitalWrite(LED_01, LOW); //Escreve 0 (LOW) no LED_01
    digitalWrite(LED_02, LOW); //Escreve 0 (LOW) no LED_02
    digitalWrite(LED_03, LOW); //Escreve 0 (LOW) no LED_03

  }
  else{//Acende os Led's
  	digitalWrite(LED_01, HIGH); //Escreve 1 (HIGH) no LED_01
    digitalWrite(LED_02, HIGH); //Escreve 1 (HIGH) no LED_02
    digitalWrite(LED_03, HIGH); //Escreve 1 (HIGH) no LED_03
  }
}
void counter(){//contador de 0 a 7
    // Incrementa o contador
    count = (count == 7) ? 0 : count+1;

    Serial.print("Contador em:");
    Serial.println(count);
	  digitalWrite(LED_01, count % 2);
    digitalWrite(LED_02, (count >> 1) % 2);
    digitalWrite(LED_03, (count >> 2) % 2);
    
    // Delay para evitar a captura repetitiva do botão pressionado
    delay (700);
  
}
void blink(){//pisca led
  while (initial_time != final_time||
         digitalRead (KEY_01) == HIGH||
         digitalRead (KEY_02) == HIGH) {
    // faz algo repetitivo 8 vezes
    digitalWrite(LED_01, HIGH); //Escreve 1 (HIGH) no LED_01
    digitalWrite(LED_02, HIGH); //Escreve 1 (HIGH) no LED_02
    digitalWrite(LED_03, HIGH); //Escreve 1 (HIGH) no LED_03
    delay(500);  //Espera 500ms
    digitalWrite(LED_01, LOW); //Escreve 0 (LOW) no LED_01
    digitalWrite(LED_02, LOW); //Escreve 0 (LOW) no LED_02
    digitalWrite(LED_03, LOW); //Escreve 0 (LOW) no LED_03
    delay(500);  //Espera 500ms
    initial_time+=500;
  }
  initial_time=0;

}
//Em desenvolvimento
void temperatura_umidade(){
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
//From:https://portal.vidadesilicio.com.br/buzzer-com-esp32-curso-esp32-basico
//Buzzer - Procedimento Simples
void sound_bz_1() 
{
  digitalWrite(PINO_BUZZER_0, HIGH); // Ligar o buzzer
  delay(1000); // Deixa o buzzer ligado por 1 segundo
  digitalWrite(PINO_BUZZER_0, LOW); // Desligar o buzzer
  delay(1000); // Deixa o buzzer desligado por 1 segundo
}
//From:https://portal.vidadesilicio.com.br/buzzer-com-esp32-curso-esp32-basico
//Buzzer - Procedimento Avançado
void sound_bz2() 
{
  // Toca a "Marcha Imperial"
  int melody[] = {
    440, 440, 440, 349, 523, 440, 349, 523, 440,
    659, 659, 659, 698, 523, 784, 740, 698, 659
  };
  int tempo[] = 
  {
    500, 500, 500, 350, 150, 500, 350, 150, 1000,
    500, 500, 500, 350, 150, 500, 350, 150, 1000
  };
  for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) 
  {
    ledcWrite(CANAL_PWM, melody[i]);
    delay(tempo[i] * 1.30); // Pequeno delay para espaçar as notas
    ledcWrite(CANAL_PWM, 0); // Desliga o buzzer ao final de cada nota
    delay(50); // Pequeno delay para evitar cliques entre as notas
  }
  delay(2000); // Aguarda 2 segundos antes de repetir a música
}
//Configuração
void setup() {
  // Define os PINO dos LED's como saída
  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
  pinMode(LED_03, OUTPUT);

  //Define os PINO das chaves como entrada
  pinMode(KEY_01, INPUT);
  pinMode(KEY_02, INPUT);
  pinMode(KEY_03, INPUT);

  // Define o PINO do buzzer 1 como saída
  pinMode(PINO_BUZZER_0, OUTPUT);

  // Configuração do canal PWM (frequência de 1000 Hz, resolução de 8 bits)
  ledcSetup(CANAL_PWM, 1000, 8);
  // Associa o pino do buzzer 2 ao canal PWM  
  ledcAttachPin(PINO_BUZZER_1, CANAL_PWM); 

  //Serial.begin(9600);//Frequencia do Arduino
  Serial.begin(115200);//Frequencia do ESP32

  Serial.println(F("DHTxx test!"));//PREPARATIVOS
  dht.begin();

  delay(2000);         // wait two seconds for initializing
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();          // display on OLED
}
//loop dentro do ESP32
void loop() {
  /** 
  * Lê o valor do botão, se pressionado (press) é LOW (ou 1), se liberado (release)
  * o valor é HIGH (ou 0)
  */
  Serial.println(digitalRead (KEY_01));
  Serial.println(digitalRead (KEY_02));
  Serial.println(digitalRead (KEY_03));
  if ( digitalRead (KEY_01) == HIGH) {
    Serial.println("Botao pressionado!");
    initial_time=0;
    on_off();
  }
  else if ( digitalRead (KEY_02) == HIGH) {
    Serial.println("Botao pressionado!");
    initial_time=0;
    counter();
  }
  else if ( digitalRead (KEY_03) == HIGH) {
    Serial.println("Botao pressionado!");
    initial_time=0;
    blink();
  }
  else{
    Serial.println("Funcao nao especificada!");
  }
}