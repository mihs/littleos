OBJDIR = build
SRCDIR = src
OBJECTS = $(addprefix $(OBJDIR)/, loader.o driver/fb.o driver/serial.o kmain.o memory.o error.o x86.o)
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Werror -Wextra -c \
	 -std=c11 -I ./$(SRCDIR) -I ./$(SRCDIR)/driver -I /usr/include
LDFLAGS = -T $(SRCDIR)/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

.PHONY: clean

kernel: $(OBJDIR)/kernel.elf

iso: $(OBJDIR)/os.iso

$(OBJDIR)/kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $(OBJDIR)/kernel.elf

$(OBJDIR)/os.iso: $(OBJDIR)/kernel.elf
	cp -av iso/ $(OBJDIR)/
	cp $(OBJDIR)/kernel.elf $(OBJDIR)/iso/boot/kernel.elf
	genisoimage -R                              \
                -b boot/grub/stage2_eltorito    \
                -no-emul-boot                   \
                -boot-load-size 4               \
                -A os                           \
                -input-charset utf8             \
                -quiet                          \
                -boot-info-table                \
                -o $(OBJDIR)/os.iso                       \
                $(OBJDIR)/iso

run: $(OBJDIR)/os.iso
	bochs -f bochsrc.txt -q

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $$(dir $$@)
	$(CC) $(CFLAGS) $< -o $@

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.s | $$(dir $$@)
	$(AS) $(ASFLAGS) $< -o $@

.PRECIOUS: $(OBJDIR)/ $(OBJDIR)%/

$(OBJDIR)/:
	mkdir $(OBJDIR)

$(OBJDIR)%/:
	mkdir -p $@

all: iso

clean:
	rm -rf $(OBJDIR)
