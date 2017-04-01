#include "flags_automate.h"

// --------------- HAL layer (TODO another header) ----------------------
#define F_CPU 8000000
#define PRESCALER 64
// Number of timer impulses
#define TIMER_DIVIDER 1*(F_CPU/PRESCALER/1000)
// ----------------------------------------------------------------------

/* ----------------------------------------------------------------------
 * ----------------------- Flags Automate Layer  ------------------------
 * ------------------------------------------------------------------- */

 #include "macros.h"
 #include <avr/io.h>
 #include <avr/interrupt.h>

 // Flag byte with tasks states (1=ON, 0=OFF)
 uint16_t TASKS_FLAGS = 0x0000;

 #define SET_TASK_ON(task_number) SET_BIT(TASKS_FLAGS, task_number)
 #define SET_TASK_OFF(task_number) CLEAR_BIT(TASKS_FLAGS, task_number)

 // Array with pointers on automate functions (program layer)
 void(*automate_func[NUMBER_OF_TASKS])(void) = {read_encoder, read_temperature};

// Array with structure fields task number and timer counter
struct timer_array
{
  uint8_t flag_number;
  uint16_t timer;
} timer_tasks[NUMBER_OF_TIMER_TASKS];

void run_over_flags()
{
  for (unsigned int i=0;i<NUMBER_OF_TASKS;i++)
  {
    if(IS_TRUE_BIT(TASKS_FLAGS,i)) automate_func[i]();
  }
}

void init_flag_timer()
{
  cli();
  TCCR0B = 0; // Stop timer
  TCNT0 = 0; // Clear timer counter register
  TCCR0A = (1<<WGM01); // Clear timer on compare (CTC) mode
  OCR0A = TIMER_DIVIDER; // Number of implulses for 1 ms delay
  TIMSK0 = (1<<OCIE0A); // Enable interrupts on compare match
  TCCR0B = (1<<CS01)|(1<<CS02); // Prescaler CLK/64 and run timer
  sei();
}

void add_timer(uint8_t flag, uint16_t time)
{
  cli();
  for(uint8_t i=0; i<NUMBER_OF_TIMER_TASKS; i++)
  {
    if (timer_tasks[i].flag_number==flag)
    {
      timer_tasks[i].timer=time;
      sei();
      return;
    }
  }
  for (uint8_t i=0; i<NUMBER_OF_TIMER_TASKS; i++)
  {
    if (timer_tasks[i].timer==UINT16_MAX)
    {
      timer_tasks[i].flag_number=flag;
      timer_tasks[i].timer=time;
      sei();
      return;
    }
  }
  sei();
  return;
}

/* Timer duty run in interrupt every 1 ms */
ISR(TIMER0_COMPA_vect)
{
  //decrement tasks timer
  for (uint8_t i=0; i<NUMBER_OF_TIMER_TASKS; i++)
  {
    if (timer_tasks[i].timer==UINT16_MAX) continue;
    else if (timer_tasks[i].timer==0) SET_TASK_ON(timer_tasks[i].flag_number);
    else timer_tasks[i].timer--;
  }
}

/* ------------------------------------------------------------------------
 * ----------------- Program Layer (Automate Functions) -------------------
 * --------------------------------------------------------------------- */

 #include "HAL.h"
 // #include "encoder.h"
 #include <stdint.h>

 uint16_t SET_TEMPERATURE = 250;
 uint16_t STATE_TEMPERATURE = 20;

 void read_encoder()
 {
   SET_TASK_OFF(TASK_READ_ENCODER);
   check_encoder_state();
   uint8_t state = get_encoder_state();
   switch(state)
   {
     case SPIN_LEFT:
     {
       SET_TEMPERATURE--;
       break;
     }
     case SPIN_RIGHT:
     {
       SET_TEMPERATURE++;
       break;
     }
   }
   add_timer(TASK_READ_ENCODER, 100);
 }

 void read_temperature()
 {

 }

 void run_pid()
 {

 }
