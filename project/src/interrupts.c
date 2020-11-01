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
  if (++blink_count == 30) {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 30000; j++) {
      }
    }
    switch_interrupt_handler();
    blink_count = 0;
  }
  state_advance();
  led_update();
}
