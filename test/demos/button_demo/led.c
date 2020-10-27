#include <msp430.h>
#include "led.h"
#include "switches.h"

char button_state = 0;
void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  switch_state_changed = 1;
  led_update();
}

void led_update(){
  if (switch_state_changed) {
    char ledFlags = 0; /* by default, no LEDs on */
    switch (button_state) {
    case 0:
      ledFlags |= LED_GREEN;
      break;
    case 1:
      ledFlags |= 0;
      break;
   case 2:
      ledFlags |= LED_RED;
      break;
   case 3:
      ledFlags |= 0;
      break;
    default:
      break;
    }  
    /*
    ledFlags |= switch_state_down ? LED_GREEN : 0;
    ledFlags |= switch_state_down ? 0 : LED_RED;
    */
    P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
    P1OUT |= ledFlags;         // set bits for on leds
  }
  switch_state_changed = 0;
}

