#include "kernel.h"
#include "utils.h"
#include "char.h"

uint32 vga_index;
static uint32 next_line_index = 1;
uint8 g_fore_color = WHITE, g_back_color = BLUE;
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
	uint16 ax = 0;
	uint8 ah = 0, al = 0;

	ah = back_color;
	ah <<= 4;
	ah |= fore_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
	uint32 i;
	for (i = 0; i < BUFSIZE; i++) {
		(*buffer)[i] = vga_entry(NULL, fore_color, back_color);
	}
	next_line_index = 1;
	vga_index = 0;
}

void init_vga(uint8 fore_color, uint8 back_color)
{
	vga_buffer = (uint16*)VGA_ADDRESS;
	clear_vga_buffer(&vga_buffer, fore_color, back_color);
	g_fore_color = fore_color;
	g_back_color = back_color;
}

void print_new_line()
{
	if (next_line_index >= 55) {
		next_line_index = 0;
		clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
	}
	vga_index = 80*next_line_index;
	next_line_index++;
}

void print_char(char ch)
{
	vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
	vga_index++;
}

void print_string(char *str)
{
	uint32 index = 0;
	while (str[index]) {
		print_char(str[index]);
		index++;
	}
}

void print_int(int num)
{
	char str_num[digit_count(num)+1];
	itoa(num, str_num);
	print_string(str_num);
}

uint8 inb(uint16 port)
{
	uint8 ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
	return ret;
}

void outb(uint16 port, uint8 data)
{
	asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

char get_input_keycode()
{
	char ch = 0;
	while ((ch = inb(KEYBOARD_PORT)) != 0) {
		if(ch > 0) {
			return ch;
		}
	}
	return ch;
}

void wait_for_io(uint32 timer_count)
{
	while(1) {
		asm volatile("nop");
		timer_count--;
		if (timer_count <= 0) {
			break;
		}
	}
}

void sleep(uint32 timer_count)
{
	wait_for_io(timer_count);
}

//void keyboard_test()
//{
//	char ch = 0;
//	char keycode = 0;
//	do {
//		keycode = get_input_keycode();
//		if (keycode == KEY_ENTER) {
//			print_new_line();
//		} else {
//			ch = get_ascii_char(keycode);
//			print_char(ch);
//		}
//		sleep(0x02FFFFFF);
//	} while(ch > 0);
//}
void confidential_msg() {
	print_string("           OPENOS RB2");
	print_new_line();
	print_new_line();
	print_string("    CODENAME REDSTONE BETA 2");
	print_new_line();
	print_string("CONFIDENTIAL TO THE BETA TESTERS");
	print_new_line();
	print_string("   OPEN OS KERNAL VERSION 0.5");
	print_new_line();
	print_string("THIS IS OPEN SOURCE AND DO NOT ABUSE IT.");
	print_new_line();
	print_string("PRESS ANY KEY TO CONTINUE");
	print_new_line();
}
void panic(char* error_code) {
	init_vga(WHITE, BLUE);
	print_string("--------------------------OPENOS CRASH--------------------------");
	print_new_line();
	print_string("A problem has occurred and OpenOS has stopped to prevent");
	print_new_line();
	print_string("corruption and other problems. The reason why it crashed");
	print_new_line();
	print_string("might have to do with your drivers or kernal. DO NOT");
	print_new_line();
	print_string("RESTART. The error code provided by the kernel is:");
	print_new_line();
	print_string(error_code);
	print_new_line();
	print_string("-------------------DO NOT RESTART UNTIL SAFE TO-----------------");
	print_new_line();
}

void kernel_entry() //When the kernel starts up
{
	init_vga(WHITE, BLACK);
	confidential_msg();
	get_input_keycode();
	init_vga(WHITE, BLACK);
	panic("PANIC_TEST"); //Kernel panic test
}
