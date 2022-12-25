#include "interrupts.h"

void print_str(char * str);

GateDescriptor interrupt_descriptor_table[256];

void set_interrupt_descriptor_table_entry(
    uint8_t interrupt_number,
    uint16_t code_segment_selector_offset,
    void (*handler)(),
    uint8_t descriptor_privilege_level,
    uint8_t descriptor_type) {
        const uint8_t IDT_DESC_PRESET = 0x80;

        interrupt_descriptor_table[interrupt_number].handler_address_lo = ((uint32_t)handler) & 0xFFFF;
        interrupt_descriptor_table[interrupt_number].handler_address_hi = (((uint32_t)handler) >> 16) & 0xFFFF;
        interrupt_descriptor_table[interrupt_number].gdt_code_segment_selector = code_segment_selector_offset;
        interrupt_descriptor_table[interrupt_number].access = IDT_DESC_PRESET | descriptor_type | ((descriptor_privilege_level & 3) << 5);
        interrupt_descriptor_table[interrupt_number].reserved = 0;
}

void init_interrupt_manager(GlobalDescriptorTable gdt) {
    uint16_t code_segment = gdt_code_segment_selector(gdt);
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for (uint16_t i = 0; i < 256; i++)
        set_interrupt_descriptor_table_entry(i, code_segment, ignore_interrupt_request, 0, IDT_INTERRUPT_GATE);

    set_interrupt_descriptor_table_entry(0x20, code_segment, handle_interrupt_request_0x00, 0, IDT_INTERRUPT_GATE);
    set_interrupt_descriptor_table_entry(0x21, code_segment, handle_interrupt_request_0x01, 0, IDT_INTERRUPT_GATE);

    IntteruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interrupt_descriptor_table;

    asm volatile("lidt %0" : : "m" (idt));
}

uint32_t interrupt_handler(uint8_t interrupt_number, uint32_t esp) {

    print_str(" INTERRUPT");

    return esp;
}

void activate() {
    asm("sti");
}