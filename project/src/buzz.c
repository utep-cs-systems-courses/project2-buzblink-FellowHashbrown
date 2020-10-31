#include <msp430.h>
#include "libTimer.h"
#include "buzz.h"

static int furEliseCounter = 0;
static int cScaleCounter = 0;

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
  CCR0 = cycles;
  CCR1 = cycles >> 1;
}

void furElise()
{
  switch (furEliseCounter) {
    case 0:
    case 2:
    case 4:
    case 10:
    case 13:
      // play e note
      break;
    case 1:
    case 3:
      // play d sharp note
      break;
    case 5:
    case 12:
    case 15:
      // play b note
      break;
    case 6:
      //play d note
      break;
    case 7:
    case 9:
    case 16:
      // play c note
      // go back to 0
      break;
    case 8:
    case 11:
    case 14:
      // play a note
      break;
  }
}

void cScale()
{
  switch (cScaleCounter) {
    case 0:
      // play c note
      break;
    case 1:
      // play d note
      break;
    case 2:
      // play e note
      break;
    case 3:
      // play f note
      break;
    case 4:
      // play g note
      break;
    case 5:
      // play a note
      break;
    case 6:
      // play b note
      break;
  }
}
