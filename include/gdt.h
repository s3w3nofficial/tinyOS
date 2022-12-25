#pragma once

#include <stdint.h>
#include <stddef.h>

typedef struct {   
    uint16_t limit_lo;
    uint16_t base_lo;
    uint8_t base_hi;
    uint8_t type;
    uint8_t flags_limit_hi;
    uint8_t base_vhi;
} SegmentDescriptor;

typedef struct {
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;
} GlobalDescriptorTable;

GlobalDescriptorTable * gdt_init();
uint16_t gdt_data_segment_selector(GlobalDescriptorTable gdt);
uint16_t gdt_code_segment_selector(GlobalDescriptorTable gdt);

SegmentDescriptor segment_descriptor_init(uint32_t base, uint32_t limit, uint8_t flags);
uint32_t segment_descriptor_base(SegmentDescriptor segmentDescriptor);
uint32_t segment_descriptor_limit(SegmentDescriptor segmentDescriptor);