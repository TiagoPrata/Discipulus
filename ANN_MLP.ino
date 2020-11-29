void Treinar() {
  TreinaRede3();
  TreinaRede6();
}
  
void TreinaRede3() {  
  
  RGBled(0, 126, 129);
 //*****************************************************************Inicio Rede 3************************************************************
  EM_dif = EM_atual - EM_anterior;
  while (abs(EM_dif) > e) {
    EM_anterior = EM_atual;
    for (int k = 0; k < qtdAmostras; k++) {
      //=============Inicio do Forward=====================
      for (int i = 0; i < qtdCamadas; i++) {
        for (int j = 0; j < Topologia[i]; j++) {
          if (i == 0) {
            for (int entrada = 1; entrada <= qtdEntradas; entrada++) {
              Camada[i].Cell[j].Input[entrada] = AmostrasSensores[k][entrada-1];
            }
            Camada[i].Cell[j].calc();
          } else {
            for (int entrada = 1; entrada <= Topologia[i-1]; entrada++) {
              Camada[i].Cell[j].Input[entrada] = Camada[i-1].Cell[entrada-1].Output;
            }
            Camada[i].Cell[j].calc();
          }
        }
      }
      //===========Fim do Forward============================
      
      //===========Inicio do Backward========================
      for (int i = qtdCamadas-1; i >= 0; i--) {
        for (int j = 0; j < Topologia[i]; j++) {
          //=====Cálculo do Delta========
          if (i == qtdCamadas - 1) { //se i = ultima camada
            Camada[i].Cell[j].Delta = (Target_M1[k] - Camada[i].Cell[j].Output) * Camada[i].Cell[j].derived();
          } else {
            double SomaDoDelta = 0.0;
            for (int j2 = 0; j2 < Topologia[i+1]; j2++) {
              SomaDoDelta = Camada[i+1].Cell[j2].Delta * Camada[i+1].Cell[j2].Weight[j];
            }
            Camada[i].Cell[j].Delta = SomaDoDelta;
          }
          
          //======Seta novo peso===============
          for (int entrada = 0; entrada <= Camada[i].Cell[j].qtyInputs; entrada++) {
            Camada[i].Cell[j].Weight[entrada] = Camada[i].Cell[j].Weight[entrada] + n * Camada[i].Cell[j].Delta * Camada[i].Cell[j].Input[entrada];
          }
          //=====Fim do ajuste do peso======
        }
      }
      //========Fim do backward===============
    }
    for (int k = 0; k < qtdAmostras; k++) {
      //=============Inicio do Forward=====================
      for (int i = 0; i < qtdCamadas; i++) {
        for (int j = 0; j < Topologia[i]; j++) {
          if (i == 0) {
            for (int entrada = 1; entrada <= qtdEntradas; entrada++) {
              Camada[i].Cell[j].Input[entrada] = AmostrasSensores[k][entrada-1];
            }
            Camada[i].Cell[j].calc();
          } else {
            for (int entrada = 1; entrada <= Topologia[i-1]; entrada++) {
              Camada[i].Cell[j].Input[entrada] = Camada[i-1].Cell[entrada-1].Output;
            }
            Camada[i].Cell[j].calc();
          }
        }
      }
      //===========Fim do Forward============================
      
      Erro[k] = pow((Target_M1[k] - Camada[1].Cell[0].Output),2);
      Erro[k] = Erro[k]/2.0;
    }
    EM = 0;
    for (int k = 0; k < qtdAmostras; k++) {
      EM = EM + Erro[k];
    }
    EM = EM/qtdAmostras;
    EM_atual = EM;
    epoca = epoca + 1;
    Serial.print("Epoca: ");
    Serial.println(epoca);
    Serial.print("Erro: ");
    Serial.println(EM_dif, 15);
    
    EM_dif = EM_atual - EM_anterior;
  }
  Serial.println("\\o/");
  Serial.println(" ");
  //******************************************************************Fim Rede 3****************************************************************
  for (int j = 0; j < qtdNeuroniosCamada1; j++) {
    for (int i = 0; i <= qtdEntradas; i++) {
      PesoCamada1[0][j][i] = Camada[0].Cell[j].Weight[i];
    }
  }
  for (int j = 0; j < qtdNeuroniosCamada2; j++) {
    for (int i = 0; i <= qtdNeuroniosCamada1; i++) {
      PesoCamada2[0][j][i] = Camada[1].Cell[j].Weight[i];
    }
  }
  //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* 
}
 
