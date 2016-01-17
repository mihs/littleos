#include "fb.h"
#include "error.h"

static int fb_row = 0;
static int fb_col = 0;

int fb_write_cell(
    unsigned int row,
    unsigned int col,
    unsigned char c,
    unsigned int fg,
    unsigned int bg
) {
    return fb_write_cell_raw(row, col, (c & 0xFF) | ((fg & 0x0F) << 12) | ((bg & 0x0F) << 8));
}

int fb_write_cell_raw(unsigned int row, unsigned int col, unsigned short data) {
    if (row >= FB_ROWS || col >= FB_COLUMNS) {
        return -EFBOUTRANGE;
    }
    /* on little-endian arch, the bytes will be switched and the character
     * will be placed first */
    *(unsigned short*)(FB_ADDRESS + (row * FB_COLUMNS + col) * FB_CELL_SIZE) = data;
    return 0;
}

unsigned short fb_read_cell_raw(unsigned int row, unsigned int col) {
    if (row >= FB_ROWS || col >= FB_COLUMNS) {
        return -1;
    }
    return *(unsigned short*)(FB_ADDRESS + (row * FB_COLUMNS + col) * FB_CELL_SIZE);
}

void fb_move_cursor(unsigned int row, unsigned int col) {
    unsigned short pos = (row * FB_COLUMNS + col);
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

void fb_write(char* buffer, unsigned int len, unsigned int fg, unsigned int bg) {
    /* TODO use hardware scrolling */
    for (unsigned int i = 0; i < len; i++) {
        if (fb_col > FB_COLUMNS) {
            fb_col = 0;
            fb_row++;
        }
        if (buffer[i] == '\n') {
            fb_col = 0;
            fb_row++;
        }
        if (fb_row >= FB_ROWS) {
            /* move the previous rows up by one line */
            for (int prow = 0; prow < fb_row; prow++) {
                for (int pcol = 0; pcol < FB_COLUMNS; pcol++) {
                    fb_write_cell_raw(prow - 1, pcol, fb_read_cell_raw(prow, pcol));
                }
            }
            fb_row = FB_ROWS - 1;
        }
        if (buffer[i] == '\n') {
            continue;
        }
        fb_move_cursor(fb_row, fb_col);
        fb_write_cell(fb_row, fb_col, buffer[i], fg, bg);
        fb_col++;
    }
}
