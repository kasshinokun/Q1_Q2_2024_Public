/*
Código do trabalho entregue por Gabriel Cassino


Base code from: https://lobodarobotica.com/blog/web-server-com-esp32-conexao-wifi/
and code from: https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
and my code html


Adaptação para se adequar ao vídeo - código da placa ainda não foi salvo no GitHub
*/

//=========================Bibliotecas=====================================================================================
#include <WiFi.h>
#include <FS.h>          
#include <WiFiManager.h> 
#include <DNSServer.h>
#include <WebServer.h>

//=========================Pinos na Placa==================================================================================
const int KEY_01 = 12;
const int KEY_02 = 13;
const int KEY_03 = 14;
const int LED_01 = 25;
const int LED_02 = 26;
const int LED_03 = 27;

//=========================Configuraçoes===================================================================================
// Configuraçoes e Endereço de Internet WIFI

WiFiServer server (80);  //Default

const char* ssid = "ongtiu-interna";
const char* password = "ademir1993";

const char* ssid2 = "A52s";
const char* password2 = "biel1024";

const char* ssid3 = "B.Cassino";
const char* password3 = "biel1024";

const char* ssid4 = "j2";
const char* password4 = "biel1024";

const char* ssid5 = "ESP32_IoT";
const char* password5 = "12345678";

//configurações de IP Fixo
IPAddress local_IP(192, 168, 1, 184);

IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   
IPAddress secondaryDNS(8, 8, 4, 4); 

//Configurações de tempo
//tempo atual
unsigned long currentTime = millis();
//tempo anterior
unsigned long previousTime = 0; 
// Define intervalo em milisegundos (exemplo: 1000ms = 1s)
const long timeoutTime = 1000;

