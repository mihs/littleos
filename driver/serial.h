#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

#include "io.h"

/*
  http://wiki.osdev.org/Serial_ports
 */

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_INTERRUPT_PORT(base) (base + 1)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

#define SERIAL_DIVISOR_LOW(base) (base)
#define SERIAL_DIVISOR_HIGH(base) (base + 1)

void serial_set_baud_rate(unsigned int port, unsigned short divisor);
void serial_configure_line(unsigned int port, unsigned char config);
void init_serial_log();
void log_serial(char* buffer);
void serial_write(unsigned int port, char* buffer);
int serial_is_transmit_fifo_empty(unsigned int port);

#endif // INCLUDE_SERIAL_H
