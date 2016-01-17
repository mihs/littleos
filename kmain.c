#include "driver/fb.h"
#include "driver/serial.h"

int main() {
    fb_write("1234567890\n", 11, FB_COLOR_BLUE, FB_COLOR_WHITE);
    fb_write("This is a \n", 11, FB_COLOR_BLUE, FB_COLOR_WHITE);
    fb_write("test\n", 5, FB_COLOR_BLUE, FB_COLOR_WHITE);
    init_serial_log();
    log_serial("starting machine");
    return 0;
}
