/*======================================================
            Developed by Tiago Prata
            Nov, 2013
            tiagoprata@ymail.com
========================================================*/

#include <Wire.h>
#include <Neuronio.h>

//=============Control================
#define ControlByteLenght 6
#define ControlWireAddress 2

#define buttonClickDelay 170

//==========UltraSensor==============
#define Sensor1Echo 52
#define Sensor1Trig 53
#define Sensor2Echo 50
#define Sensor2Trig 51
#define Sensor3Echo 48
#define Sensor3Trig 49
#define Sensor4Echo 46
#define Sensor4Trig 47
#define Sensor5Echo 44
#define Sensor5Trig 45
#define Sensor6Echo 42
#define Sensor6Trig 43
#define Sensor7Echo 40
#define Sensor7Trig 41
#define Sensor8Echo 38
#define Sensor8Trig 39
#define Sensor9Echo 36
#define Sensor9Trig 37
#define Sensor10Echo 34
#define Sensor10Trig 35
long longSensorValue[8];
float sensorValue[8];

//===============LEDs================
#define Led_RED 8
#define Led_GND 9
#define Led_GREEN 10
#define Led_BLUE 11

//=============Motors================
#define PWM_M1 4
#define EN1_M1 15
#define EN2_M1 14
#define EN2_M2 5
#define EN1_M2 6
#define PWM_M2 7
#define incrementalStep 10
#define incrementalDelay 40
byte M1, M2 = 0;
byte PWMM1, PWMM2 = 0;
boolean forwardM1, forwardM2, backwardM1, backwardM2 = false;

//=============================================Control=================================
//Primeiro byte - ControlArray[0]                                                    //
const byte _UP = 1;                                                                  //
const byte _DOWN = 2;                                                                //
const byte _LEFT = 4;                                                                //
const byte _RIGHT = 8;                                                               //
const byte _GREEN = 16;                                                              //
const byte _RED = 32;                                                                //
const byte _BLUE = 64;                                                               //
const byte _PINK = 128;                                                              //
                                                                                     //
//Segundo byte - ControlArray[1]                                                     //
const byte _L1 = 1;                                                                  //
const byte _L2 = 2;                                                                  //
const byte _R1 = 4;                                                                  //
const byte _R2 = 8;                                                                  //
const byte _L3 = 16;                                                                 //
const byte _R3 = 32;                                                                 //
const byte _START = 64;                                                              //
const byte _SELECT = 128;                                                            //
                                                                                     //
byte ControlArray[6] = {0,0,0,0,0,0};                                                //
//ControlArray[0] - Setas direcionais e botoes principais                            //
//ControlArray[1] - Ls e Rs + Start e Select                                         //
//ControlArray[2] - Analogico LY                                                     //
//ControlArray[3] - Analogico RY                                                     //
//ControlArray[4] - Analogico LX                                                     //
//ControlArray[5] - Analogico RX                                                     //
boolean readACK;       //  !readACK = comando recebido, mas ainda nao executado      //
//=====================================================================================

//=====================Data===========================
#define qtdAmostras 600
#define qtdEntradas 8
#define qtdRedes 2
float AmostrasSensores[qtdAmostras][qtdEntradas];
float Target_M1[qtdAmostras];      //Rede 3
float Target_M2[qtdAmostras];      //Rede 6

//===================ANN===========================  
#define qtdCamadas 2
#define qtdNeuroniosCamada1 (2*qtdEntradas)+1    //Metodo de Kolmogorov
#define qtdNeuroniosCamada2 1
Layer Camada[2];
byte Topologia[qtdCamadas] = {qtdNeuroniosCamada1, qtdNeuroniosCamada2};
double Erro[qtdAmostras];
float n = 0.001;
double e = 0.0000001;
int epoca = 0;
double EM_atual = 0.0;
double EM_anterior = 0.5;
double EM = 0;
double EM_dif = 0; //EM_atual - EM_anterior

//================Pesos pos treinamento================
double PesoCamada1[qtdRedes][qtdNeuroniosCamada1][qtdEntradas];
double PesoCamada2[qtdRedes][qtdNeuroniosCamada2][qtdNeuroniosCamada1];

