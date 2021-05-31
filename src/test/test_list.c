#include "../../lib/minunit/minunit.h"

#include "../api.h"
#include "../input_string_utils.h"
#include "../error.h"
#include "../command_set/command_set.h"

INPUT_STRING* in;

MU_TEST(empty_list){
	mu_check(error == no_error);
	in = set_command_line("list");
	mu_check(list(in));
	mu_check(error == no_error);
}

MU_TEST(correct_params){
	mu_check(error == no_error);

	create(set_command_line("create aaa 5"));
	create(set_command_line("create bbb 20"));
	create(set_command_line("create ccc 10"));
	mu_check(error == no_error);

	in = set_command_line("list -a");
	mu_check(list(in));
	mu_check(error == no_error);

	in = set_command_line("list -d");
	mu_check(list(in));
	mu_check(error == no_error);

	in = set_command_line("list -alp");
	mu_check(list(in));
	mu_check(error == no_error);

	in = set_command_line("list -s");
	mu_check(list(in));
	mu_check(error == no_error);

	in = set_command_line("list *");
	mu_check(list(in));
	mu_check(error == no_error);

	in = set_command_line("list *a*");
	mu_check(list(in));
	mu_check(error == no_error);
}

MU_TEST(wrong_params){
	mu_check(error == no_error);

	create(set_command_line("create aaa 5"));
	create(set_command_line("create bbb 20"));
	create(set_command_line("create ccc 10"));
	mu_check(error == no_error);

	in = set_command_line("list -a -d");
	mu_check(!list(in));
	mu_check(error == invalid_ordering);

	in = set_command_line("list -d -a");
	mu_check(!list(in));
	mu_check(error == invalid_ordering);

	in = set_command_line("list -alp -s");
	mu_check(!list(in));
	mu_check(error == invalid_ordering);

	in = set_command_line("list -s -alp");
	mu_check(!list(in));
	mu_check(error == invalid_ordering);

	in = set_command_line("list a a");
	mu_check(!list(in));
	mu_check(error == too_many_parameters);
}

MU_TEST_SUITE(test_list){
	MU_SUITE_CONFIGURE(&VT_start, &VT_end);

	MU_RUN_TEST(empty_list);
	MU_RUN_TEST(correct_params);
	MU_RUN_TEST(wrong_params);
}

int main(void){

	MU_RUN_SUITE(test_list);
	MU_REPORT();

	return MU_EXIT_CODE;
}