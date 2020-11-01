#include <msp430.h>
#include "buzz.h"
#include "notes.h"
#include "libTimer.h"

static short furEliseCounter = 0;
static short cScaleCounter = 0;
static short resetCScale = 1;

void buzzer_init()
{
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void buzzer_set_period(short cycles)
{
  cycles = 2000000 / cycles;
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

void fur_elise()
{
  switch (furEliseCounter) {
    case 0: case 1:
    case 4: case 5:
    case 8: case 9:
    case 20: case 21:
    case 26: case 27:
      buzzer_set_period(E4);
      furEliseCounter++;
      break;
    case 2: case 3:
    case 6: case 7:
      buzzer_set_period(D4sharp);
      furEliseCounter++;
      break;
    case 10: case 11:
    case 24: case 25:
    case 30: case 31:
      buzzer_set_period(B4);
      furEliseCounter++;
      break;
    case 12: case 13:
      buzzer_set_period(D4);
      furEliseCounter++;
      break;
    case 14: case 15:
    case 18: case 19:
    case 32: case 33:
      buzzer_set_period(C4);
      if (furEliseCounter++ == 33) {
	furEliseCounter = 0;
      }
      break;
    case 16: case 17:
    case 22: case 23:
    case 28: case 29:
      buzzer_set_period(A4);
      furEliseCounter++;
      break;
  }
}

void c_scale(short direction)
{
  switch (cScaleCounter) {
    case 0:
      buzzer_set_period(C4);
      if (direction < 0 && resetCScale) {
        cScaleCounter = 11;
	resetCScale = 0;
      } else {
	cScaleCounter += direction;
      }
      break;
    case 1:
      buzzer_set_period(C4sharp);
      cScaleCounter += direction;
      resetCScale = 1;
      break;
    case 2:
      buzzer_set_period(D4);
      cScaleCounter += direction;
      break;
    case 3:
      buzzer_set_period(D4sharp);
      cScaleCounter += direction;
      break;
    case 4:
      buzzer_set_period(E4);
      cScaleCounter += direction;
      break;
    case 5:
      buzzer_set_period(F4);
      cScaleCounter += direction;
      break;
    case 6:
      buzzer_set_period(F4sharp);
      cScaleCounter += direction;
      break;
    case 7:
      buzzer_set_period(G4);
      cScaleCounter += direction;
      break;
    case 8:
      buzzer_set_period(G4sharp);
      cScaleCounter += direction;
      break;
    case 9:
      buzzer_set_period(A4);
      cScaleCounter += direction;
      break;
    case 10:
      buzzer_set_period(A4sharp);
      cScaleCounter += direction;
      resetCScale = 1;
      break;
    case 11:
      buzzer_set_period(B4);
      if (direction > 0 && resetCScale) {
	cScaleCounter = 0;
      } else {
        cScaleCounter += direction;
      }
      break;
  }
}

void stop()
{
  buzzer_set_period(0);
}
