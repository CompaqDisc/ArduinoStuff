char serialLastChar = 0; // last character stored in buffer
int clsLine = 0; // will be used in while loop, controls 100 blank lines
boolean powerState = true; // if Serial Communications are active, false = sleep mode

#define IRpin_PIN PIND
#define IRpin 2 // pin for IR Data
const int statusWARN = 3; // pin for WARN LED (RED), also for PWM (Dimmable) on UNO
const int statusOK = 5; // pin for OK LED (GREEN), PWM
const int statusINFO = 6; // pin for INFO LED (BLUE), PWM
const int statusBUZZ = 8; // Onboard Buzzer / Speaker

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000
#define NUMPULSES 50

/* what our timing resolution should be, larger is better
as its more 'precise' - but too large and you wont get
accurate timing */
#define RESOLUTION 20 

// What percent we will allow in variation to match the same code, fault tolerance
#define FUZZINESS 20

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[NUMPULSES][2];  // pair is high and low pulse 
uint8_t currentpulse = 0; // index for pulses we're storing

#include "ircodes.h" // for decoding remote signals
#include "pitches.h" // for BUZZ tones

//#define DEBUG // uncomment for signal verification on remote
//int* Signal = PlaySignal;

void setup(void) {
  MockingjayBoot();
}

void loop(void) {
  int numberpulses;
  
  numberpulses = listenForIR();
  
  Serial.print("Heard ");
  Serial.print(numberpulses);
  Serial.println("-pulse long IR signal from:");
  if (IRcompare(numberpulses, PowerSignal,sizeof(PowerSignal)/4)) {
    Serial.println("--> Power Button");
    flashInfoLED();
  }
  else if (IRcompare(numberpulses, ReadSignal,sizeof(ReadSignal)/4)) {
    Serial.println("--> Mode Button (Read Buffer)");
    flashInfoLED();
    serialRead();
  }
  else if (IRcompare(numberpulses, SongSignal,sizeof(SongSignal)/4)) {
    Serial.println("--> Song Button");
    flashInfoLED();
    song();
  }
  else
  {
   
   printpulses();
   flashErrorLED();
   
  }
  delay(250);
}

//KGO: added size of compare sample. Only compare the minimum of the two
boolean IRcompare(int numpulses, int Signal[], int refsize) {
  int count = min(numpulses,refsize);
  Serial.print("count set to: ");
  Serial.println(count);
  for (int i=0; i< count-1; i++) {
    int oncode = pulses[i][1] * RESOLUTION / 10;
    int offcode = pulses[i+1][0] * RESOLUTION / 10;
    
#ifdef DEBUG    
    Serial.print(oncode); // the ON signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 0]); // the ON signal we want 
#endif   
    
    // check to make sure the error is less than FUZZINESS percent
    if ( abs(oncode - Signal[i*2 + 0]) <= (Signal[i*2 + 0] * FUZZINESS / 100)) {
#ifdef DEBUG
      Serial.print(" (ok)");
#endif
    } else {
#ifdef DEBUG
      Serial.print(" (x)");
#endif
      // we didn't match perfectly, return a false match
      return false;
    }
    
    
#ifdef DEBUG
    Serial.print("  \t"); // tab
    Serial.print(offcode); // the OFF signal we heard
    Serial.print(" - ");
    Serial.print(Signal[i*2 + 1]); // the OFF signal we want 
#endif    
    
    if ( abs(offcode - Signal[i*2 + 1]) <= (Signal[i*2 + 1] * FUZZINESS / 100)) {
#ifdef DEBUG
      Serial.print(" (ok)");
#endif
    } else {
#ifdef DEBUG
      Serial.print(" (x)");
#endif
      // we didn't match perfectly, return a false match
      return false;
    }
    
#ifdef DEBUG
    Serial.println();
#endif
  }
  // Everything matched!
  return true;
}

