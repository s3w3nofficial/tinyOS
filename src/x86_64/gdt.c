#include "gdt.h"

GlobalDescriptorTable * gdt_init() {

    SegmentDescriptor nullSegmentSelector = segment_descriptor_init(0, 0, 0);
    SegmentDescriptor unusedSegmentSelector = segment_descriptor_init(0, 0, 0);
    SegmentDescriptor codeSegmentSelector = segment_descriptor_init(0, 64*1024*1024, 0x9A);
    SegmentDescriptor dataSegmentSelector = segment_descriptor_init(0, 64*1024*1024, 0x92);

    GlobalDescriptorTable gdt = {
        .nullSegmentSelector = nullSegmentSelector,
        .unusedSegmentSelector = unusedSegmentSelector,
        .codeSegmentSelector = codeSegmentSelector,
        .dataSegmentSelector = dataSegmentSelector 
    };

    uint32_t i[2];
    i[0] = (uint32_t)&gdt;
    i[1] = sizeof(GlobalDescriptorTable) << 16;

    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i) + 2));
}

uint16_t gdt_data_segment_selector(GlobalDescriptorTable gtd) {
    uint8_t * dataSegmentSelector = (uint8_t *)&gtd.dataSegmentSelector;
    return (uint16_t)(dataSegmentSelector - (uint8_t)&gtd);
}

uint16_t gdt_code_segment_selector(GlobalDescriptorTable gtd) {
    uint8_t * codeSegmentSelector = (uint8_t *)&gtd.codeSegmentSelector;
    return (uint16_t)(codeSegmentSelector - (uint8_t)&gtd);
}

SegmentDescriptor segment_descriptor_init(uint32_t base, uint32_t limit, uint8_t flags) {
    SegmentDescriptor this = {0};
    uint8_t * target = (uint8_t *)&this;

    if (limit <= 65536)
    {
        target[6] = 0x40;
    }
    else
    {
        if ((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12) - 1;
        else
            limit = limit >> 12;

        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF; 
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;
    
    target[5] = flags;
}

uint32_t segment_descriptor_base(SegmentDescriptor segmentDescriptor) {
    uint8_t * target = (uint8_t *)&segmentDescriptor;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

uint32_t segment_descriptor_limit(SegmentDescriptor segmentDescriptor) {
    uint8_t * target = (uint8_t *)&segmentDescriptor;
    uint32_t result = target[6] & 0xF;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if (target[6] & 0xC0 == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;
}