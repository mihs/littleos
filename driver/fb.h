/* Framebuffer text mode */

#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

/* We need io functions for the fb_move_cursor */
#include "io.h"

/* Framebuffer colors */
#define FB_COLOR_BLACK        0x00
#define FB_COLOR_BLUE         0x01
#define FB_COLOR_GREEN        0x02
#define FB_COLOR_CYAN         0x03
#define FB_COLOR_RED          0x04
#define FB_COLOR_MAGENTA      0x05
#define FB_COLOR_BROWN        0x06
#define FB_COLOR_LGREY        0x07
#define FB_COLOR_DGREY        0x08
#define FB_COLOR_LBLUE        0x09
#define FB_COLOR_LGREEN       0x0A
#define FB_COLOR_LCYAN        0x0B
#define FB_COLOR_LRED         0x0C
#define FB_COLOR_LMAGENTA     0x0D
#define FB_COLOR_LBROWN       0x0E
#define FB_COLOR_WHITE        0x0F

#define FB_ADDRESS            0x000B8000
#define FB_ROWS               25
#define FB_COLUMNS            80

/* the cell size in bytes */
#define FB_CELL_SIZE          2

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/*
 * This function will output an ASCII character at the specified coordinates.
 * row and col start at 0.
 *
 * http://wiki.osdev.org/VGA_Hardware#Memory_Layout_in_text_modes
 *
 * TODO TEST: Depending on the mode setup, attribute bit 7 may be either the
 * blink bit or the fourth background color bit (which allows all 16 colors
 * to be used as background colours).
 *
 * TODO TEST: Attribute bit 3 (foreground intensity) also selects between
 * fonts A and B. Therefore if these fonts are not the same, this bit is
 * simultaneously an additional code point bit.
 *
 * TODO TEST: Attribute bit 0 also enables underline, if certain other
 * attribute bits are set to zero.
 *
 */
int fb_write_cell(
    unsigned int row,
    unsigned int col,
    unsigned char c,
    unsigned int fg,
    unsigned int bg
);

int fb_write_cell_raw(unsigned int row, unsigned int col, unsigned short data);
unsigned short fb_read_cell_raw(unsigned int row, unsigned int col);
void fb_write(char* buffer, unsigned int len, unsigned int fg, unsigned int bg);

/*
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned int row, unsigned int col);

#endif // INCLUDE_FB_H
