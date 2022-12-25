#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint16_t port_number;
} Port;

typedef struct {
    Port base;
} Port8Bit;

typedef struct {
    Port base;
} Port8BitSlow;

typedef struct {
    Port base;
} Port16Bit;

typedef struct {
    Port base;
} Port32Bit;

Port8Bit port_8bit_init(uint16_t port_number);
void port_8bit_write(Port8Bit * port, uint8_t data);
uint8_t port_8bit_read(Port8Bit * port);

Port8BitSlow port_8bit_slow_init(uint16_t port_number);
void port_8bit_slow_write(Port8BitSlow * port, uint8_t data);
uint8_t port_8bit_slow_read(Port8BitSlow * port);

Port16Bit port_16bit_init(uint16_t port_number);
void port_16bit_write(Port16Bit * port, uint8_t data);
uint8_t port_16bit_read(Port16Bit * port);

Port32Bit port_32bit_init(uint16_t port_number);
void port_32bit_write(Port32Bit * port, uint8_t data);
uint8_t port_32bit_read(Port32Bit * port);