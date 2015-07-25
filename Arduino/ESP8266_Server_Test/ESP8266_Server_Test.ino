int WaitMS = 1000;
int SMWait = 1000;
String RET = "\r\n";
String ReqStr = "";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial1.begin(9600);
  while (!Serial1) {
    Serial.println("Waiting for WiFi Module connection..."); // wait for WiFi module to connect by serial.
  }
  Serial.println("Module connected.");
  while (!checkATResponse()) {
    Serial.println("Waiting on AT OK response..."); // wait for the WiFi module to report "OK" on "AT" command.
  }
  Serial.println("AT OK response recieved.");
  delay(200);
  Serial1.println("AT+CWJAP=\"HOME-E2E9\",\"Baxter22!\"");
  delay(200);
  Serial.println("AT+CIPMODE=1");
  delay(1000);
  
  BeginServer("80");
  
  Serial.print("\r\nThe terminal is yours.\r\n");
}

void loop() {
  BasicAT();
}

String sendData(String CMD, const int TO, boolean DEBUG)
{
    String RESP = "";
    
    Serial1.print(CMD); // send the command to the WiFi module.
    if (DEBUG) {
      Serial.println("Sent: \r\n\t" + CMD);
    }
    
    long int TIME = millis();
    
    while ((TIME + TO) > millis())
    {
      while (Serial1.available()) // read data until end of stream or timeout period.
      {
        char C = Serial1.read();
        RESP += C;
      }
    }
    
    if (DEBUG)
    {
      Serial.println("Timeout on command.");
      Serial.println("Got: \r\n\r\n" + RESP);
    }
    return RESP;
}

String sendHtml(String CMD, String CMDSize, const int TO, boolean DEBUG)
{
    String RESP = "";
    String ATS = "AT+CPISEND=0,";
    
    Serial1.print(ATS + CMDSize + "\r\n"); // send command header.
    delay(200);
    Serial1.print(CMD); // send command body.
    delay(200);
    if (DEBUG) {
      Serial.println("Sent: \r\n\t" + ATS + CMDSize + "\r\n" + CMD);
    }
    
    long int TIME = millis();
    
    while ((TIME + TO) > millis())
    {
      while (Serial1.available()) // read data until end of stream or timeout period.
      {
        char C = Serial1.read();
        RESP += C;
      }
    }
    
    if (DEBUG)
    {
      Serial.println("Timeout on command.");
      Serial.println("Got: \r\n\r\n" + RESP);
    }
    return RESP;
}

boolean checkATResponse() {
  String RESP = sendData("AT\r\n", 100, true);
  if (RESP != "") {
    if (RESP.indexOf("OK") >= 0) {
      return true;
    } else {
      return false;
    }
  }
}

void RelayAT_CMDS(int TO, boolean DBG) {
  String CMD = "";
  Serial.print("\r\nEnd of program, you can now enter your own AT commands for the WiFi module.");
  Serial.print("\r\n\r\nArduino@ATMega2560 ~/ > ");
  while (true) {
    if (Serial.available())
      {
        while (Serial.available())
          {
            char C = Serial.read();
            CMD += C;
          }
      }
    if (CMD != "") {
      Serial.print(CMD);
      delay(TO * 2);
      sendData(CMD, TO, DBG);
      delay(TO * 2);
      CMD = "";
      Serial.print("\r\nArduino@ATMega2560 ~/ > ");
    } 
  }
}

void BasicAT() {
  // read from port 1, send to port 0:
  if (Serial1.available()) {
    char inChar = Serial1.read();
    Serial.write(inChar);
    ReqStr += inChar;
    //Serial.println(ReqStr);
  }
  
  // read from port 0, send to port 1:
  if (Serial.available()) {
    char inChar = Serial.read();
    Serial1.write(inChar);
  }
  
  if (ReqStr != "") {
    if (ReqStr.indexOf("GET / HTTP/1.1") >= 0) {
      ReqStr = "";
      Serial.println("\r\nGot connection.");
      SendContent();
    }
  }
}

void BeginServer(String PORT) {
  sendData("AT+CIPMUX=1\r\n", 500, true);
  sendData("AT+CIFSR\r\n", 500, true);
  sendData("AT+CIPSERVER=1," + PORT + "\r\n", 1000, true);
}

void SendContent() {
  delay(1000);
  Serial.println("\r\nReady to send headers.");
  SendHeaders();
  SendBody();
}

void SendHeaders() {
  /*String OKH = "HTTP/1.1 200 OK\r\n";
  String CONH = "Content-Type: text/html; charset=UTF-8\r\n";
  String OKL = "17";
  String CONL = "42";
  sendHtml(OKH, OKL, 200, true);
  sendHtml(CONH, CONL, 200, true);
  sendHtml("\r\n", "2", 200, true);*/
  Serial1.println("AT+CIPSEND=0,17");
  delay(SMWait);
  Serial1.println("HTTP/1.1 200 OK");
  delay(SMWait);
  Serial1.println("AT+CIPSEND=0,42");
  delay(SMWait);
  Serial1.println("Content-Type: text/html; charset=UTF-8");
  Serial1.println();
  delay(SMWait);
  Serial1.println("AT+CIPSEND=0,32");
  delay(SMWait);
  Serial1.println("<h1>Successful Connection</h1>");
  delay(SMWait);
  Serial1.println("AT+CIPCLOSE=0");
}

void SendBody() {
  /*String H1S = "<h1>Successful Connection</h1>\r\n";
  String H1L = "32";
  delay(1000);
  sendHtml(H1S, H1L, 200, true);
  sendData("AT+CIPCLOSE\r\n", 200, true);*/
  
}
