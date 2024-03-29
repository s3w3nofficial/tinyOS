#include "print.h"
#include "gdt.h"
#include "interrupts.h"
#include <stdint.h>

void kernel_main() {
  print_clear();
  print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
  print_str("Welcome to our 64-bit kernel!");

  print_newline();

  GlobalDescriptorTable * gdt = gdt_init();

  init_interrupt_manager(*gdt);

  activate();
}