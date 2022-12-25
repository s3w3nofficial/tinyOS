extern interrupt_handler
global ignore_interrupt_request

section .text
bits 64

%macro HandleInterruptException 1
global handle_interrupt_exception_%1
handle_interrupt_exception_%1:
    push rax
    add rax, %1
    mov [interrupt_number], rax
    jmp int_bottom
    pop rax
%endmacro

%macro HandleInterruptRequest 1
global handle_interrupt_request_%1
handle_interrupt_request_%1:
    push rax
    mov rax, 0x20
    add rax, %1
    mov [interrupt_number], rax
    jmp int_bottom
    pop rax
%endmacro

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01

int_bottom:
    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

    push rax
    push rcx
    push rdx
    push rbx
    push rbp
    push rsi
    push rdi

    push rsp
    push (interrupt_number)
    call interrupt_handler
    mov rsp, rax

    pop rdi
    pop rsi
    pop rbp
    pop rbx
    pop rdx
    pop rcx
    pop rax

ignore_interrupt_request:
    iret

section .data
    interrupt_number: 
        db 0
