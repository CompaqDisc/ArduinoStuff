/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://arduino.cc/en/Tutorial/Tone

 */
#include <Arduino.h>
#include "pitches.h"

// Line 1 in nbs file
// notes in the melody: 0 for none
int melody[] = {
  CS5, 0, E5, 0, 0, 0, E5, 0, FS5, 0, 0, 0, B4, 0, GS4, 0, 0, 0, CS5, 0, 0, 0, E5, 0, FS5, 0, 0, 0, GS4, 0, CS5, 0, 0, 0, CS5, 0, 0, 0, E5, 0, FS5, 0, 0, 0, B4, 0, GS4, 0
};

void setup() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 48; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000 / 8, etc.
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

void loop() {

}
