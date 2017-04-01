#ifndef FLAGS_AUTOMATE_H
#define FLAGS_AUTOMATE_H

/* -------------------------------------------------------------------------
 * Flags automate for 16 tasks. Need to define all the tasks in
 * Program Layer Functions block and in function pointers array.
 * run_over_flags() must be used in main cycle to execute automate functions.
 * Timer procedure must be initialized and configured with init_timer().
 * Timed tasks are added using add_timer(number in flag byte, delay time).
 * ------------------------------------------------------------------------ */

#include <stdint.h>
#include "macros.h"

/* ------------------------------------------------------------------------
 * ----------------------- Flags Automate Layer  --------------------------
 * --------------------------------------------------------------------- */

// ---------------- Flags Automate configuration --------------------------
#define NUMBER_OF_TASKS 6 // No more than 16
#define NUMBER_OF_TIMER_TASKS 3 // No more than 16-NUMBER_OF_TASKS

// ------------------ Main flags automate functions -----------------------
void run_over_flags();
void init_flag_timer();
void add_timer(uint8_t flag, uint16_t time);




/* ------------------------------------------------------------------------
 * ----------------- Program Layer (Automate Functions) -------------------
 * --------------------------------------------------------------------- */

// ------------- Declaration of task numbers in flag byte -----------------
#define TASK_READ_ENCODER 0
#define TASK_READ_TEMP 1
#define TASK_RUN_PID 2
#define TASK_RUN_ADC_SCAN 3
#define TASK_SET_PWM 4

// ------------ Program Layer Functions (Automate Functions) --------------
void read_encoder(void); // scan every 100ms
void read_temperature(void);
void run_pid(void);
void run_adc_scan(void);
void set_pwm(void);

#endif