//=========================Funções=========================================================================================
void esp_wifi(){

  WiFiClient client = server.available();   

  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("new client");           
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    

          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");

            client.println("Content-type:text/html");
            client.println();

            client.println("<!DOCTYPE html><html lang=\"pt-br\">");

            client.println("<head><meta charset=\"utf-8\" />");
            client.println("<title>ESP32 WebServer</title>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            // CSS para estilizar os botões e Pagina
            client.println("<style>");
            client.println("h1{font-size:16 px;color:black;}");
            client.println("h4{font-size:2vw;color:black;}");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<center>");
            client.println("<h1>");

            client.println("<h4 class=\"login_title\"><br>Internet das Coisas I<br>");
            client.println("ESP32 - Relatorio 01<br>Devices and peripherals<br><br>");
            client.println("Resp.: Gabriel da Silva Cassino</h4>");

            client.print("Clique <a href=\"/H1\"><button>aqui</button></a> para ligar o LED_01<br>");
            client.print("Clique <a href=\"/H2\"><button>aqui</button></a> para ligar o LED_02<br>");
            client.print("Clique <a href=\"/H3\"><button>aqui</button></a> para ligar o LED_03<br>");
            client.print("Clique <a href=\"/H4\"><button>aqui</button></a> para ligar todos os LED's<br>");


            client.print("Clique <a href=\"/L1\"><button>aqui</button></a> para desligar o LED_01<br>");
            client.print("Clique <a href=\"/L2\"><button>aqui</button></a> para desligar o LED_02<br>");
            client.print("Clique <a href=\"/L3\"><button>aqui</button></a> para desligar o LED_03<br>");
            client.print("Clique <a href=\"/L4\"><button>aqui</button></a> para desligar todos os LED's<br>");

            client.println("<br>Leitura dos LED's<br>");

            //LED_01
            if(digitalRead(LED_01)==HIGH){
            client.println("Valor no LED_01: ON<br>");
            }
            else{
            client.println("Valor no LED_01: OFF<br>");
            }
            //LED_02
            if(digitalRead(LED_02)==HIGH){
            client.println("Valor no LED_02: ON<br>");
            }
            else{
            client.println("Valor no LED_02: OFF<br>");
            }
            //LED_03
            if(digitalRead(LED_03)==HIGH){
            client.println("Valor no LED_03: ON<br>");
            }
            else{
            client.println("Valor no LED_03: OFF<br>");
            }


            client.println();
            client.println("</center>");
            client.println("</h1>");
            client.println("</body>");
            client.println("</html>");

            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;      
        }


        if (currentLine.endsWith("GET /H1")) {
          digitalWrite(LED_01, HIGH);               
        }
        if (currentLine.endsWith("GET /L1")) {
          digitalWrite(LED_01, LOW);                
        }

        if (currentLine.endsWith("GET /H2")) {
          digitalWrite(LED_02, HIGH);               
        }
        if (currentLine.endsWith("GET /L2")) {
          digitalWrite(LED_02, LOW);                
        }

        if (currentLine.endsWith("GET /H3")) {
          digitalWrite(LED_03, HIGH);              
        }
        if (currentLine.endsWith("GET /L3")) {
          digitalWrite(LED_03, LOW);                
        }

        if (currentLine.endsWith("GET /H4")) {
          digitalWrite(LED_01, HIGH);
          digitalWrite(LED_02, HIGH); 
          digitalWrite(LED_03, HIGH);                
        }
        if (currentLine.endsWith("GET /L4")) {
          digitalWrite(LED_01, LOW);
          digitalWrite(LED_02, LOW); 
          digitalWrite(LED_03, LOW);                
        }

      }
    }

      client.stop();

  }
}
void counting(){//contador de 3 bits
  Serial.println("Contando com LED's.");
  Serial.println("Binario é 000.");
  digitalWrite(LED_01, LOW); 
  digitalWrite(LED_02, LOW); 
  digitalWrite(LED_03, LOW); 
  delay(1000);
  Serial.println("Binario é 001.");
  digitalWrite(LED_01, HIGH); 
  digitalWrite(LED_02, LOW); 
  digitalWrite(LED_03, LOW); 
  delay(1000);
  Serial.println("Binario é 010.");
  digitalWrite(LED_01, LOW); 
  digitalWrite(LED_02, HIGH);
  digitalWrite(LED_03, LOW);
  delay(1000);
  Serial.println("Binario é 011.");
  digitalWrite(LED_01, HIGH); 
  digitalWrite(LED_02, HIGH);
  digitalWrite(LED_03, LOW);
  delay(1000);
  Serial.println("Binario é 100.");
  digitalWrite(LED_01, LOW); 
  digitalWrite(LED_02, LOW);
  digitalWrite(LED_03, HIGH);
  delay(1000);
  Serial.println("Binario é 101.");
  digitalWrite(LED_01, HIGH); 
  digitalWrite(LED_02, LOW);
  digitalWrite(LED_03, HIGH);
  delay(1000);
  Serial.println("Binario é 110.");
  digitalWrite(LED_01, LOW); 
  digitalWrite(LED_02, HIGH);
  digitalWrite(LED_03, HIGH);
  delay(1000);
  Serial.println("Binario é 111.");
  digitalWrite(LED_01, HIGH); 
  digitalWrite(LED_02, HIGH);
  digitalWrite(LED_03, HIGH);
  delay(1000);
  Serial.println("Desligando os LED's.");
  digitalWrite(LED_01, LOW); 
  digitalWrite(LED_02, LOW); 
  digitalWrite(LED_03, LOW); 
}
void checking(){//Checagem de Led's e leitura das chaves

  Serial.println("Checando LED's e KEY's");
  for(int i=0;i<4;i++){
    delay(2000);
    int k=i+1;
    Serial.println(String("Processo 0"+(k)));
    if(digitalRead(KEY_01)==HIGH){
      Serial.println("Key 01 está em HIGH.");
      digitalWrite(LED_01, HIGH); 
      digitalWrite(LED_02, LOW);
      digitalWrite(LED_03, LOW);  
    }
    else if(digitalRead(KEY_02)==HIGH){
      Serial.println("Key 02 está em HIGH.");
      digitalWrite(LED_01, LOW); 
      digitalWrite(LED_02, HIGH);
      digitalWrite(LED_03, LOW);  
    }
    else if(digitalRead(KEY_03)==HIGH){
      Serial.println("Key 03 está em HIGH.");
      digitalWrite(LED_01, LOW); 
      digitalWrite(LED_02, LOW);
      digitalWrite(LED_03, HIGH); 
    }
  }
}

