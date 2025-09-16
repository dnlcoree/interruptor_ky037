const int sensorPin = 10;                 //pino do sensor
const int rlyPin = 2;                     //pino do rele

unsigned long lastTrigTime = 0;           //armazena o tempo do ultimo gatilho detectado 
unsigned long trigTimeout = 2000;         //tempo maximo de 2 segundos para os dois gatilhos acontecerem

int trigCount = 0;                        //contador de gatilhos consecutivos
bool rlyState = false;                    //estado atual do rele (desligado inicialmente)

const int debounce = 50;                  //delay para evitar detecções falsas
unsigned long lastDetect = 0;             //ultimo tempo de detecção

void setup() {

  //configuração dos pinos

  pinMode(sensorPin, INPUT);
  pinMode(rlyPin, OUTPUT);

  //LED iniciando desligado

  digitalWrite(rlyPin, LOW);


}

void loop() {
  
  int sensorState = digitalRead(sensorPin);                           //lê e armazena o estado do sensor (LOW = detecção)

  //verifica se houve som detectado e se passou tempo suficiente desde a última detecção

  if (sensorState == LOW && (millis() - lastDetect) > debounce) {
    lastDetect = millis();                                            //atualiza tempo da última detecção
    soundTrig();                                                      //chama a função que processa a detecção
  }

  //reseta o contador de gatilhos se passar muito tempo

  if (trigCount > 0 && (millis() - lastTrigTime) > trigTimeout) {
    trigCount = 0;
  }
}  

void soundTrig () {

  unsigned long currentTime = millis();                               //obtem e armazena o tempo atual
  
  //verifica se é o primeiro gatilho OU se está dentro do tempo limite
  if (trigCount == 0 || (currentTime - lastTrigTime) < trigTimeout) {
    trigCount++;                                                      //incrementa contador de gatilhos
    lastTrigTime = currentTime;                                       //atualiza tempo do ultimo gatilho

    //se detectados dois gatilhos dentro do tempo limite

    if (trigCount == 2) {
      toggleRly();                                                    //alterna estado do rele
      trigCount = 0;                                                  //reseta contador
    } 
   }
  }

void toggleRly () {

  rlyState = !rlyState;                                               //inverte estado do rele
  digitalWrite(rlyPin, rlyState);                                     //aplica novo estado ao pino
 }  

