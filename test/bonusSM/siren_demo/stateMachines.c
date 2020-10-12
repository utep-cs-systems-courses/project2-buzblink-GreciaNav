#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"

char turn_green_on()	/* only toggle green if red is on!  */
{
  green_on = 1;
  red_on = 0;
  led_update();
}

char turn_red_on()
{
  red_on = 1;
  green_on = 0;
  led_update();
}

void up_state(){
  static int sb = 1;
  turn_green_on();
}

void down_state(){
  sb = 0;
  turn_red_on();
}

void main_state_advance(){
  static char state = 0;
  switch(state) {
  case 0:
  case 1:
    up_state();
    state++;
    break;
  case 2:
    down_state();
    state = 0;
  default:
    break;
  }
}

void buzzer_advance()
{
  static int x = 500;
  if (sb) {
    x += 225;
  }
  else{
    x -= 400;
  }

  char cycles = 2000000 / x;
  buzzer_set_period(cycles);
}
    
