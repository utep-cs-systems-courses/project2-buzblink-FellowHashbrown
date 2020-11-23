
#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "buzz.h"
#include "switches.h"

void state_advance()
{
  char changed = 0;
  static char blink_count = 0;
  switch (switch_state_changed) {
  case 1:
    dim_75();
    changed = 1;
    break;
  case 2:
    dim_50();
    changed = 1;
    break;
  case 3:
    dim_25();
    changed = 1;
    break;
  case 4:
    if (++blink_count == 125) {
      binary_led();
      blink_count = 0;
    }
    changed = 1;
    break;
  }

  led_changed = changed;
}

void song_advance()
{
  static char song_count = 0;
  if (++song_count == 20) {
    switch (switch_state_changed) {
      case 1:
	song_1();
	break;
      case 2:
        song_2();
	break;
      case 3:
	song_3();
	break;
      case 4:
	stop();
	break;
    }
    song_count = 0;
  }
}
