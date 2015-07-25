#define wait 500
#define bd1 9600
#define bd2 9600
String ssid = "Fairplay Network";
String pass = "CabinFever1";
String request = "";

void setup() {
  Serial.begin(bd1);
  Serial1.begin(bd2);
  delay(wait);
  Serial1.println("AT");
  delay(wait);
  Serial1.println("AT+CWMODE=3");
  delay(wait);
  Serial1.println("AT+CWLAP");
  delay(1000);
  Serial1.println("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"");
  delay(2000);
  Serial1.println("AT+CIFSR");
  delay(wait);
  Serial1.println("AT+CIPMUX=1");
  delay(wait);
  Serial1.println("AT+CIPSERVER=1,80");
  delay(wait);
  Serial1.println("AT+CIPSTO=20");
  delay(wait);
  Serial1.println("AT");
  delay(wait);
}

void loop() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    char inByte = Serial1.read();
    Serial.write(inByte);
    request += inByte;
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inByte = Serial.read();
    Serial1.write(inByte);
  }
  
  // determine if a request has been made
  if (request != "") {
    if (request.indexOf("GET / HTTP/1.1") >= 0) {
      request = "";
      sendAll();
    }
  }
}

void sendAll() {
  delay(wait);
  Serial1.println("AT+CIPSEND=0,17");
  delay(wait);
  Serial1.println("HTTP/1.1 200 OK");
  delay(wait);
  Serial1.println("AT+CIPSEND=0,42");
  delay(wait);
  Serial1.println("Content-Type: text/html; charset=UTF-8");
  delay(wait);
  Serial1.println("");
  delay(wait);
  Serial1.println("AT+CIPSEND=0,32");
  delay(wait);
  Serial1.println("<h1>Successful Connection</h1>");
  delay(wait);
  Serial1.println("AT+CIPCLOSE=0");
  delay(wait);
  Serial1.println("AT");
  delay(wait);
}