void esp_resetWIFI() {//reset do wifi
  Serial.println("Preparando para reset.......");
  digitalWrite(LED_01, LOW); //apaga os led's
  digitalWrite(LED_02, LOW); 
  digitalWrite(LED_03, LOW); 
  delay(500);
  digitalWrite(LED_02, HIGH); //acende o led 02
  delay(1500);
  digitalWrite(LED_01, HIGH); //acende os demais
  digitalWrite(LED_03, HIGH);

  Serial.println(String("o valor da Key 03 é: "+digitalRead(KEY_03)));
  delay(2000);
  //Verifica se o botao foi pressionado

  int valor = digitalRead(KEY_03);
  if (valor == 1) {
    digitalWrite(LED_01, LOW); 
    digitalWrite(LED_02, LOW); 
    digitalWrite(LED_03, LOW); 
    Serial.println(String("O valor lido na Key 03 é: "+digitalRead(KEY_03)));
    //Apaga os dados da rede wifi gravados na memoria e reinicia o ESP
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    Serial.println("Configuracoes zeradas!");
    ESP.restart();
  }else{
    Serial.println(String("O valor lido na Key 03 é: "+digitalRead(KEY_03)));
    Serial.println("Configuracoes mantidas!");
  }
}


//Metodos para configuração do wifi
void wifi_manager(){

  Serial.println("Configurando rede Wifi");

  WiFiManager wifiManager;

  wifiManager.setConfigPortalTimeout(240);
  //Cria um AP (Access Point) com: ("nome da rede", "senha da rede")
  if (!wifiManager.autoConnect(ssid5, password5)) {
    Serial.println(F("Falha na conexao. Resetar e tentar novamente..."));
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  delay(150);

}
void wifi_connection(){

   Serial.println(ssid);
   WiFi.begin(ssid, password);
  //outras redes para testes
  //WiFi.begin(ssid2, password2);
  //WiFi.begin(ssid3, password3);
  //WiFi.begin(ssid4, password4);


}
void wifi_state(){//analise da conexão wifi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("------------------------------------------------------------");
    Serial.print("Hostname: ");
    Serial.println(WiFi.getHostname());
    Serial.print("Conectado no IP: ");
    Serial.println(WiFi.localIP());

    Serial.println("------------------------------------------------------------");
    delay(150);
  }
  else{
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }
}
//=========================Configuraçoes Iniciais==========================================================================
void setup() {


  Serial.begin(115200);

  WiFi.setHostname("ESP32_Server");


  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA falhou em configurar");
  }else{
    Serial.println("STA configurado com sucesso");
  }

  wifi_manager();

  wifi_connection();

  wifi_state();

  //*** SETUP -- Definição dos Pinos -- //////////
  delay(50);

  //pinMode(BUZZER_01,OUTPUT); //Define BUZZER_01 como saida
  pinMode(KEY_01,INPUT); // Define KEY_01 como entrada
  pinMode(KEY_02,INPUT); // Define KEY_02 como entrada
  pinMode(KEY_03,INPUT); // Define KEY_03 como entrada
  pinMode(LED_01,OUTPUT); //Define LED_01 como saida
  pinMode(LED_02,OUTPUT); //Define LED_02 como saida
  pinMode(LED_03,OUTPUT); //Define LED_03 como saida

  Serial.println("Iniciado **************************");
  server.begin();
}
//=========================Processos em Loop==============================================================================
void loop() {
  //inicia página
  esp_wifi();
  if(digitalRead(KEY_01)==HIGH){
    Serial.println("Key 01 está em HIGH.");
    checking(); 
  }
  else if(digitalRead(KEY_02)==HIGH){
    Serial.println("Key 02 está em HIGH.");
    esp_resetWIFI();
  }
  else if(digitalRead(KEY_03)==HIGH){
    Serial.println("Key 03 está em HIGH.");
    counting();
  }
  else{
    wifi_state();
    Serial.println("ESP32 ativado sem função definida.");

  }
  delay(1000);
}


//-------------------------------------------------------------------------
//código a seguir desenvolvido por Gabriel Cassino e Bruno Henrique 

//-------------------------------------------------------------------------
//Relatório 02 - IoT - Gabriel da Silva Cassino e Bruno Henrique Reis Almeida
//INCLUSÃO DE BIBLIOTECA
#include "DHT.h" //DHT11

//Para o Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold18pt7b.h>



//################################################################
//Variaveis para o projeto

const int DHT11_1 = 4; //PINO ANALÓGICO UTILIZADO PELO DHT11

#define DHTTYPE DHT11  //VARIAVEL TIPO A SER UTILIZADA PELO DHT11(PRECISO ADAPTAR)

const int PINO_BUZZER_0 = 23; // Pino D23 conectado ao buzzer ativo
const int PINO_BUZZER_1 = 25;// Pino D24 conectado ao buzzer passivo(VALOR GENERICO PRECISO DEFINIR CORRETAMENTE)

const int CANAL_PWM = 0;   // Canal PWM utilizado para o buzzer passivo

