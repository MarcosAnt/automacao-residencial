/*
  Universidade Federal do Paraná
  TADS - SEPT

  Projeto de Automação Residencial

  Equipe:
  João Victor Alves da Maia
  Marcos Antonio da Silva

  Última alteração: 24/11/2018
*/

//Portas
#define motor            2
#define IN3              6
#define IN4              7
#define LED              13
#define LM35             A0

void setup(){
  Serial.begin(9600); //Inicialização da porta serial
  pinMode(LED, OUTPUT); //Inicialização do led
  //Inicialização do motor
  pinMode(motor, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

/*
  Controla funcionamento do LED
  1 - liga
  2 - desliga
*/
void controleLed(char opcao) {
  if (opcao == '1') {
    digitalWrite(LED, HIGH);
  }
  else if(opcao == '2') {
    digitalWrite(LED, LOW);
  }
}

//Acionamento do motor
void subir(int limite){
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(motor,255);
  delay(limite);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
}

//Acionamento do motor
void descer(int limite){
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(motor,255);
  delay(limite);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,HIGH);
}

//Verifica temperatura para detrminar a velocidade para acionar o motor
void acionarPerciana() {
  subir(1000);
}

//Le a temperatura do sensor
float monitorarTemperatura() {
  float temperatura = 0;

  temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
  return(temperatura);
}

void loop(){
  //Le dados enviados via porta serial
  char comando = Serial.read();

  //Trata parametro recebido
  if(comando == '1' || comando == '2') {
    controleLed(comando);
  }
  else if(comando == '3') {
    acionarPerciana();
  }
  else if(comando == '4') {
    int i = 0;
    for(i; i < 10; i++){
      Serial.write(char(monitorarTemperatura()));
    }
  }
}

