#include "kernel.h"
#include "terminal.h"
void kernel_entry() //When the kernel starts up
{
	init_vga(WHITE, BLACK);
	startup_msg();
	get_input_keycode();
	init_vga(WHITE, BLACK);
	print_string("Starting up OpenOS RB2...");
	print_new_line();
	sleep(0x0FFFFFFF);
	start_terminal();
	//sleep(0x0FFFFFFF);
	//panic("PANIC_TEST"); //Kernel panic test
}

