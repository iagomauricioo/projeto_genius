 //Mapeamento dos pinos
#define pin_bt1 2
#define pin_bt2 3
#define pin_bt3 4
#define pin_bt4 5
#define pin_led1 6
#define pin_led2 7
#define pin_led3 8
#define pin_led4 9
#define pin_buzzer 10
#define pin_btReset 11

//Mapeamento das notas do buzzer
#define C5     523
#define D5     587
#define E5     659
#define B4     493
#define A_sus4 466 

#define a 12
#define b 13
#define c A2
#define d A3
#define e A4
#define f A0
#define g A1

//Variáveis globais
int number_random = 0;            // Variável que armazena o número aleatório
int memory_number[100];          // Vetor que vai armazenando os números aleatórios
int memory_position = 0;         // Posição do número aleatório no vetor
int botao_position = 0;          // Variável que informa qual dos quatro botões foi pressionado
const byte POTENCIOMETRO = A5;	//Variável do potenciometro
unsigned int ValorPotenciometro; //Valor recebido do potenciometro



void displayAcender1() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void displayAcender2() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void displayAcender3() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void displayAcender4() {
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayAcender5() {
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayAcender6(){
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayAcender7() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void displayAcender8() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayAcender9() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void displayAcender0() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

//Flags dos botões
bool flag1 = 0;
bool flag2 = 0;
bool flag3 = 0;
bool flag4 = 0;
bool flagReset = 0;

//Protótipo das funções
void ler_botoes();
void acender_led(int n);
bool validar_execucao();
void mostrar_sequencia_leds();
int random_generator();
void end_game();

void setup() {
  //Configurando os botões como entrada com resistor de pull-up
  pinMode(pin_bt1,INPUT_PULLUP);
  pinMode(pin_bt2,INPUT_PULLUP);
  pinMode(pin_bt3,INPUT_PULLUP);
  pinMode(pin_bt4,INPUT_PULLUP);
  pinMode(pin_btReset,INPUT_PULLUP);

  //Configurando os LEDs como saída
  pinMode(pin_led1,OUTPUT);
  pinMode(pin_led2,OUTPUT);
  pinMode(pin_led3,OUTPUT);
  pinMode(pin_led4,OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  //Configurando potenciometro como entrada
  pinMode(POTENCIOMETRO, INPUT);

  //Inicializar o gerador de números aleatórios com uma entrada significantemente aleatória utilizando o pino A0
 /*  randomSeed(analogRead(A0)); */

  //Vetor totalmente nulo
  for(int i=0; i<100; i++){
    memory_number[i] = 0;  
  }

  number_random = random_generator();               //Guardando o valor aleatório
  memory_number[memory_position] = number_random;   //Guardando o número aleatório no vetor

  acender_led(number_random);                       //Acender LED para mostrar o número escolhido
}

void loop() {
  // Ler o valor do potenciômetro
  ValorPotenciometro = analogRead(POTENCIOMETRO);
  
  if (ValorPotenciometro > 113) {
   displayAcender0(); 
  }
  
  if (ValorPotenciometro >= 0 && ValorPotenciometro <= 113) { 
    displayAcender9();
  }
  
  if (ValorPotenciometro > 113 && ValorPotenciometro <= 113*2) {
    displayAcender8();
  }
  
  if (ValorPotenciometro > 113*2 && ValorPotenciometro <= 113*3) {
    displayAcender7();
  }
  
  if (ValorPotenciometro > 113*3 && ValorPotenciometro <= 113*4) {
    displayAcender6();
  }
  
  if (ValorPotenciometro > 113*4 && ValorPotenciometro <= 113*5) {
    displayAcender5();
  }
  
  if (ValorPotenciometro > 113*5 && ValorPotenciometro <= 113*6) {
    displayAcender4();
  }
  
  if (ValorPotenciometro > 113*6 && ValorPotenciometro <= 113*7) {
    displayAcender3();
  }

  if (ValorPotenciometro > 113*7 && ValorPotenciometro <= 113*8) {
    displayAcender2();
  }

  if (ValorPotenciometro > 113*8 && ValorPotenciometro < 113*9) {
    displayAcender1();
  }

  // Aguarde um curto intervalo para evitar a leitura rápida do potenciômetro
  delay(100);
  
  //Verifica se os botões pressionados corresponde a sequência gerada
  if(validar_execucao() == 1){
    delay(200);
    memory_position += 1; 
    number_random = random_generator();
    memory_number[memory_position] = number_random;

    mostrar_sequencia_leds();
  }
}

//Função para ler botões
void ler_botoes(){
  if(!digitalRead(pin_bt1)){
    flag1 = 1;  
    delay(30);
  }

  if(!digitalRead(pin_bt2)){
    flag2 = 1;  
    delay(30);
  }

  if(!digitalRead(pin_bt3)){
    flag3 = 1;  
    delay(30);
  }
  
  if(!digitalRead(pin_bt4)){
    flag4 = 1;  
    delay(30);
  }
  
  if(!digitalRead(pin_btReset)){
    flagReset = 1;  
    delay(30);
  }
  
  if(digitalRead(pin_bt1) && flag1){
    flag1 = 0;
    acender_led(1);
    delay(30);
    botao_position = 1;
  } 

  if(digitalRead(pin_bt2) && flag2){
    flag2 = 0;
    acender_led(2);
    delay(30);
    botao_position = 2;
  } 

  if(digitalRead(pin_bt3) && flag3){
    flag3 = 0;
    acender_led(3);
    delay(30);
    botao_position = 3;
  }
  
  if(digitalRead(pin_bt4) && flag4){
    flag4 = 0;
    acender_led(4);
    delay(30);
    ////botao_position = 4;
  }
  
  if(digitalRead(pin_btReset) && flagReset){
    flagReset = 0;
    delay(30);
    botao_position = 5;
  }
}

//Função para acender os LEDs e tocar o buzzer
void acender_led(int n){
  ValorPotenciometro = analogRead(POTENCIOMETRO);
  
  if(n==1){
    digitalWrite(pin_led1,HIGH);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,LOW);
    tone(pin_buzzer,C5);
    delay(ValorPotenciometro);
    noTone(pin_buzzer);
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,LOW);
    delay(ValorPotenciometro);
  }
  else if(n==2){
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,HIGH);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,LOW);
    tone(pin_buzzer,D5);
    delay(ValorPotenciometro);
    noTone(pin_buzzer);
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,LOW);
    delay(ValorPotenciometro);
  } 
  else if(n==3){
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,HIGH);
    digitalWrite(pin_led4,LOW);
    tone(pin_buzzer,E5);
    delay(ValorPotenciometro);
    noTone(pin_buzzer);
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,LOW);
    delay(ValorPotenciometro);
  }
  else if(n==4){
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,HIGH);
    tone(pin_buzzer,B4);
    delay(ValorPotenciometro);
    noTone(pin_buzzer);
    digitalWrite(pin_led1,LOW);
    digitalWrite(pin_led2,LOW);  
    digitalWrite(pin_led3,LOW);
    digitalWrite(pin_led4,LOW);
    delay(ValorPotenciometro);
  }   
}

