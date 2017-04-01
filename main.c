#include <avr/io.h>
#include "flags_automate.h"

//#define __AVR_ATmega328P__

int main()
{
  init_flag_timer();
  // SET ON ALL TASKS (make init function)
  while(1)
  {
    run_over_flags();
  }
}
