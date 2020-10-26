#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "notes.h"

static int sb = 1;

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
  sb = 1;
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
    x -= 450;
  }

  short cycles = 2000000 / x;
  buzzer_set_period(cycles);
}

void buzz_song_advance()
{
  static char curr_note = 0;

  switch(curr_note) {
  case 0: //Plays note G
    buzzer_set_period(G);
    curr_note++;
    break;
  case 1: //Plays note E, hold 2 beats
    buzzer_set_period(E);
    curr_note++;
    break;
  case 3: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 4: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 5: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 6: //Plays note F, hold 2 beats
    buzzer_set_period(F);
    curr_note++;
    break;
  case 8: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 9: //Plays note D, hold 2 beats
    buzzer_set_period(D);
    curr_note++;
    break;
  case 11: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 12: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 13: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 14: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 15: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 16: //Plays note E
    buzzer_set_period(E);
    curr_note++;
    break;
  case 17:
    buzzer_set_period(0);
    curr_note++;
  case 18: //Plays note C, hold 2 beats
    buzzer_set_period(Cn);
    curr_note++;
    break;
  case 20: //Break in notes
    buzzer_set_period(0);
    curr_note++;
    break;
  case 21: //Plays note A#, hold 2 beats
    buzzer_set_period(ASH);
    curr_note++;
    break;
  case 23: //Plays note D, hold 2 beats
    buzzer_set_period(D);
    curr_note++;
    break;
  case 25: //Song end, back to beggining
    buzzer_set_period(0);
    curr_note = 0;
    break;
  default:
    curr_note++;
  }   
}  
    
