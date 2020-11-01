#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachine.h"
#include "buzz.h"

void __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if (P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void __interrupt_vec(WDT_VECTOR) WDT()
{
  static char blink_count = 0;
  if (++blink_count == 12) {
    short i = 0;
    while (i++ < 5) {
      short j = 0;
      while (j++ < 30000) {}
    }
    switch_interrupt_handler();
    blink_count = 0;
  } else {
    state_advance();
    led_update();
  }
}
