#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "switches.h"

void state_advance()
{
  char changed = 0;
  switch (switch_state_changed) {
  case 1:
    toggle_green();
    changed = 1;
    break;
  case 2:
    toggle_red();
    changed = 1;
    break;
  case 3:
    red_on = 0;
    green_on = 0;
    toggle_red_green();
    changed = 1;
    break;
  case 4:
    toggle_off();
    changed = 1;
    break;
  }

  led_changed = changed;
  led_update();
}
