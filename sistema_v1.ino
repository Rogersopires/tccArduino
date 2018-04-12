#include <Wire.h> // Biblioteca para se comunicar com dispositivos I2C ( display)
#include <LiquidCrystal_I2C.h> // biblioteca do display
#include <String.h>

// variaveis de entrada no arduino 

int bot_liga = 7; // entrada do bot�o liga e desliga
int bot_acio = 6; // entrada do bot�o de ligar os ciclos
int bot_emer = 5; // entrada do bot�o de emergencia
int bot_decd = 4;  // entrada do bot�o de diminuir decimais nos ciclos
int bot_deca = 3; // entrada do bot�o de aumentar decimais nos ciclos
int bot_numd = 2; // entrada do bot�o de diminuir o numero nos ciclos
int bot_numa = 1; // entrada do bot�o de aumentar o numero nos ciclos

// variaveis do programa 

int num_cicl = 0;   //numero de ciclos
int dec_disp = 10;  //casa decimal do ciclo
int num_disp = 1;   //numero do ciclo

// estado inicial dos bot�es 

boolean lig_deslN = LOW;  //seleciona o estado do programa (liga e desliga o painel e todas as fun��es do programa)
boolean emergencN = LOW;    //estado de emergencia (ligado desliga o ciclos e para o programa no estado q ele esta)
boolean bot_decdN = LOW;  //estado inicial do bot�o de diminuir decimais
boolean bot_decaN = LOW;  //estado inicial do bot�o de aumentar decimais
boolean bot_numdN = LOW;  //estado inicial do bot�o de diminuir o numero
boolean bot_numaN = LOW;  //estado inicial do bot�o de aumentar o numero

// verificadores da fun��o bot_delay

boolean emergencF = LOW;  //verifica pra fun��o o estado de emergencia
boolean lig_deslF = LOW;  //verifica pra fun��o o estado do programa
boolean bot_decdF = LOW;  //verifica pra fun��o o estado do bot�o de diminuir decimais
boolean bot_decaF = LOW;  //verifica pra fun��o o estado do bot�o de aumentar decimais
boolean bot_numdF = LOW;  //verifica pra fun��o o estado do bot�o de diminuir o numero
boolean bot_numaF = LOW;  //verifica pra fun��o o estado do bot�o de aumentar o numero 


//setup do display 
int lig_disp = 0;   //liga e desliga o display
int buf_disp = 0;   //muda o valor do display
LiquidCrystal_I2C lcd(0x27,16,2); //cria um lcd de 16x2 na memoria 0x27(programa come�a sempre nessa memoria)

void setup(){

// seta no arduino as entradas de informa��es

  pinMode(bot_liga,INPUT);  //seta no arduino entrada do bot�o liga e desliga como input(entra info)
  pinMode(bot_acio,INPUT);  //seta no arduino entrada do bot�o de acionar os ciclos como input(entra info)
  pinMode(bot_emer,INPUT);  //seta no arduino entrada do bot�o de emergencia como input(entra info)
  pinMode(bot_decd,INPUT);  //seta no arduino entrada do bot�o de diminuir a dezena como input(entra info)
  pinMode(bot_deca,INPUT);  //seta no arduino entrada do bot�o de aumentar a dezena como input(entra info)
  pinMode(bot_numd,INPUT);  //seta no arduino entrada do bot�o de diminuir o numero como input(entra info)
  pinMode(bot_numa,INPUT);  //seta no arduino entrada do bot�o de aumentar o numero como input(entra info)

}

// fun��o para evitar o delay do bot�o

boolean bot_delay(boolean ultimo,int botao){
  boolean agora = digitalRead(botao);
  if(ultimo != agora){
    delay(5);
    agora = digitalRead(botao);
  }
  return agora;
}


void loop(){
  // set ligado e desligado
  lig_deslN = bot_delay(lig_deslF,bot_liga);

  //setup para ligar
  
  if(lig_deslF == LOW && lig_deslN == HIGH){

    // liga o display

    if(lig_disp == 1){
      lcd.init();       //inicializa o LCD
      lcd.backlight();  //Liga a luz do LCD
      lcd.print(num_cicl);
      lig_disp = 0;
    }//fechamento do liga o display

    //bot�o de diminuir dezenas

    bot_decdN = bot_delay(bot_decdF,bot_decd);
    if (bot_decdF == LOW && bot_decdN == HIGH)
      {
      dec_disp = dec_disp/10;
      if(dec_disp <=10){
        dec_disp = 10;
        }
      buf_disp = 0; 
      }
    bot_decdF = bot_decdN;

    //bot�o de aumentar dezenas

    bot_decaN = bot_delay(bot_decaF,bot_deca);
    if (bot_decaF == LOW && bot_decaN == HIGH)
      {
      dec_disp = dec_disp*10;
      buf_disp = 0; 
      }
    bot_decaF = bot_decaN;
    
    //bot�o de diminuir numero

    bot_numdN = bot_delay(bot_numdF,bot_numd);
    if (bot_numdF == LOW && bot_numdN == HIGH)
      {
      num_disp = num_disp-1;
      if(num_disp <=1){
        num_disp = 1;
        }
      buf_disp = 1; 
      }
    bot_numdF = bot_numdN;
    
    //bot�o de aumentar numero
    
    bot_numaN = bot_delay(bot_numaF,bot_numa);
    if (bot_numaF == LOW && bot_numaN == HIGH)
      {
      num_disp = num_disp+1;
      buf_disp = 1; 
      }
    bot_numaF = bot_numaN;
    
    //mostrar a tela
    if(buf_disp == 1){
      num_cicl = num_disp*dec_disp;
      lcd.clear();
      lcd.print(num_cicl);
      buf_disp = 0;
    }
    
    lig_deslF = lig_deslN; // manter ligado quando ligado
    
  }// fechamento do setup para ligar

  //setup para desligar

  else if(lig_deslF == LOW && lig_deslN == LOW){
    
    // desliga o display

    if(lig_disp == 0){
      lcd.noBacklight();  //desliga a luz do LCD
      lcd.off(); //desliga o LCD
      lig_disp = 1;
    }// fechamento do desliga o display
  }// fechamento do setup para desligar
  
  

}// fechamento do loop
