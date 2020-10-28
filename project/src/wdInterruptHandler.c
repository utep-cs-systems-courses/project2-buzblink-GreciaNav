#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char button_state = 0;
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;

  if (++blink_count == 62 && button_state == 0) { //Called roughly every 1/4th of a sec
    buzz_song_advance();
    blink_count = 0;
  }
  else if ((blink_count % 25) == 0 && button_state == 1) //Sound and blink pattern
     buzzer_advance();
  else if ((blink_count == 62) && button_state == 1) {
    main_state_advance();
    blink_count = 0;
  }
  else if (button_state == 2) {
    buzzer_set_period(0);
    turn_green_on();
  }
  else if (button_state == 3) {
    buzzer_set_period(0);
    turn_red_on();
  }
}
