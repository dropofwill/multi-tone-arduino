/*
  Multiple tone player

 Plays multiple tones on multiple pins to play basic power chords

 circuit:
 * 3 8-ohm speaker on digital pins set by the constants LEFT_S, MID_S, RIGHT_S
 * Capacative touch setup on the default I2C

 base on code from Tom Igoe
 based on a snippet from Greg Borenstein

This example code is in the public domain.

 http://arduino.cc/en/Tutorial/Tone4
 */

#include <Tone.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"
#include "pitches.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

// Pins for the speakers
const int LEFT_S  = 11;
const int MID_S   = 5;
const int RIGHT_S = 3;
// Pins for the touch
const int LEFT_T  = 6;
const int MID_T   = 8;
const int RIGHT_T = 10;

boolean is_left = false;
boolean is_mid = false;
boolean is_right = false;

Tone freq1;
Tone freq2;

void setup() {
  Serial.begin(9600);
  freq1.begin(LEFT_S);
  freq2.begin(RIGHT_S);

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
 if (!cap.begin(0x5A)) { while (1); }
}

void loop() {
    // Get the currently touched pads
  currtouched = cap.touched();

  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      if (i == LEFT_T) {
        is_left = true;
      }
      if (i == MID_T) {
        is_mid = true;
      }
      if (i == RIGHT_T) {
        is_right = true;
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      if (i == LEFT_T) {
        is_left = false;
      }
      if (i == MID_T) {
        is_mid = false;
      }
      if (i == RIGHT_T) {
        is_right = false;
      }
    }
  }

//  // G5 - Bb5 - F5

//  // G5: G2 and D2
//  // Bb5: Bb2/As2 and F3
//  // F5:  F2 and C2
//  if (!is_left && !is_mid && !is_right) {
//    freq1.stop();
//    freq2.stop();
//  }
//  // G
//  else if (is_left && !is_mid && !is_right) {
//    freq2.stop();
//    freq1.play(NOTE_G3);
//  }
//  // Bb
//  else if (is_mid && !is_left && !is_right) {
//    freq1.play(NOTE_AS3);
//    freq2.stop();
//  }
//  // F
//  else if (is_right && !is_left && !is_mid) {
//    freq1.play(NOTE_F3);
//    freq2.stop();
//  }
//  // G5
//    else if (is_left && is_mid && !is_right) {
//    freq1.play(NOTE_G3);
//    freq2.play(NOTE_D3);
//  }
//  // Bb5
//  else if (is_mid && is_right && !is_left) {
//    freq1.play(NOTE_AS3);
//    freq2.play(NOTE_F4);
//  }
//  // F5
//  else if (is_right && is_left && !is_mid) {
//    freq1.play(NOTE_F3);
//    freq2.play(NOTE_C3);
//  }


  // A5 - D5 - E5

  // A5:  G2 and D2
  // D5:  Bb2/As2 and F3
  // E5:  F2 and C2
  // off
  if (!is_left && !is_mid && !is_right) {
    freq1.stop();
    freq2.stop();
  }
  // A
  else if (is_left && !is_mid && !is_right) {
    freq2.stop();
    freq1.play(NOTE_A3);
  }
  // D
  else if (is_mid && !is_left && !is_right) {
    freq1.play(NOTE_D3);
    freq2.stop();
  }
  // E
  else if (is_right && !is_left && !is_mid) {
    freq1.play(NOTE_E3);
    freq2.stop();
  }
  // A5
    else if (is_left && is_mid && !is_right) {
    freq1.play(NOTE_A3);
    freq2.play(NOTE_E4);
  }
  // D5
  else if (is_mid && is_right && !is_left) {
    freq1.play(NOTE_D3);
    freq2.play(NOTE_A4);
  }
  // E5
  else if (is_right && is_left && !is_mid) {
    freq1.play(NOTE_E3);
    freq2.play(NOTE_B3);
  }

  // reset our state
  lasttouched = currtouched;
}