int listenForIR(void) {
  currentpulse = 0;
  
  while (1) {
    uint16_t highpulse, lowpulse;  // temporary storage timing
    highpulse = lowpulse = 0; // start out with no pulse length
  
//  while (digitalRead(IRpin)) { // this is too slow!
    while (IRpin_PIN & (1 << IRpin)) {
       // pin is still HIGH

       // count off another few microseconds
       highpulse++;
       delayMicroseconds(RESOLUTION);

       // If the pulse is too long, we 'timed out' - either nothing
       // was received or the code is finished, so print what
       // we've grabbed so far, and then reset
       
       // KGO: Added check for end of receive buffer
       if (((highpulse >= MAXPULSE) && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    // we didn't time out so lets stash the reading
    pulses[currentpulse][0] = highpulse;
  
    // same as above
    while (! (IRpin_PIN & _BV(IRpin))) {
       // pin is still LOW
       lowpulse++;
       delayMicroseconds(RESOLUTION);
        // KGO: Added check for end of receive buffer
        if (((lowpulse >= MAXPULSE)  && (currentpulse != 0))|| currentpulse == NUMPULSES) {
         return currentpulse;
       }
    }
    pulses[currentpulse][1] = lowpulse;

    // we read one high-low pulse successfully, continue!
    currentpulse++;
  }
}
void printpulses(void) {
//  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
//  for (uint8_t i = 0; i < currentpulse; i++) {
//    Serial.print(pulses[i][0] * RESOLUTION, DEC);
//    Serial.print(" usec, ");
//    Serial.print(pulses[i][1] * RESOLUTION, DEC);
//    Serial.println(" usec");
//  }
  
  // print it in a 'array' format
  Serial.println("int SignalSignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 0; i < currentpulse-1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.println(", 0};");
}

void MockingjayBoot(){
  RemoteBoot();
  pinMode(statusWARN, OUTPUT);
  pinMode(statusOK, OUTPUT);
  pinMode(statusINFO, OUTPUT);
  digitalWrite(statusOK, HIGH);
  delay(1000);
  flashInfoLED();
  Serial.println("Welcome to Mockinjay v2.0");
  Serial.println("Remote Functions:");
  flashInfoLED();
  Serial.println("1) Power Button toggles sleep / wake of serial communications");
  flashInfoLED();
  Serial.println("2) Mode Button reads buffer of serial input");
  flashInfoLED();
  Serial.println("3) Center Button (RED) triggers newline");
  flashInfoLED();
  Serial.println("4) U/SD Button (RED) triggers -Unleashed Serial Destruction- or, wipes serial screen");
  flashInfoLED();
  Serial.println("*) Play Button may play song once feature is added");
  flashInfoLED();
}

void RemoteBoot(){
  Serial.begin(9600);
  Serial.println("Connected");
  Serial.println("IR Remote Decoder Active");
}

void serialRead(){
  serialLastChar = Serial.read();
  if (Serial.available() > 0){
    Serial.print(serialLastChar);
    serialRead();
  } else {
    Serial.print("");
  }
}

void flashInfoLED(){
  digitalWrite(statusOK, LOW);
  digitalWrite(statusINFO, HIGH);
  delay(250);
  digitalWrite(statusINFO, LOW);
  digitalWrite(statusOK, HIGH);
  delay(250);
}

void flashErrorLED(){
  digitalWrite(statusOK, LOW);
  digitalWrite(statusWARN ,HIGH);
  delay(250);
  digitalWrite(statusWARN, LOW);
  digitalWrite(statusOK, HIGH);
  delay(250);
}

void song() {
  
  // notes in the melody:
  int melody[] = {
    NDS4, NE4, NFS4, 0,
    NB4, 0, NDS4, NE4,
    NFS4, NB4, NCS5, NDS5,
    NCS5, NAS4, NB4, 0,
    NFS4, 0, NDS4, NE4,
    NFS4, 0, NB4, 0,
    NCS5, NAS4, NB4, NCS5,
    NE5, NDS5, NE5, NCS5
  };

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 32; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / 10;
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}
