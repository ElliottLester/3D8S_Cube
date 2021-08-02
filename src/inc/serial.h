#pragma once
#include <main.h>

void serial_setup(void);
void serial_putc(char c);
// void serial_puts(__code const char *s);
void serial_puts(const char *s);
INTERRUPT_USING(serial_isr, SI0_VECTOR, 1);
