//Codigo carrinho APS 5º& 6ºsemestre.

//Definição dos pinos de controle do motor
#define M1 3 // Pino_Velocidade 1º Motor ( 0 a 255) Porta IN2 ponte H.
#define M2 5 //Pino_Velocidade 2º Motor ( 0 a 255) Porta IN4 ponte H.
#define dir1 2 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW) porta IN1 ponte H.
#define dir2 4 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW) porta IN3 ponte H.

//Definição dos pinos dos sensores IR
//#define pin_S1 6  //Sensor IR 1. [não usado]
#define pin_S2 7  //Sensor IR 2.
//#define pin_S3 8  //Sensor IR 3. [não usado]
#define pin_S4 9  //Sensor IR 4.
//#define pin_S5 10  //Sensor IR 5. [não usado]

#define S0 12 //Sensor de Cor 0.
#define S1 11 //Sensor de Cor 1.
#define S2 8  //Sensor de Cor 2.
#define S3 6  //Sensor de Cor 3.
#define SOUT 13  //Sensor Saida de Frequencia.

//Zera o valor dos sensores IR.
//bool Sensor1 = 0;
bool Sensor2 = 0;
//bool Sensor3 = 0;
bool Sensor4 = 0;
//bool Sensor5 = 0;
int velocidadeConst = 150;
//variável responsável por controlar a velocidade dos motores.
int velocidade = velocidadeConst;

int redColor = 0; // declara uma variavel int de nome red para uso do sensor de cor.
int greenColor = 0; // declara uma variavel int de nome green para uso do sensor de cor.
int blueColor = 0;// declara uma variavel int de nome blue para uso do sensor de cor.

int redFrequency = 0; //declara uma variavel de frequencia de cor.
int greenFrequency = 0; //declara uma variavel de frequencia de cor.
int blueFrequency = 0; //declara uma variavel de frequencia de cor.

void setup() {
  Serial.begin(9600);
  //Pinos de controle dos motores como saída.
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  //coloca os fotodiodos em funcionamento.
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  //Pino para o LED vermelho, saída.
  pinMode(10, OUTPUT);

  //Direção inicial do motor como 0, isso fará com que ambos os motores girem para frente.
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);

  //Pinos dos sensores como entrada
  //pinMode(pin_S1, INPUT);  //[não usado]
  pinMode(pin_S2, INPUT);
  //pinMode(pin_S3, INPUT);  //[não usado]
  pinMode(pin_S4, INPUT);
  //pinMode(pin_S5, INPUT);  //[não usado]

  //Pinos do sensor de cor. Sensores como saida e sensor de frequencia como entrada.
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SOUT, INPUT);

  //declara o pino de LED.
  pinMode(A5, OUTPUT);
}

void loop() {

  //Comportamento de movimento do carrinho: Para a cor branca valor 0 e para a cor preta, o valor 1.

  if ((Sensor2 == 1) && (Sensor4 == 1)) { // Se detectar na extremidade das faixas duas cores pretass.
    analogWrite(M1, velocidade); // Ambos motores ligam na mesma velocidade.
    analogWrite(M2, velocidade);
  }

  if ((Sensor2 == 0) && (Sensor4 == 1)) { // Se detectar um lado branco e o outro preto.
    analogWrite(M1, 50); // O motor 1 desliga.
    analogWrite(M2, velocidade); // O motor 2 fica ligado, fazendo assim o carrinho virar.
  }

  if ((Sensor2 == 1) && (Sensor4 == 0)) { // Se detectar um lado preto e o outro branco.
    analogWrite(M1, velocidade); //O motor 1 fica ligado.
    analogWrite(M2, 50); // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido.
  }

// Leitura dos fotodiodos R, G, B (vermelho, verde e azul).
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(SOUT, LOW);
  redColor = map(redFrequency, 22, 190, 255, 0);
  delay(100);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(SOUT, LOW);
  greenColor = map(greenFrequency, 48, 190, 255, 0);
  delay(100);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(SOUT, LOW);
  blueColor = map(blueFrequency, 48, 190, 255, 0);
  delay(100);

//Print(impressão) no serial para debug das cores.
  Serial.print("R= ");
  Serial.print(redColor);
  Serial.print(" ");
  Serial.print("G= ");
  Serial.print(greenColor);
  Serial.print(" ");
  Serial.print("B= ");
  Serial.print(blueColor);
  Serial.println(" ");


  //Guarda o valor lido pelos sensores IR na variavel correspondente.
  //Sensor1 = digitalRead(pin_S1);  //[não usado]
  Sensor2 = digitalRead(pin_S2);
  //Sensor3 = digitalRead(pin_S3);  //[não usado]
  Sensor4 = digitalRead(pin_S4);
  //Sensor5 = digitalRead(pin_S5);  //[não usado]

  if (redColor > 0 || greenColor > 0 || blueColor > 0) {

    if (redColor > greenColor && redColor > blueColor && blueColor > greenColor && redColor > 0 && greenColor > 0 && blueColor > 0 && redColor >= 200) {
      velocidade = 0;
      Serial.println("Vermelho");
      analogWrite(M1, 0);
      analogWrite(M2, 0);
      //vermelho
    }
    if (redColor > 0 && greenColor > 0 && blueColor > 0 && redColor >= 180 && greenColor >= 225 && blueColor >= 230 && redColor < 220) {
      velocidade = velocidadeConst;
      Serial.println("Verde");
      analogWrite(M1, velocidade);
      analogWrite(M2, velocidade);
      //verde
    }
    if (redColor > 0 && greenColor > 0 && blueColor > 0 && redColor >= 265 && greenColor >= 300 && blueColor >= 270) {

      digitalWrite(A5, HIGH);
      delay(300);
      digitalWrite(A5, LOW);
      Serial.println("Amarelo");
      //amarelo
    }
  }
}
