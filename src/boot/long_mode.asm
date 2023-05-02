extern kernel_early_main
extern kernel_main
extern kernel_end

section .text
bits 64
long_mode_start:
    ; Load null into all data segment registers
    mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	; Init serial communication
	call kernel_early_main

	; Main execution code
    call kernel_main ; Defined in src/kernel/kernel.c

    ; Execute final bit of C-Code to clean up
	call kernel_end ; Defined in src/kernel/kernel.c

	; Halt
	hlt