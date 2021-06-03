#include "../../lib/minunit/minunit.h"

#include <string.h>

#include "../api.h"
#include "../input_string_utils.h"
#include "../error.h"
#include "../command_set/history.h"

INPUT_STRING* in;
char* version_cmd = "version";
char* example_cmd = "list";

MU_TEST(empty_history){
	mu_check(error == no_error);
	mu_check(history_first == NULL);
	mu_check(history_last == NULL);

	// when starting the terminal, there should be only the command "version"
	VT_start();
	mu_check(history_first == history_last);
	mu_check(!strcmp(history_first->command_string, version_cmd));
	VT_end();
}

MU_TEST(correct_params){
	VT_start();
	input(example_cmd);
	mu_check(!strcmp(example_cmd, history_last->command_string));
	in = set_command_line("history 1");
	mu_check(history(in));
	mu_check(!strcmp(version_cmd, history_last->command_string));
	in = set_command_line("history 2");
	mu_check(history(in));
	mu_check(!strcmp(example_cmd, history_last->command_string));
	VT_end();
}

MU_TEST(wrong_params){
	VT_start();
	in = set_command_line("history a");
	mu_check(!history(in));
	VT_end();
}

MU_TEST(incognito_mode){
	VT_start();
	mu_check(!strcmp(version_cmd, history_last->command_string));
	input("config -d -a");
	input("config save false");
	input("config hist false");
	input(example_cmd);
	mu_check(strcmp(version_cmd, history_last->command_string));
	input("config hist true");
	mu_check(strcmp(version_cmd, history_last->command_string));
	VT_end();
}

MU_TEST_SUITE(test_history){
	MU_RUN_TEST(empty_history);
	MU_RUN_TEST(correct_params);
	MU_RUN_TEST(wrong_params);
	MU_RUN_TEST(incognito_mode);
}

int main(void){

	MU_RUN_SUITE(test_history);
	MU_REPORT();

	return MU_EXIT_CODE;
}