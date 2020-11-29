//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void driving() {

  if (buttonCheck(_L1)) {
    if (ControlArray[2] > 135) {
      forwardM1 = false;
      backwardM1 = true;
      M1 = map(ControlArray[2], 136, 255, 0, 255);
    } else if (ControlArray[2] < 120) {
      forwardM1 = true;
      backwardM1 = false;
      M1 = map(ControlArray[2], 119, 0, 0, 255);
    } else {
      forwardM1 = false;
      backwardM1 = false;
      M1 = 0;
    }
  }
  
  //___________________________________________________
  if (buttonCheck(_R1)) {
    if (ControlArray[3] > 135) {
      forwardM2 = false;
      backwardM2 = true;
      M2 = map(ControlArray[3], 136, 255, 0, 255);
    } else if (ControlArray[3] < 120) {
      forwardM2 = true;
      backwardM2 = false;
      M2 = map(ControlArray[3], 119, 0, 0, 255);
    } else {
      forwardM2 = false;
      backwardM2 = false;
      M2 = 0;
    }
  }
  
  //___________________________________________________
//  if (!buttonCheck(_L1) && L1release) {
//    M1 = 0;
//    forwardM1 = false;
//    backwardM1 = false;
//  }
//  
//  //___________________________________________________
//  if (!buttonCheck(_R1) && R1release) {
//    M2 = 0;
//    forwardM2 = false;
//    backwardM2 = false;
//  }
  
  //___________________________________________________
  if (buttonCheck(_PINK)) {
    backwardM1 = false;
    backwardM2 = false;
    forwardM1 = false;
    forwardM2 = false;
    M1 = 0;
    M2 = 0;
  }
  
  //_____________________________________________________
  if (forwardM1) {
    digitalWrite(EN1_M1, HIGH);
    digitalWrite(EN2_M1, LOW);
  } else if (backwardM1) {
    digitalWrite(EN1_M1, LOW);
    digitalWrite(EN2_M1, HIGH);
  } else {
    digitalWrite(EN1_M1, LOW);
    digitalWrite(EN2_M1, LOW);
  }
  
  //________________________________________________________
  if (forwardM2) {
    digitalWrite(EN1_M2, LOW);
    digitalWrite(EN2_M2, HIGH);
  } else if (backwardM2) {
    digitalWrite(EN1_M2, HIGH);
    digitalWrite(EN2_M2, LOW);
  } else {
    digitalWrite(EN1_M2, LOW);
    digitalWrite(EN2_M2, LOW);
  }
  
  PWMM1 = map(M1, 0, 255, 20, 40);
  PWMM2 = map(M2, 0, 255, 20, 40);
  //____________________________________________________________
  analogWrite(PWM_M1, PWMM1);
  analogWrite(PWM_M2, PWMM2);
//  analogWrite(PWM_M1, map(M1 + offsetM1, 0, offsetM1 + 255, 30, 100));
//  analogWrite(PWM_M2, map(M2 + offsetM2, 0, offsetM2 + 255, 30, 100));
  
//  Serial.print("PWM1 ");
//  Serial.println(map(M1 + offsetM1, 0, offsetM1 + 255, 0, 255));
//  Serial.print("PWM2 ");
//  Serial.println(map(M2 + offsetM2, 0, offsetM2 + 255, 0, 255));
//  Serial.print("M1 ");
//  Serial.println(M1);
//  Serial.print("M2 ");
//  Serial.println(M2);
//  Serial.print("offsetM1 ");
//  Serial.println(offsetM1);
//  Serial.print("offsetM2 ");
//  Serial.println(offsetM2);
  
  delay(incrementalDelay);
}