//Função para validar a sequência de cliques do botão
bool validar_execucao(){
  int varredura = 0;
  while(varredura < 100){
    ler_botoes();
    if (botao_position != 0){
      if(memory_number[varredura] != botao_position){
        botao_position = 0;
        end_game();
        return 0;
        break;
      }  
       else{
        varredura += 1; 
        botao_position = 0;
       }
    }

    if(memory_number[varredura] == 0){
      return 1;
      break;  
    }
  }
}

//Função que mostra a sequência de números aleatórios armazenados no vetor
void mostrar_sequencia_leds(){
  for(int i=0; i<100; i++){
    if (memory_number[i] != 0){
      acender_led(memory_number[i]);
    }else{
      break; 
     }  
  }  
}


//Função para tentar deixar o número mais aleatório
int random_generator(){
  int num = 0;
  int media = 0;
  for(int i=0; i<10; i++){
    num += random(0,1000);  
  }

  media = num/10;
  media = (media%3)+1;

  return media;
}

//Função que gera a melodia de game over
void end_game(){
  int tempo = 2000;

  tone(pin_buzzer, C5);
  delay(tempo/12);
  tone(pin_buzzer, B4);
  delay(tempo/12);
  tone(pin_buzzer, A_sus4);
  delay(tempo/12);

  tone(pin_buzzer, A4);
  delay(tempo/2);
  noTone(pin_buzzer);

  for(int i=0; i<100; i++){
    memory_number[i] = 0;  
  }

  memory_position = 0;

  delay(1000);
  number_random = random_generator();
  memory_number[memory_position] = number_random;
  acender_led(memory_number[memory_position]);
}
