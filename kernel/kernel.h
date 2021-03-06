#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"
#include "keyboard.h"
#include "utils.h"
#include "char.h"

#define NULL 0

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

enum vga_color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	GREY,
	DARK_GREY,
	BRIGHT_BLUE,
	BRIGHT_GREEN,
	BRIGHT_CYAN,
	BRIGHT_RED,
	BRIGHT_MAGENTA,
	YELLOW,
	WHITE,
};
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
void startup_msg() {
	print_string("             R B 2");
	print_new_line();
	print_new_line();
	print_string("THIS BUILD IS A BETA SO");
	print_new_line();
	print_string("IT IS KNOWN TO NOT BE");
	print_new_line();
	print_string("COMPLETE AND STABLE.");
	print_new_line();
	print_string("NEW FEATURES COMING SOON");
	print_new_line();
	print_string("PRESS ANY KEY TO CONTINUE");
	print_new_line();
}
void panic(char* error_code) {
	init_vga(WHITE, BLUE);
	print_string("--------------------------OpenOS crash--------------------------");
	print_new_line();
	print_string("A problem has occurred and OpenOS has stopped to prevent");
	print_new_line();
	print_string("corruption and other problems. The reasons why it crashed");
	print_new_line();
	print_string("might have to do with your drivers or the kernel.");
	print_new_line();
	print_string("The error code provided by the kernel is: ");
	print_string(error_code);
	print_new_line();
	print_string("-----------------------------------------------------------------");
	print_new_line();
}
#endif
