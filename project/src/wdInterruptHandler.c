#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char button_state = 0;
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_buz_count = 0;

  if (++blink_buz_count == 62 && button_state == 0) { //Called per 1/4th of a sec, plays song
    buzz_song_advance();
    blink_buz_count = 0;
  }
  else if ((blink_buz_count % 25) == 0 && button_state == 1) //Siren buzz
     buzzer_advance();
  else if ((blink_buz_count == 62) && button_state == 1) { //Advances siren state, switches leds
    siren_state_advance();
    blink_buz_count = 0;
  }
  else if (button_state == 2) { //Only green led on, buzzer off
    buzzer_set_period(0);
    turn_green_on();
  }
  else if ((blink_buz_count == 3) && button_state == 3) { //Only red led on, buzzer off
    buzzer_set_period(0);
    dim();
    blink_buz_count = 0;
  }
}
