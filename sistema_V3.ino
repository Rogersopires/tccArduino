//Livrarias

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <String.h>

// Definicao dos pinos no arduino

int pin_ciclo_mais          = 0;
int pin_ciclo_menos         = 1;
int pin_dezena_mais         = 2;
int pin_dezena_menos        = 3;
int pin_freq_mais           = 4;
int pin_freq_menos          = 5;
int pin_voltar              = 6;
int pin_start               = 7;
int pin_emergencia          = 8;
int pin_rele                = 9;
int pin_sensor_temperatura  = 10;
int pin_sensor_pressao      = 11;
int pin_porta               = 12;
int pin_liga                = 13;


//Estado dos botoes

boolean bot_ciclo_mais    = false;
boolean bot_ciclo_menos   = false;
boolean bot_dezena_mais   = false;
boolean bot_dezena_menos  = false;
boolean bot_freq_mais     = false;
boolean bot_freq_menos    = false;
boolean bot_voltar        = false;
boolean bot_start         = false;
boolean bot_emergencia    = false;
boolean bot_porta         = false;
boolean bot_liga          = false;

// Variaveis do programa

LiquidCrystal_I2C lcd(0x27, 16, 2); // Criando um LCD de 16x2 no endereÃ§o 0x27
unsigned long temporizador_botao;  // temporizaÃ§Ã£o do delay dos botoes
boolean liga_desliga = false;
boolean opcao_menu = true;
int num_ciclo = 1;
int num_dez = 1;
int frequencia = 2;
int forca = 100;
int forca_max = 120;

//Setup

void setup() {
  //Setup de entrada e saida dos pinos
  pinMode(pin_ciclo_mais, INPUT);
  pinMode(pin_ciclo_menos, INPUT);
  pinMode(pin_dezena_mais, INPUT);
  pinMode(pin_dezena_menos, INPUT);
  pinMode(pin_freq_mais, INPUT);
  pinMode(pin_freq_menos, INPUT);
  pinMode(pin_voltar, INPUT);
  pinMode(pin_start, INPUT);
  pinMode(pin_emergencia, INPUT);
  pinMode(pin_porta, INPUT);
  pinMode(pin_rele, OUTPUT);
  pinMode(pin_sensor_pressao, INPUT);
  pinMode(pin_sensor_temperatura, OUTPUT);
  //Inicia o LCD
  lcd.init();
}

//Startup da Maquina

void loop() {
  programa();
}


//Programa da Maquina Ciclicla de Protese Dentarias

void programa() {
  botao_delay(pin_liga, bot_liga);
  if (bot_liga == true) {
    displayApresentacao();
    displayMenu();
    botoesMenu();
  }
  else if (bot_liga == false) {
    displayDespedida();
  }
}


// Tira o delay do botao e muda o estado do botao
void le_botao(int botao, boolean estado) {
  int estado = digitalRead(botao);
  if (estado == HIGH && (millis() - temporizador_botao) > 100) {
    temporizador_botao = millis();
    estado = !estado;
  }
}

// Display no LCD : Apresentacao do TCC
void displayDespedida() {
  lcd.clear();
  lcd.print("Tchau!"); // Exibindo no Lcd Tchau!
  delay(2000);
  lcd.clear();
  lcd.noBacklight(); // Desliga o BackLight do LCD
}

// Display no LCD : Apresentacao do TCC
void displayApresentacao() {
  lcd.backlight();            // Ligando o BackLight do LCD
  lcd.clear();                // limpa a tela
  lcd.print("Maquina Ciclica");
  lcd.setCursor(0, 1);
  lcd.print("Prot. Dentarias");
  delay(3000);
  lcd.clear();
  lcd.print("Tcc Realizado:");
  lcd.setCursor(0, 1);
  lcd.print("Rogers e Felipe");
  delay(3000);
  lcd.clear();
  lcd.print("Orientacao:");
  lcd.setCursor(0, 1);
  lcd.print("Prof. Michele");
  delay(3000);
}

// Display no LCD : Menu inicial ( X ensaio / setup)
void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MENU:");
  lcd.setCursor(6, 0);
  lcd.print("[X]ENSAIOS");
  lcd.setCursor(6, 1);
  lcd.print("[ ]SETUP");
  opcao_menu = true;
}

// Display no LCD : Menu inicial ( ensaio / X setup)
void displayMenu_Setup() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MENU:");
  lcd.setCursor(6, 0);
  lcd.print("[ ]ENSAIOS");
  lcd.setCursor(6, 1);
  lcd.print("[X]SETUP");
  opcao_menu = false;
}

// Ativa os botoes no menu
void botoesMenu() {
  botao_delay(pin_start, bot_start);
  botao_delay(pin_freq_mais, bot_freq_mais);
  botao_delay(pin_freq_menos, bot_freq_menos);
  if (bot_start == true) {
    if (opcao_menu == true) {
      displayEnsaio();
      menuVoltar();
    }
    else if (opcao_menu == false) {
      displaySetup();
      menuVoltar();
    }
    bot_start == false;
  }
  if (bot_freq_mais == true) {
    displayMenu();
  }
  if (bot_freq_menos == true) {
    displayMenu_Setup()
  }
}

// Display no LCD : Ensaio Mecanico
void displayEnsaio() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ciclos:");
  lcd.setCursor(8, 0);
  lcd.print(num_ciclo);
  lcd.setCursor(10, 0);
  lcd.print("x 10^");
  lcd.setCursor(15, 0);
  lcd.print(num_dez);
  lcd.setCursor(0, 1);
  lcd.print("Frequencia:");
  lcd.setCursor(12, 1);
  lcd.print(frequencia);
  lcd.setCursor(14, 1);
  lcd.print("Hz");
}

// Display no LCD : Setup Maquina
void displaySetup() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setup da Maquina");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Forca:");
  lcd.setCursor(12, 0);
  lcd.print(forca);
  lcd.setCursor(15, 0);
  lcd.print("N");
  lcd.setCursor(0, 1);
  lcd.print("Forca Max:");
  lcd.setCursor(12, 1);
  lcd.print(forca_max);
  lcd.setCursor(15, 1);
  lcd.print("N");
}

//Volta do Ensaio / Setup para o menu
void menuVoltar() {
  botao_delay(pin_voltar, bot_voltar);
  if (bot_voltar == true) {
    bot_voltar = false;
    displayMenu();
    botoesMenu();
  }
}

