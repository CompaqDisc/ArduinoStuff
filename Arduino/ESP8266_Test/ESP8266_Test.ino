int WaitMS = 500;
String RET = "\r\n";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial1.begin(115200);
  while (!Serial1) {
    Serial.println("Waiting for WiFi Module connection..."); // wait for WiFi module to connect by serial.
  }
  Serial.println("Module connected.");
  while (!checkATResponse()) {
    Serial.println("Waiting on AT OK response..."); // wait for the WiFi module to report "OK" on "AT" command.
  }
  Serial.println("AT OK response recieved.");
  
  Connect("google.com", "/", 80);
  
  Serial.print("\r\nThe terminal is yours.\r\n");
}

void loop() {
  //RelayAT_CMDS(100, true);
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
    int inByte = Serial1.read();
    Serial.write(inByte); 
  }
  
  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte); 
  }
}

void Connect(String domain, String document, int port) {
  int wt = 500;
  Serial1.print("AT+CIPMUX=1\r\n");
  delay(wt);
  Serial1.print("AT+CIPSTART=4,\"TCP\",\"" + domain + "\"," + port + "\r\n");
  delay(wt);
  String GET_REQ = "GET " + document +" HTTP/1.0\r\n\r\n";
  Serial1.print("AT+CIPSEND=4," + sizeof(GET_REQ));
  delay(wt);
  Serial1.print(GET_REQ);
  delay(wt);
}
