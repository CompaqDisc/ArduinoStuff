char serialIn = 0;
int clsProg = 0;
boolean onOff = true;
int statusLed = 2;
int onOffButton = 3;
int newLine = 4;
int clsPin = 5;
int powPin = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(powPin, OUTPUT);
  digitalWrite(powPin, HIGH);
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);
  Serial.begin(9600);
  Serial.println("Starting Connection...");
  Serial.println("Welcome to Mockinjay v1.2");
  Serial.println("Button 1 is On / Off | Button 2 is Newline | Button 3 is Clear Screen");
}

void loop() {
  // put your main code here, to run repeatedly:
  serialIn = Serial.read();
  if (serialIn == -1){
    Serial.print("");
  } else {
    Serial.print(serialIn);
  }
  
  if (digitalRead(newLine) == HIGH) {
    Serial.println("");
    digitalWrite(statusLed, LOW);
    delay(100);
    digitalWrite(statusLed, HIGH);
    delay(250);
  }
  
  if (digitalRead(clsPin) == HIGH) {
    cls();
    digitalWrite(statusLed, LOW);
    delay(100);
    digitalWrite(statusLed, HIGH);
    delay(100);
    digitalWrite(statusLed, LOW);
    delay(100);
    digitalWrite(statusLed, HIGH);
    delay(250);
  }
    
    if ((digitalRead(onOffButton)) == HIGH){
      onOff = false;
    }
      
    if (onOff == false){
      digitalWrite(statusLed, LOW);
      end();
    }
}

void end(){
  delay(250);
  Serial.println("");
  Serial.println("");
  Serial.println("Warning: Serial Connection Terminated");
  Serial.end();
  if (digitalRead(onOffButton) == HIGH){
      onOff = true;
  }
  
  if (onOff == true){
    begin();
  } else {
    end();
  }
}

void begin(){
  digitalWrite(statusLed, HIGH);
  Serial.begin(9600);
  Serial.println("");
  Serial.println("");
  Serial.println("Note: Serial Connection Restored");
  delay(250);
}

void cls(){
  clsProg = 0;
  while (clsProg <= 50 ){
    clsProg++;
    Serial.println("");
  }
}
