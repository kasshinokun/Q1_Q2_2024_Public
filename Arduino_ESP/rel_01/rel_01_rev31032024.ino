/*
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