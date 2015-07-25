int homeX = 514;
int homeY = 503;

int xPin = A1;
int yPin = A0;
int buttonPin = 2;

int xPosition = 0;
int xPos = 0;
int yPosition = 0;
int yPos = 0;
int buttonState = 0;
int btnSt = 0;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
  
  // For versions prior to Arduino 1.0.1
  // pinMode(buttonPin, INPUT);
  // digitalWrite(buttonPin, HIGH);
  
}

void loop() {
  //rawRead();
  fourPosStick();
}

void rawRead() {
  xPosition = getX();
  yPosition = getY();
  buttonState = getB();
  
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState);

  delay(10); // add some delay between reads
}

void fourPosStick() {
  if (getX() >= (homeX - 100) && getX() <= (homeX + 100)) {
    switch (getY()) {
      case 1023:
        Serial.println("N");
        break;
      case 0:
        Serial.println("S");
        break;
    }
  }
  if (getY() >= (homeY - 100) && getY() <= (homeY + 100)) {
    switch (getX()) {
      case 1023:
        Serial.println("E");
        break;
      case 0:
        Serial.println("W");
        break;
    }
  }
  if (getX() >= (homeX - 100) && getX() <= (homeX + 100) && getY() >= (homeY - 100) && getY() <= (homeY + 100)) {
    //Serial.println("C");
  }
  if (getB()) {
    Serial.println("B");
  }
  delay(10); // add some delay between reads
}

int getX() {
  xPos = analogRead(xPin);
  return xPos;
}

int getY() {
  yPos = analogRead(yPin);
  return yPos;
}

int getB() {
  btnSt = !digitalRead(buttonPin);
  return btnSt;
}
