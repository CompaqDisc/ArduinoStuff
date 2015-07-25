char serialIn = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting Connection...");
  Serial.println("Welcome to Bare Mockinjay v1.0");
}

void loop() {
  // put your main code here, to run repeatedly:
  serialIn = Serial.read();
  if (serialIn == -1){
    Serial.print("");
  } else {
    Serial.print(serialIn);
  }
}