//Pinos dos LEDs
int LED_01 = 13;
int LED_02 = 14;
int LED_03 = 15;

// Pino do botão
int KEY_01 = 16;
int KEY_02 = 17;
int KEY_03 = 18;

// contador
int count = 0;

//variavel para tempo(generica)
int initial_time=0;
int final_time=5000;

int h, t;


//Definições para o display
#define LARGURA_OLED 128
#define ALTURA_OLED 64
 
#define RESET_OLED 4
#define bitmap_height   128
#define bitmap_width    64

Adafruit_SSD1306 display(LARGURA_OLED, ALTURA_OLED, &Wire, RESET_OLED);
DHT dht(DHT11_1, DHTTYPE);

static const unsigned char PROGMEM logo_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0F, 0x8F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x78, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x80, 0x08, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x80, 0x78, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x80, 0x08, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xC0, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xC0, 0x78, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x01, 0xC0, 0x78, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xC0, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xE0, 0x08, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xE0, 0x78, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x07, 0xF0, 0x08, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0F, 0xF0, 0x08, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x0F, 0xF8, 0x78, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x1F, 0xF8, 0x08, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x1F, 0xF8, 0x08, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x3F, 0xFC, 0x78, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x3F, 0xFE, 0x08, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7F, 0xFE, 0x0F, 0x8F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7F, 0xFF, 0x7F, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0x0F, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xFF, 0xFF, 0x0F, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0xFF, 0xFF, 0x7F, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xFF, 0x0F, 0x8F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xFF, 0x0F, 0x87, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xFF, 0x1F, 0x8F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0xFF, 0xFF, 0x7F, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0xFF, 0xFF, 0x0F, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0xFF, 0xFF, 0x0F, 0x8F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xFF, 0xFF, 0x7F, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xFF, 0xFF, 0x0F, 0x8F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0x0F, 0xF3, 0xEF, 0x83, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3E, 0x03, 0xE7, 0xCF, 0xC0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3C, 0x61, 0xC7, 0x9F, 0xE0, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7C, 0x71, 0xCF, 0xBF, 0xE3, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7C, 0x71, 0xCF, 0xBF, 0xF3, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7C, 0x71, 0x9F, 0xBF, 0xE3, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFC, 0x71, 0x3F, 0xBF, 0xE3, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFC, 0x71, 0x38, 0x1F, 0xE7, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFC, 0x02, 0x20, 0x0F, 0x87, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFE, 0x06, 0x46, 0x03, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0x8C, 0xC7, 0x18, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xFC, 0xC7, 0x1C, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xF9, 0xC7, 0x1C, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xF9, 0xC7, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0xF3, 0xC6, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0xE3, 0xC0, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0xE7, 0xE0, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1F, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x07, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

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
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("°C");
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.println("%");
  display.display();
  //display.clearDisplay();
  showBitmap();
  printText();
  display.display();
  delay(500);
  display.clearDisplay();
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

void alarme(){
  for(int i=0; i<5; i++){
    digitalWrite(LED_01, HIGH);
    digitalWrite(LED_02, HIGH);
    digitalWrite(LED_03, HIGH);
    digitalWrite(PINO_BUZZER_0, HIGH);
    delay(500);
    digitalWrite(LED_01, LOW);
    digitalWrite(LED_02, LOW);
    digitalWrite(LED_03, LOW);
    digitalWrite(PINO_BUZZER_0, LOW);
    delay(500);
  }
}

void printText() {
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(45, 28);            // Start at top-left corner
  display.print(t);
  display.drawCircle(92, 8, 3, WHITE);
  display.setCursor(100, 27);
  display.print("C");
  display.setCursor(45, 62);
  display.print(h);
  display.print("%");

}

void showBitmap(void) {
  display.drawBitmap(0, 0, logo_bmp, bitmap_height, bitmap_width, WHITE);
  //display.display();
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
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  printText();
}
//loop dentro do ESP32
void loop() {
  Serial.println("\n-----------------------------------");
  int estado = digitalRead(KEY_01);
  Serial.print("Botão = ");
  Serial.println(estado);
  if(estado == HIGH){
    temperatura_umidade();
  }
  else{
    Serial.println("Alarme acionado");
    // display.display();
    // display.clearDisplay();
    // display.setTextSize(2);
    // display.setCursor(0,0);
    // display.println("ENCHENTE");
    alarme();
    // display.clearDisplay();
    // display.display();
  }

}