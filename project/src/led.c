#include <msp430.h>
#include "led.h"
#include "switches.h"

static char red[] = {0, RED}, green[] = {0, GREEN};

void led_init()
{
  P1DIR |= LEDS;
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed) {
    char ledFlags = 0;

    ledFlags = red[red_on] | green[green_on];

    P1OUT &= (0xff ^ LEDS) | ledFlags;
    P1OUT |= ledFlags;
    led_changed = 0;
  }
}

void toggle_red()
{
  if (red_on) { red_on = 0; }
  else { red_on = 1; }
  led_changed = 1;
}

void toggle_green()
{
  if (green_on) { green_on = 0; }
  else { green_on = 1; }
  led_changed = 1;
}

void toggle_red_green()
{
  toggle_red();
  toggle_green();
  led_changed = 1;
}

void toggle_off()
{
  red_on = green_on = 0;
  led_changed = 1;
}
