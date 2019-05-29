# Flags Automate library for AVR-based MCUs
Flags automate for 16 tasks. Need to define all the tasks in Program Layer Functions block and in function pointers array. run_over_flags() must be used in main cycle to execute automate functions. Timer procedure must be initialized and configured with init_timer(). Timed tasks are added using add_timer(number in flag byte, delay time).
