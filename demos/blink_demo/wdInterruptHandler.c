#include <msp430.h>
#include "stateMachines.h"

__interrupt(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 125) {
    state_advance();
    blink_count = 0;
  }
}
