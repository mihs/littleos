#ifndef INCLUDE_MEMORY_H
#define INCLUDE_MEMORY_H

#include <inttypes.h>

void init_memory();

/*
 * Since we don't use segmentation, we use this simple function to setup
 * entries in the gdt array
 * Implemented in x86.s
 */
void load_gdt();

#endif // INCLUDE_MEMORY_H
