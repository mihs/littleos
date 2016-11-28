#include "driver/fb.h"
#include "system.h"

void kerror(char* text) {
    fb_write_c("\n", FB_COLOR_BLACK, FB_COLOR_BLACK);
    fb_write_c(text, FB_COLOR_RED, FB_COLOR_BLACK);
    disable_interrupts();
    while(1) halt();
}
