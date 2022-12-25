//#include "char.h"
//#include "keyboard.h"
#include "print.h"
#include "gdt.h"
#include <stdint.h>

/*
void test_input()
{
  char ch = 0;
  char keycode = 0;
  do{
    keycode = get_input_keycode();
    if(keycode == KEY_ENTER){
      print_newline();
    }else{
      ch = get_ascii_char(keycode);
      print_char(ch);
    }
    sleep(0x02FFFFFF);
  }while(ch > 0);
}
*/

void kernel_main() {
  print_clear();
  print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
  print_str("Welcome to our 64-bit kernel!");

  //print_newline();

  //test_input();

  GlobalDescriptorTable * gdt = gdt_init();
}