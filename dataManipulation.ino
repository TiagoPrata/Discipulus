void recData() {
  for (int i = 0; i < 8; i++) {
    AmostrasSensores[amostraAtual][i];
  }
  
  if (forwardM1 && !backwardM1) {
    Target_M1[amostraAtual] = (map(M1, 0, 255, 6666, 9999)/10000.0);
  } else if (!forwardM1 && backwardM1) {
    Target_M1[amostraAtual] = (map(M1, 0, 255, 0, 3333)/10000.0);
  } else {
    Target_M1[amostraAtual] = 0.5000;
  }
  
  if (forwardM2 && !backwardM2) {
    Target_M2[amostraAtual] = (map(M2, 0, 255, 6666, 9999)/10000.0);
  } else if (!forwardM2 && backwardM2) {
    Target_M2[amostraAtual] = (map(M2, 0, 255, 0, 3333)/10000.0);
  } else {
    Target_M2[amostraAtual] = 0.5000;
  }
  
  amostraAtual++; 
  Serial.print("Amostra ");
  Serial.println(amostraAtual-1);
}
