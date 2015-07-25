int VCC = 255;
int GND = 0;
int VCCPin = 14;
int GNDPin = 18;
int DATAPin = 16;

void setup() {
  Serial.begin(9600);
  pinMode(VCCPin, OUTPUT);
  pinMode(DATAPin, INPUT);
  pinMode(GNDPin, OUTPUT);
  analogWrite(VCCPin, VCC);
  analogWrite(GNDPin, GND);
}

void loop() {
  int value = analogRead(2);
  Serial.println(value);
  analogWrite(11, (value / 4) - 50);
  delay(1000);
}
