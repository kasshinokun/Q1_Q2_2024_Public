//-------------------------------------------------------------------------
//Relatório 02 - IoT - Gabriel da Silva Cassino 

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

//Procedimentos
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
void blind(){//pisca led
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
void setup() {
  pinMode(LED_01, OUTPUT);
  pinMode(LED_02, OUTPUT);
  pinMode(LED_03, OUTPUT);

  pinMode(KEY_01, INPUT);
  pinMode(KEY_02, INPUT);
  pinMode(KEY_03, INPUT);

  Serial.begin(9600);//Frequencia do Arduino
  //Serial.begin(115200);//Frequencia do ESP32
}

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
    blind();
  }
  else{
    Serial.println("Funcao nao especificada!");
  }
}