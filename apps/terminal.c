#ifndef TERMINAL_H
#define TERMINAL_H
#define NULL
#include "keyboard.h"
#include "oows.h"
int term_running = 1;
int arcomp(char *array1, char *array2)
{
	int i = 0;
	while (array1[i] != '\0' || array2[i] != '\0') {
		if (array1[i] == array2[i]) {}
		else {
			return 0;
		}
		i++;
	}
	return 1;
}
void run_command(char command[1024]) {
	char command_oows[1024] = "OOWS";
	char command_tstpanic[1024] = "TESTPANIC";
	if (arcomp(command, command_oows)) {
		term_running = 0;
		start_oows();
	}
	else if (arcomp(command, command_tstpanic)) {
		term_running = 0;
		panic("PANIC_TEST");
	}
}
void start_terminal()
{
	//panic("NOT_IMPLEMENTED_YET");
	char ch = 0;
	char keycode = 0;
	char current_char[2];
	char term_buffer[1024];
	print_char('$');
	do {
		keycode = get_input_keycode();
		if (keycode == KEY_ENTER) {
			print_new_line();
			run_command(term_buffer);
			print_new_line();
			if (term_running) {
				print_char('$');
				int i = 0;
				while (term_buffer[i] != '\0') {
					term_buffer[i] = '\0';
					i++;
				}
			}
		} else {
			if (term_running) {
				ch = get_ascii_char(keycode);
				print_char(ch);
				current_char[0] = ch;
				int i = 0, j = 0;
				while (term_buffer[i] != '\0') {
					term_buffer[j] = term_buffer[i];
					i++;
					j++;
				}
				i = 0;
				while (current_char[i] != '\0') {
					term_buffer[j] = current_char[i];
					i++;
					j++;
				}
				term_buffer[j] = '\0';
			}
		}
		sleep(0x05FFFFFF);
	} while(ch > 0 && term_running);
}
#endif
