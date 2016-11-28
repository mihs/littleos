#include "driver/fb.h"
#include "driver/serial.h"
#include "memory.h"
#include "error.h"

int main() {
    fb_clear();
    fb_write_c("Booting littleos\n", FB_COLOR_BLUE, FB_COLOR_WHITE);
    init_serial_log();
    log_serial("Starting machine");
    log_serial("Initializing memory");
    init_memory();
    log_serial("Memory initialized");
    fb_write_c("This is a \n", FB_COLOR_BLUE, FB_COLOR_WHITE);
    fb_write_c("test\n", FB_COLOR_BLUE, FB_COLOR_WHITE);
    return 0;
}
