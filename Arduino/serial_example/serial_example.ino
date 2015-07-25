char serialIn = 0;
boolean onOff = true;
int statusLed = 3;
int toggleButton = 2;
int newLine = 4;
int clsLn = 0;
int clsPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Starting Connection...");
  Serial.println("Welcome to Mockinjay v1.2");
  Serial.println("Button 1 is On / Off | Button 2 is Newline | Button 3 is Clear Screen");
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);
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
    
    if ((digitalRead(toggleButton)) == HIGH){
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
  if (digitalRead(toggleButton) == HIGH){
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
  clsLn = 0;
  while (clsLn <= 50 ){
    clsLn++;
    Serial.println("");
  }
}
