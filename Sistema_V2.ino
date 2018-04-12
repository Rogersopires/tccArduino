//Livrarias 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <String.h>  


// Definição dos pinos no arduino 

int bot_cicla_pin = 6; //define input do botão
int ciclo_pin = 9; //define output do ciclo
int liga_pin  = 7; //liga e desliga o sistema
int led_liga_pin = 13;// led indicando liga e desliga
int bot_add_num = 1;// aumenta o numero de ciclos
int bot_rem_num = 2;// remove o numero de ciclos
int bot_add_dez = 3;// aumenta o numero de dezenas
int bot_rem_dez = 4;// remove o numero de dezenas
int bot_add_freq = 11;// aumenta o numero de frequencia
int bot_rem_freq = 12;// remove o numero de frequencia

// Variaveis do programa

//temporizadores dos botoes
unsigned long tempo_bot_liga; // botao liga/desliga
unsigned long tempo_bot_cicla; // botao cicla
unsigned long tempo_bot_add_num; // botao aumenta o numero
unsigned long tempo_bot_rem_num; // botao remove o numero
unsigned long tempo_bot_add_dez; // botao aumenta a dezena
unsigned long tempo_bot_rem_dez; // botao remove a dezena
unsigned long tempo_bot_add_freq; // botao aumenta a frequencia
unsigned long tempo_bot_rem_freq; // botao remove a frequencia

//controle

LiquidCrystal_I2C lcd(0x27,16,2);  // Criando um LCD de 16x2 no endereço 0x27
boolean liga_desliga =  LOW; // coloca o estado em liga ou desliga dos botoes
boolean ligado =  HIGH; // diz a mensagem Oi uma vez
int num_dez = 1; // mostra a dezena na qual vai ser adicionada
int num_ciclo = 1; // numero de ciclos
int frequencia = 2; // setup de frequencia


//Setup

void setup() {
  pinMode(bot_cicla_pin,INPUT); //botao de ciclo pra input
  pinMode(ciclo_pin,OUTPUT); //rele pra output
  pinMode(liga_pin,INPUT); //liga/desliga pra input
  pinMode(led_liga_pin,OUTPUT);//led do lig/des pra output
  
  analogWrite(ciclo_pin,LOW); //startup rele off
  digitalWrite(led_liga_pin,LOW); //led do lig/des desligado

  lcd.init();        //Inicia o LCD
}
void loop() {
 bot_liga();
}


//Botao de adicionar numero de unidade
void bot_add_num_func(){
 int estado = digitalRead(bot_add_num);
 if (estado == HIGH && (millis()- tempo_bot_add_num)>100){
       if(num_ciclo < 99){
        num_ciclo += 1;
       }
       display_atualiza();
       delay(1000);
      }
}

//Botao de remover numero de unidade
void bot_rem_num_func(){
 int estado = digitalRead(bot_rem_num);
 if (estado == HIGH && (millis()- tempo_bot_rem_num)>100){
       if(num_ciclo > 1){
        num_ciclo -= 1;
       }
       display_atualiza();
       delay(1000);
      }
}

//Botao de adicionar numero de dezenas
void bot_add_dez_func(){
 int estado = digitalRead(bot_add_dez);
 if (estado == HIGH && (millis()- tempo_bot_add_dez)>100){
       if(num_dez < 9){
        num_dez += 1;
       }
       display_atualiza();
       delay(1000);
      }
}

//Botao de remover numero de dezenas
void bot_rem_dez_func(){
 int estado_rem = digitalRead(bot_rem_dez);
 if (estado_rem == HIGH && (millis()- tempo_bot_rem_dez)>100){
       if(num_dez > 0){
        num_dez -= 1;
       }
       display_atualiza();
       delay(1000);
      }
}

//Botao de adicionar numero de frequencia
void bot_add_freq_func(){
 int estado = digitalRead(bot_add_freq);
 if (estado == HIGH && (millis()- tempo_bot_add_freq)>100){
       if(frequencia < 15){
        frequencia += 1;
       }
       display_atualiza();
       delay(1000);
      }
}

//Botao de remover numero de frequencia
void bot_rem_freq_func(){
 int estado = digitalRead(bot_rem_freq);
 if (estado == HIGH && (millis()- tempo_bot_rem_freq)>100){
       if(frequencia > 1){
        frequencia -= 1;
       }
       display_atualiza();
       delay(1000);
      }
}


// Verifica estado do botao liga e desliga
void bot_liga(){
  int estado_lig = digitalRead(liga_pin);
  if (estado_lig == HIGH && (millis()- tempo_bot_liga)>500){
       liga_desliga = !liga_desliga;
       tempo_bot_liga = millis();
      }
  if (liga_desliga == HIGH){
    digitalWrite(led_liga_pin,HIGH);
    bot_cicla();
    bot_add_num_func();
    bot_rem_num_func();
    bot_add_dez_func();
    bot_rem_dez_func();
    bot_add_freq_func();
    bot_rem_freq_func();
    if ( ligado == HIGH){
      display_liga();
      ligado = LOW;
    }
    
  }   
  else if (liga_desliga == LOW){
    digitalWrite(led_liga_pin,LOW);
    display_desliga();
    ligado = HIGH;
  }
}

//Display liga e desliga 
void display_liga(){
  lcd.backlight();            // Ligando o BackLight do LCD
  lcd.clear();                // limpa a tela
  lcd.print("Maquina Ciclica");
  lcd.setCursor(0,1);
  lcd.print("Prot. Dentarias");
  delay(3000);
  lcd.clear();                
  lcd.print("Tcc Realizado:");
  lcd.setCursor(0,1);
  lcd.print("Rogers e Felipe");
  delay(3000);
  lcd.clear();                
  lcd.print("Orientacao:");
  lcd.setCursor(0,1);
  lcd.print("Prof. Michele");
  delay(3000);
  display_atualiza();
  }

void display_desliga(){
  lcd.clear();               
  lcd.print("Tchau!"); // Exibindo no Lcd Tchau!
  delay(2000);
  lcd.clear();
  lcd.noBacklight(); // Desliga o BackLight do LCD
  }

//Atualiza Tela 
void display_atualiza(){
  lcd.clear();                
  lcd.print("Ciclos:"); 
  lcd.setCursor(8,0);
  lcd.print(num_ciclo);
  lcd.setCursor(10,0);
  lcd.print("x 10^");
  lcd.setCursor(15,0);
  lcd.print(num_dez);
  lcd.setCursor(0,1); 
  lcd.print("Frequencia:");
  lcd.setCursor(12,1);
  lcd.print(frequencia);
  lcd.setCursor(14,1);
  lcd.print("Hz");
  }


// Verifica estado do botão de ciclo
void bot_cicla(){
 int estado = digitalRead(bot_cicla_pin);
 if (estado == HIGH && (millis()- tempo_bot_cicla)>100){
       ciclo();
      }
}



// ciclo completo
void ciclo() {
  int freq_real = frequencia*02;  // normalização pro programa
  int inc = 1000/frequencia;      //incremento 
  int pulso = inc;                //tempo entre pulsos
  int ciclos  = num_ciclo*pow(10,num_dez)*inc;    // tempo total dos ciclos em ms 
  for(inc; inc<=ciclos; inc += pulso){
    analogWrite(ciclo_pin,255); //255 no analogico é on
    delay(pulso/2);
    analogWrite(ciclo_pin,0); //255 no analogico é on
    delay(pulso-pulso/2);
     }
  tempo_bot_cicla = millis();
}
