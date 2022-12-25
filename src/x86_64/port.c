#include "port.h"

Port8Bit port_8bit_init(uint16_t port_number) {
    Port port = { .port_number = port_number };
    Port8Bit port8bit = { .base = port };
    
    return port8bit;
}

void port_8bit_write(Port8Bit * port, uint8_t data) {
    asm volatile("outb %0, %1" : : "a" (data), "Nd" ((* port).base.port_number));
}

uint8_t port_8bit_read(Port8Bit * port) {
    uint8_t result;
    asm volatile("inb %1, %0" : "=a" (result) : "Nd" ((* port).base.port_number));
    return result;
}

Port8BitSlow port_8bit_slow_init(uint16_t port_number) {
    Port port = { .port_number = port_number };
    Port8BitSlow port8bit = { .base = port };
    
    return port8bit;
}

void port_8bit_slow_write(Port8BitSlow * port, uint8_t data) {
    asm volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" ((* port).base.port_number));
}

uint8_t port_8bit_slow_read(Port8BitSlow * port) {
    uint8_t result;
    asm volatile("inb %1, %0" : "=a" (result) : "Nd" ((* port).base.port_number));
    return result;
}