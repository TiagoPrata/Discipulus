//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReceiveEvent(int numBytes) {
  byte i = 0;
  if (numBytes == 2) {
    i = Wire.read();
    ControlArray[i] = Wire.read();
//    Serial.print("i");
//    Serial.print(" ");
//    Serial.println(i);
//    Serial.print("ControlArray");
//    Serial.print(" ");
//    Serial.println(ControlArray[i]);
    readACK = false;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
boolean buttonCheck(const byte &button) {
  byte Array;
  
  if (!readACK) {
    if ((&button == &_UP) || (&button == &_DOWN) || (&button == &_LEFT) || (&button == &_RIGHT) || (&button == &_GREEN) || (&button == &_RED) || (&button == &_BLUE) || (&button == &_PINK)) {
      Array = ControlArray[0];
    } else {
      Array = ControlArray[1];
    }
    
    if (((Array & button) == button)) {
      return true;
    } else {
      return false;
    }
    readACK = true;
  }
}

//void readControl() {
//  byte i = 0;
//  Wire.requestFrom(ControlWireAddress, ControlByteLenght);    // request 6 bytes from slave device #2
//
//  while(Wire.available())
//  { 
//    ControlArray[i] = Wire.read();
//    Serial.print("1 ");
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.println(ControlArray[i]);
//    i++;
//  }
//  Serial.println(" ");
//  
//  delay(100);
//  
//  i = 0;
//  Wire.requestFrom(ControlWireAddress, ControlByteLenght);    // request 6 bytes from slave device #2
//
//  while(Wire.available())
//  { 
//    ControlArray2[i] = Wire.read();
//    Serial.print("2 ");
//    Serial.print(i);
//    Serial.print(" ");
//    Serial.println(ControlArray2[i]);
//    i++;
//  }
//  Serial.println(" ");
//  
//  delay(100);
//}
