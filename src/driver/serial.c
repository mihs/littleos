#include "serial.h"

void serial_set_baud_rate(unsigned int port, unsigned short divisor) {
    short line_control = inb(SERIAL_LINE_COMMAND_PORT(port));
    outb(SERIAL_LINE_COMMAND_PORT(port), line_control | 0x80);
    outb(SERIAL_DIVISOR_LOW(port), divisor & 0x00FF);
    outb(SERIAL_DIVISOR_HIGH(port), (divisor >> 8) & 0x00FF);

    // Restore the previous line control value and delete DLAB bit;
    outb(SERIAL_LINE_COMMAND_PORT(port), line_control & 0x7F);
}

void serial_configure_line(unsigned int port, unsigned char config) {
    outb(SERIAL_LINE_COMMAND_PORT(port), config);
}

void init_serial_log() {
    unsigned int port = COM1;
    serial_set_baud_rate(port, 12);

    /* Disable interrupts */
    outb(SERIAL_INTERRUPT_PORT(port), 0x00);

    /*
     * FIFO
     * 14 bytes length, 56 bytes size
     * enable FIFO and clear buffers
     * 11000111
     */
    outb(SERIAL_FIFO_COMMAND_PORT(port), 0xC7);

    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    serial_configure_line(port, 0x03);

    /* Modem
     * Enable DTS and RTS
     */
    outb(SERIAL_MODEM_COMMAND_PORT(port), 0x03);
}

void log_serial(char* buffer) {
    serial_write(COM1, buffer);
    serial_write(COM1, "\n");
}

void serial_write(unsigned int port, char* buffer) {
    char* c = buffer;
    while(*c != '\0') {
        while(serial_is_transmit_fifo_empty(port) == 0);
        outb(SERIAL_DATA_PORT(port), *c++);
    }
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int port)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(port)) & 0x20;
}
