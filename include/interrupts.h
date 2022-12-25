#pragma once

#include <stdint.h>
#include <stddef.h>

#include "gdt.h"

typedef struct {
    uint16_t handler_address_lo;
    uint16_t gdt_code_segment_selector;
    uint8_t reserved;
    uint8_t access;
    uint16_t handler_address_hi;

} GateDescriptor;

GateDescriptor interrupt_descriptor_table[256];

typedef struct {
    uint16_t size;
    uint32_t base;
} IntteruptDescriptorTablePointer;

void init_interrupt_manager(GlobalDescriptorTable gdt);

void set_interrupt_descriptor_table_entry(
    uint8_t interrupt_number,
    uint16_t code_segment_selector_offset,
    void (*handler)(),
    uint8_t descriptor_privilege_level,
    uint8_t descriptor_type);

uint32_t interrupt_handler(uint8_t interrupt_number, uint32_t esp); 

void activate();

void ignore_interrupt_request();
void handle_interrupt_request_0x00();
void handle_interrupt_request_0x01();