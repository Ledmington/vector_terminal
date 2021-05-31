#include "../../lib/minunit/minunit.h"

#include <stdio.h>

#include "../api.h"
#include "../input_string_utils.h"
#include "../error.h"
#include "../commands.h"
#include "../command_set/command_set.h"
#include "../command_set/csv_utils.h"

INPUT_STRING* in;
ARRAY* arr;

MU_TEST(correct_create) {
	in = set_command_line("create arr 5");
	mu_check(create(in));
	mu_check(error == no_error);
	arr = search_array("arr");
	mu_check(arr != NULL);
	mu_check(strcmp(arr->name, "arr") == 0);
	mu_check(arr->size == 5);
	for(unsigned int i=0; i<arr->size; i++) {
		mu_check(arr->ptr[i] == 0);
	}
	free_input_string(in);
	in = set_command_line("destroy arr");
	destroy(in);
	free_input_string(in);
}

MU_TEST(correct_destroy) {
	in = set_command_line("create arr 5");
	create(in);
	free_input_string(in);

	// Destroy an existing array
	in = set_command_line("destroy arr");
	mu_check(destroy(in));
	mu_check(error == no_error);
	free_input_string(in);
}

MU_TEST(wrong_create) {
	in = set_command_line("create arr 5");
	create(in);
	free_input_string(in);

	// Create an array with the same name of an already existing one
	in = set_command_line("create arr 10");
	mu_check(create(in) == false);
	mu_check(error == array_already_existing);
	free_input_string(in);
	in = set_command_line("destroy arr");
	destroy(in);
	free_input_string(in);

	// Create an array with invalid name
	in = set_command_line("create arr2 5");
	mu_check(create(in) == false);
	mu_check(error == invalid_name);
	free_input_string(in);

	// Create an array with invalid size (overflow or 0)
	in = set_command_line("create arr 0");
	mu_check(create(in) == false);
	mu_check(error == conversion_failed);
	free_input_string(in);
	in = set_command_line("create arr 99999999999999999");
	mu_check(create(in) == false);
	mu_check(error == overflow_detected);
	free_input_string(in);

	// Create an array with size > max_array_size
	char str[20];
	sprintf(str, "create arr %u", maxarr+1);
	in = set_command_line(str);
	mu_check(create(in) == false);
	mu_check(error == array_size_too_big);
	free_input_string(in);

	// Create an array with unexisting parameter
	in = set_command_line("create arr 5 -a 2");
	mu_check(create(in) == false);
	mu_check(error == parameter_not_found);
	free_input_string(in);

	// Create an array with parameter but without a following number
	in = set_command_line("create arr 5 -s");
	mu_check(create(in) == false);
	mu_check(error == number_needed);
	free_input_string(in);

	// Create an array with parameter and invalid number
	in = set_command_line("create arr 5 -s 654a");
	mu_check(create(in) == false);
	mu_check(error == conversion_failed);
	free_input_string(in);
}

MU_TEST(wrong_destroy) {
	// Destroy a nonexisting array
	in = set_command_line("destroy arr");
	mu_check(destroy(in) == false);
	mu_check(error = array_not_found);
	free_input_string(in);
}

MU_TEST(borderline_correct_create) {
	unsigned int size=20, value=2, index=10, new_value=1, last_value=4;
	char cmd[50];

	// create arr 20 -s 2 -sf 10 1
	sprintf(cmd, "create arr %u -s %u -sf %u %u", size, value, new_value, index);
	in = set_command_line(cmd);
	mu_check(create(in));
	mu_check(error == no_error);
	arr = search_array("arr");
	mu_check(arr != NULL);
	mu_check(arr->size = size);
	for (unsigned int i=0; i<index; i++) {
		mu_check(arr->ptr[i] == value);
	}
	for (unsigned int i=index; i<size; i++) {
		mu_check(arr->ptr[i] == new_value);
	}
	free_input_string(in);
	in = set_command_line("destroy arr");
	destroy(in);
	free_input_string(in);
	free_array(arr);

	// create arr 20 -s 2 -sf 10 1 -s 4
	sprintf(cmd, "create arr %u -s %u -sf %u %u -s %u", size, value, new_value, index, last_value);
	in = set_command_line(cmd);
	mu_check(create(in));
	mu_check(error == no_error);
	arr = search_array("arr");
	mu_check(arr != NULL);
	mu_check(arr->size = size);
	for (unsigned int i=0; i<size; i++) {
		mu_check(arr->ptr[i] == last_value);
	}
	free_input_string(in);
	in = set_command_line("destroy arr");
	destroy(in);
	free_input_string(in);
	free_array(arr);
}

MU_TEST(array_stack) {
	// stack empty
	mu_check(array_list == NULL);

	// searching "arr" or "vec" must be false
	mu_check(search_array("arr") == NULL);
	mu_check(error == array_not_found);
	mu_check(search_array("vec") == NULL);
	mu_check(error == array_not_found);

	// add "arr"
	in = set_command_line("create arr 5");
	mu_check(create(in));
	free_input_string(in);
	mu_check(error == no_error);

	// searching "arr" must be true
	arr = search_array("arr");
	mu_check(arr != NULL);
	mu_check(error == array_already_existing);

	// now stack is {"arr"}
	mu_check(array_list == arr);
	mu_check(arr->next_array == NULL);

	// add "vec"
	in = set_command_line("create vec 5");
	mu_check(create(in));
	free_input_string(in);
	mu_check(error == no_error);

	// searching "vec" must be true
	arr = search_array("vec");
	mu_check(arr != NULL);
	mu_check(error == array_already_existing);

	// now stack is {"vec", "arr"}
	mu_check(array_list == arr);
	mu_check(arr->next_array != NULL);

	// destroy "arr"
	in = set_command_line("destroy arr");
	mu_check(destroy(in));
	free_input_string(in);
	mu_check(error == no_error);

	// searching "arr" must be false
	mu_check(search_array("arr") == NULL);
	mu_check(error == array_not_found);

	// now stack is {"vec"}
	mu_check(array_list == arr);
	mu_check(arr->next_array == NULL);

	// destroy "vec"
	in = set_command_line("destroy vec");
	mu_check(destroy(in));
	free_input_string(in);
	mu_check(error == no_error);

	// stack empty
	mu_check(array_list == NULL);
}

MU_TEST_SUITE(test_create) {
	MU_SUITE_CONFIGURE(&VT_start, &VT_end);

	MU_RUN_TEST(correct_create);
	MU_RUN_TEST(correct_destroy);
	MU_RUN_TEST(wrong_create);
	MU_RUN_TEST(wrong_destroy);
	MU_RUN_TEST(borderline_correct_create);
	MU_RUN_TEST(array_stack);
}

int main ( void ) {
	
	MU_RUN_SUITE(test_create);
	MU_REPORT();

	return MU_EXIT_CODE;
}