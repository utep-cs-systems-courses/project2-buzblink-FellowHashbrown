#include <msp430.h>
#include "buzz.h"
#include "notes.h"
#include "libTimer.h"

static short furEliseCounter = 0;
static short cScaleCounter = 0;
static short resetCScale = 1;
static short stop_state = 0;

static int furEliseNotes[] = {
  E4, D4sharp, E4, D4sharp, E4,
  B3, D4, C4, A3, A3, A3, A3,
  C3, E3, A3, B3, B3, B3, B3,
  E3, A3, B3, C4, C4, C4, C4, E3
};
static short furEliseLength = 27;
static short furEliseIndex = 0;

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
  case 0:
    buzzer_set_period(furEliseNotes[furEliseIndex]);
    furEliseCounter++;
    break;
  case 1:
    buzzer_set_period(furEliseNotes[furEliseIndex]);
    if (++furEliseIndex == furEliseLength) {
      furEliseIndex = 0;
    }
    furEliseCounter = 0;
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
