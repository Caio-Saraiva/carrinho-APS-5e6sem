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


//Zera o valor dos sensores IR.
//bool Sensor1 = 0;
bool Sensor2 = 0;
//bool Sensor3 = 0;
bool Sensor4 = 0;
//bool Sensor5 = 0;

//variável responsável por controlar a velocidade dos motores.
int velocidade = 255;


void setup(){
//Pinos de controle dos motores como saída.
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(dir1, OUTPUT);
pinMode(dir2, OUTPUT);

//Pino para o LED vermelho, saída.
pinMode(A5, OUTPUT);

//Direção inicial do motor como 0, isso fará com que ambos os motores girem para frente.
digitalWrite(dir1, LOW);
digitalWrite(dir2, LOW);

//Pinos dos sensores como entrada
//pinMode(pin_S1, INPUT);  //[não usado]
pinMode(pin_S2, INPUT);
//pinMode(pin_S3, INPUT);  //[não usado]
pinMode(pin_S4, INPUT);
//pinMode(pin_S5, INPUT);  //[não usado]


void loop(){

//Guarda o valor lido pelos sensores IR na variavel correspondente.
//Sensor1 = digitalRead(pin_S1);  //[não usado]
Sensor2 = digitalRead(pin_S2);
//Sensor3 = digitalRead(pin_S3);  //[não usado]
Sensor4 = digitalRead(pin_S4);
//Sensor5 = digitalRead(pin_S5);  //[não usado]


//Comportamento de movimento do carrinho: Para a cor branca valor 0 e para a cor preta, o valor 1.

if((Sensor2 == 1) && (Sensor4 == 1)){ // Se detectar na extremidade das faixas duas cores pretass.
analogWrite(M1, velocidade); // Ambos motores ligam na mesma velocidade.
analogWrite(M2, velocidade);
}

if((Sensor2 == 0) && (Sensor4 == 1)){ // Se detectar um lado branco e o outro preto.
analogWrite(M1, 0); // O motor 1 desliga.
analogWrite(M2, velocidade); // O motor 2 fica ligado, fazendo assim o carrinho virar.
}

if((Sensor2 == 1) && (Sensor4 == 0)){ // Se detectar um lado preto e o outro branco.
analogWrite(M1, velocidade); //O motor 1 fica ligado.
analogWrite(M2, 0); // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido.
}

}