void TreinaRede6() {  
  
  resetWeights();
  epoca = 0;
  EM_atual = 0.0;
  EM_anterior = 0.5;
  EM = 0;
  EM_dif = 0;
  RGBled(0, 235, 42);
 //*****************************************************************Inicio Rede 6************************************************************
  EM_dif = EM_atual - EM_anterior;
  while (abs(EM_dif) > e) {
    ledPulseOn(Led_BLUE, 1);
    EM_anterior = EM_atual;
    for (int k = 0; k < qtdAmostras; k++) {
      //=============Inicio do Forward=====================
      for (int i = 0; i < qtdCamadas; i++) {
        for (int j = 0; j < Topologia[i]; j++) {
          if (i == 0) {
            for (int entrada = 1; entrada <= qtdEntradas; entrada++) {
              Camada[i].Cell[j].Input[entrada] = AmostrasSensores[k][entrada-1];
            }
            Camada[i].Cell[j].calc();
          } else {
            for (int entrada = 1; entrada <= Topologia[i-1]; entrada++) {
              Camada[i].Cell[j].Input[entrada] = Camada[i-1].Cell[entrada-1].Output;
            }
            Camada[i].Cell[j].calc();
          }
        }
      }
      //===========Fim do Forward============================
      
      //===========Inicio do Backward========================
      for (int i = qtdCamadas-1; i >= 0; i--) {
        for (int j = 0; j < Topologia[i]; j++) {
          //=====Cálculo do Delta========
          if (i == qtdCamadas - 1) { //se i = ultima camada
            Camada[i].Cell[j].Delta = (Target_M2[k] - Camada[i].Cell[j].Output) * Camada[i].Cell[j].derived();
          } else {
            double SomaDoDelta = 0.0;
            for (int j2 = 0; j2 < Topologia[i+1]; j2++) {
              SomaDoDelta = Camada[i+1].Cell[j2].Delta * Camada[i+1].Cell[j2].Weight[j];
            }
            Camada[i].Cell[j].Delta = SomaDoDelta;
          }
          
          //======Seta novo peso===============
          for (int entrada = 0; entrada <= Camada[i].Cell[j].qtyInputs; entrada++) {
            Camada[i].Cell[j].Weight[entrada] = Camada[i].Cell[j].Weight[entrada] + n * Camada[i].Cell[j].Delta * Camada[i].Cell[j].Input[entrada];
          }
          //=====Fim do ajuste do peso======
        }
      }
      //========Fim do backward===============
    }
    for (int k = 0; k < qtdAmostras; k++) {
      //=============Inicio do Forward=====================
      for (int i = 0; i < qtdCamadas; i++) {
        for (int j = 0; j < Topologia[i]; j++) {
          if (i == 0) {
            for (int entrada = 1; entrada <= qtdEntradas; entrada++) {
              Camada[i].Cell[j].Input[entrada] = AmostrasSensores[k][entrada-1];
            }
            Camada[i].Cell[j].calc();
          } else {
            for (int entrada = 1; entrada <= Topologia[i-1]; entrada++) {
              Camada[i].Cell[j].Input[entrada] = Camada[i-1].Cell[entrada-1].Output;
            }
            Camada[i].Cell[j].calc();
          }
        }
      }
      //===========Fim do Forward============================
      
      Erro[k] = pow((Target_M2[k] - Camada[1].Cell[0].Output),2);
      Erro[k] = Erro[k]/2.0;
    }
    EM = 0;
    for (int k = 0; k < qtdAmostras; k++) {
      EM = EM + Erro[k];
    }
    EM = EM/qtdAmostras;
    EM_atual = EM;
    epoca = epoca + 1;
    Serial.print("Epoca: ");
    Serial.println(epoca);
    Serial.print("Erro: ");
    Serial.println(EM_dif, 15);
    
    EM_dif = EM_atual - EM_anterior;
    ledPulseOff(Led_BLUE, 1);
  }
  Serial.println("\\o/");
  Serial.println(" ");
  //******************************************************************Fim Rede 6****************************************************************
  for (int j = 0; j < qtdNeuroniosCamada1; j++) {
    for (int i = 0; i <= qtdEntradas; i++) {
      PesoCamada1[1][j][i] = Camada[0].Cell[j].Weight[i];
    }
  }
  for (int j = 0; j < qtdNeuroniosCamada2; j++) {
    for (int i = 0; i <= qtdNeuroniosCamada1; i++) {
      PesoCamada2[1][j][i] = Camada[1].Cell[j].Weight[i];
    }
  }
  //*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Automatico() {
  int temp;
  Layer Camada[2];
  Camada[0].begin(qtdNeuroniosCamada1, qtdEntradas);
  Camada[1].begin(qtdNeuroniosCamada2, qtdNeuroniosCamada1, "linear"); 
  
  while(true) {
    ledPulseOn(Led_GREEN, 1);
    readUltraSensors();
    
    
    //*************************************************************Inicio Rede 3******************************************************************
    for (int j = 0; j < qtdNeuroniosCamada1; j++) {
      for (int i = 0; i <= qtdEntradas; i++) {
        Camada[0].Cell[j].Weight[i] = PesoCamada1[0][j][i];
      }
    }
    for (int j = 0; j < qtdNeuroniosCamada2; j++) {
      for (int i = 0; i <= qtdNeuroniosCamada1; i++) {
        Camada[1].Cell[j].Weight[i] = PesoCamada2[0][j][i];
      }
    }
    //=============Inicio do Forward=====================
    for (int i = 0; i < qtdCamadas; i++) {
      for (int j = 0; j < Topologia[i]; j++) {
        if (i == 0) {
          for (int entrada = 1; entrada <= qtdEntradas; entrada++) {
            Camada[i].Cell[j].Input[entrada] = sensorValue[entrada-1];
          }
          Camada[i].Cell[j].calc();
        } else {
          for (int entrada = 1; entrada <= Topologia[i-1]; entrada++) {
            Camada[i].Cell[j].Input[entrada] = Camada[i-1].Cell[entrada-1].Output;
          }
          Camada[i].Cell[j].calc();
          
          temp = Camada[i].Cell[j].Output * 10000;
          if (temp >= 6666) {
            forwardM1 = true;
            backwardM1 = false;
            M1 = map(temp, 6666, 9999, 0, 255);
          } else if (temp <= 3333) {
            forwardM1 = false;
            backwardM1 = true;
            M1 = map(temp, 0, 3333, 0, 255);
          } else {
            forwardM1 = false;
            backwardM1 = false;
            M1 = 0;
          }
          
        }
      }
    }
    //===========Fim do Forward============================
    //*****************************************************************************************Fim Rede 3*********************************************************
    
    
    //*************************************************************Inicio Rede 6******************************************************************
    for (int j = 0; j < qtdNeuroniosCamada1; j++) {
      for (int i = 0; i <= qtdEntradas; i++) {
        Camada[0].Cell[j].Weight[i] = PesoCamada1[1][j][i];
      }
    }
    for (int j = 0; j < qtdNeuroniosCamada2; j++) {
      for (int i = 0; i <= qtdNeuroniosCamada1; i++) {
        Camada[1].Cell[j].Weight[i] = PesoCamada2[1][j][i];
      }
    }
    //=============Inicio do Forward=====================
    for (int i = 0; i < qtdCamadas; i++) {
      for (int j = 0; j < Topologia[i]; j++) {
        if (i == 0) {
          for (int entrada = 1; entrada <= qtdEntradas; entrada++) {
            Camada[i].Cell[j].Input[entrada] = sensorValue[entrada-1];
          }
          Camada[i].Cell[j].calc();
        } else {
          for (int entrada = 1; entrada <= Topologia[i-1]; entrada++) {
            Camada[i].Cell[j].Input[entrada] = Camada[i-1].Cell[entrada-1].Output;
          }
          Camada[i].Cell[j].calc();
          
          temp = Camada[i].Cell[j].Output * 10000;
          if (temp >= 6666) {
            forwardM2 = true;
            backwardM2 = false;
            M2 = map(temp, 6666, 9999, 0, 255);
          } else if (temp <= 3333) {
            forwardM2 = false;
            backwardM2 = true;
            M2 = map(temp, 0, 3333, 0, 255);
          } else {
            forwardM2 = false;
            backwardM2 = false;
            M2 = 0;
          }
        }
      }
    }
    //===========Fim do Forward============================
    //*****************************************************************************************Fim Rede 6*********************************************************
    RGBled(0,0,0);
    driving();
  }
}

void resetWeights() {
  double _rand;
  
  for (int i = 0; i < qtdNeuroniosCamada1; i++) {
    for (int j = 0; j <= qtdEntradas; j++) {
      _rand = random(1000000)/1000000.0;
      Camada[0].Cell[i].Weight[j] = _rand;
    }
  }
  
  for (int i = 0; i < qtdNeuroniosCamada2; i++) {
    for (int j = 0; j <= qtdNeuroniosCamada1; j++) {
      _rand = random(1000000)/(float)1000000.0;
      Camada[1].Cell[i].Weight[j] = _rand;
    }
    ledPulseOff(Led_GREEN, 1);
  }
}
