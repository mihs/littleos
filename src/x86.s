global outb
global inb
global load_gdt
global enable_interrupts
global disable_interrupts
global halt

; outb - send a byte to an I/O port
; stack: [esp + 8] the data byte
;        [esp + 4] the I/O port
;        [esp    ] return address
outb:
    mov al, [esp + 8]    ; move the data to be sent into the al register
    mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
    out dx, al           ; send the data to the I/O port
    ret                  ; return to the calling function

; inb - returns a byte from the given I/O port
; stack: [esp + 4] The address of the I/O port
;        [esp    ] The return address
inb:
    mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
    in  al, dx              ; read a byte from the I/O port and store it in the al register
    ret                     ; return the read byte

load_gdt:
    mov eax, gdt
    lgdt [gdtr]
    jmp 0x08:load_data_regs

; initializes the segment registers to use the simple flat model segmentation
; grub leaves us in protected mode
load_data_regs:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov gs, ax
    mov fs, ax
    ret

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

halt:
    hlt

section .rodata
; Flat model 4GB, one segment for code and one for data
gdt:
    DB 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    DB 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00
    DB 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00
gdt_end:

gdtr: DW gdt_end - gdt - 1
      DD gdt
