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
#include "pitches.h"

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

void setup() {
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

void loop() {
  // no need to repeat the melody.
}