//===============General============================
byte screen = 1;
//screen 1 - Principal
//screen 2 - Dirigir sem gravar no SD
//screen 3 - Dirigir gravando no SD
//screen 4 - Rede Neural
unsigned int Clock = 0;
boolean recording = false;
int amostraAtual = 0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  Wire.begin(1);
  Serial.begin(9600);
  Wire.onReceive(ReceiveEvent);
  
  randomSeed(analogRead(0));
  
  Camada[0].begin(qtdNeuroniosCamada1, qtdEntradas);
  Camada[1].begin(qtdNeuroniosCamada2, qtdNeuroniosCamada1, "linear");
  
  //==============LEDs=================
  pinMode(Led_RED, OUTPUT);
  pinMode(Led_GREEN, OUTPUT);
  pinMode(Led_BLUE, OUTPUT);
  pinMode(Led_GND, OUTPUT);
  
  digitalWrite(Led_RED, LOW);
  digitalWrite(Led_GREEN, LOW);
  digitalWrite(Led_BLUE, LOW);
  digitalWrite(Led_GND, LOW);
  
  //=============Motors===================
  pinMode(PWM_M1, OUTPUT);
  pinMode(EN1_M1, OUTPUT);
  pinMode(EN2_M1, OUTPUT);
  pinMode(EN2_M2, OUTPUT);
  pinMode(EN1_M2, OUTPUT);
  pinMode(PWM_M2, OUTPUT);
  
  //==========UltraSensor==================
  pinMode(Sensor1Echo, INPUT); 
  pinMode(Sensor1Trig, OUTPUT);
  pinMode(Sensor2Echo, INPUT); 
  pinMode(Sensor2Trig, OUTPUT);
  pinMode(Sensor3Echo, INPUT); 
  pinMode(Sensor3Trig, OUTPUT);
  pinMode(Sensor4Echo, INPUT); 
  pinMode(Sensor4Trig, OUTPUT);
  pinMode(Sensor5Echo, INPUT); 
  pinMode(Sensor5Trig, OUTPUT);
  pinMode(Sensor6Echo, INPUT); 
  pinMode(Sensor6Trig, OUTPUT);
  pinMode(Sensor7Echo, INPUT); 
  pinMode(Sensor7Trig, OUTPUT);
  pinMode(Sensor8Echo, INPUT); 
  pinMode(Sensor8Trig, OUTPUT);
  pinMode(Sensor9Echo, INPUT); 
  pinMode(Sensor9Trig, OUTPUT);
  pinMode(Sensor10Echo, INPUT); 
  pinMode(Sensor10Trig, OUTPUT);
  
  delay(150);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop() {
  if (screen == 1) {
    principalScreen();
  } else if (screen == 2) {
    driveNoSD();
  } else if (screen == 3) {
    driveSD();
  } else if (screen == 4) {
    RNA();
  } else if (screen == 5) {
    Execucao();
  }
  
  Clock++;
  if (Clock > 60000) Clock = 0; 
}

//=========================Screens====================================
void Execucao() {
  Automatico();
  
  //changeScreen(_START, 2);
}

void RNA() {
  digitalWrite(EN1_M1, LOW);
  digitalWrite(EN2_M1, LOW);
  digitalWrite(EN1_M2, LOW);
  digitalWrite(EN2_M2, LOW);
  analogWrite(PWM_M1, 0);
  analogWrite(PWM_M2, 0);
  preTreino();
  Treinar();
  
  
  screen = 5;
  //changeScreen(_START, 4);
  //changeScreen(_SELECT, 3);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void driveSD() {
  RGBled(0, 0, 255);
  
  if (!recording) amostraAtual = 0;
  recording = true;
  
  readUltraSensors();
  recData();
  driving();
  
  if (amostraAtual == qtdAmostras) screen = 4;
  //changeScreen(_START, 4);
  changeScreen(_SELECT, 2);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void driveNoSD() {
  RGBled(0, 255, 0);
  
  driving();
  recording = false;
  
  if ((M1 == 0) && (M2 == 0)) {
    changeScreen(_START, 3);
    changeScreen(_SELECT, 1);
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void principalScreen() {
  RGBled(255, 0, 0);
  
  changeScreen(_START, 2);
}
//====================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void changeScreen(const byte &button, byte targetScreen) {
  if (buttonCheck(button)) {
    screen = targetScreen;
    delay(buttonClickDelay);
  }
}
