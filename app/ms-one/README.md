# MS-ONE Subtractive Synthesizer

MS-ONE (Marksard-Synthesizer-One) is a synthesizer using the Mozzi library and promicro.

## Spec

* 2 OSC(SAW, SAW2, SQU, SINE)
* 1 Lowpass Filter
* 2 Envelope (Filter amount, Amp amount)
* 1 LFO (amount to OSC2, F.FREQ and Chorus)
* 1 Chorus/Flanger Effect
* 1 Overdrive
* 1 Limitter
* Include Random Sequencer
* INPUT:
  * CV(V/OCT 0-4.8V)
  * Gate
  * USB MIDI IN (Gate/CVと切り替え)
* OUTPUT:
  * Mono Sound Out
* UI
  * Button x2
  * Rotary Encoder x4
  * OLED(SSD1306 128x32)

## Required

* compatible promicro (atmega32u4 5V 16MHz)
* Mozzi library 1.1.0 or later
* Tiny4kOLED 2.2.2 or later
* MIDIUSB 1.0.5 or later
