#include "memory.h"
#include "interrupts.h"
#include "error.h"

void init_memory() {

    /*
     * Minimal segmentation model. Flat.
     *
     * (from littleosbook.github.io)
     * Index    Offset  Name                    Address range                   Type    DPL
            0   0x00    null descriptor
            1   0x08    kernel code segment     0x00000000 - 0xFFFFFFFF         RX      PL0
            2   0x10    kernel data segment     0x00000000 - 0xFFFFFFFF         RW      PL0
     */
    disable_interrupts();
    load_gdt();
}
