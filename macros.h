#ifndef MACROS_H
#define MACROS_H

#define SET_BIT(register,pin) register |= (1<<pin)
#define CLEAR_BIT(register,pin) register &= (~(1<<pin))
//return true bite on own place if bite on place is true
#define IS_TRUE_BIT(register,pin) register & (1<<pin)

#endif
