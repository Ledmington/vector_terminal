#include "../../lib/minunit/minunit.h"

#include <stdbool.h>
#include <string.h>

#include "../input_string.h"
#include "../commands.h"
#include "../parameters.h"

bool test_function(INPUT_STRING* input_str){
	return true;
}

MU_TEST(test_command_queue){
	// check queue is empty
	mu_check(command_set == NULL);
	mu_check(command_set_end == NULL);
	mu_check(NUM_COMMANDS == 0);

	// create command A
	char* name = "A";
	char* desc = "test command";
	char* usage = "A";
	unsigned int minp = 0;
	unsigned int maxp = 2;
	COMMAND* a = add_command(name, desc, usage, minp, maxp, &test_function);
	
	// check command A is in the queue (both start and end)
	mu_check(command_set == a);
	mu_check(command_set_end == a);
	mu_check(NUM_COMMANDS == 1);
	mu_check(search_command(name) != NULL);

	// check fields inside
	mu_check(strcmp(a->name, name) == 0);
	mu_check(strcmp(a->description, desc) == 0);
	mu_check(a->min_params == minp);
	mu_check(a->max_params == maxp);
	mu_check(a->first_param == NULL);
	mu_check(a->last_param == NULL);
	mu_check(a->command_ptr == &test_function);
	mu_check(a->next_cmd == NULL);

	// create command B
	COMMAND* b = add_command("B", "another test command", "some usage", 0, 0, &test_function);

	// check command B is in the queue (at the end)
	mu_check(search_command("B") != NULL);
	mu_check(command_set == a);
	mu_check(command_set_end == b);
	mu_check(NUM_COMMANDS == 2);

	// check command B is after command A
	mu_check(a->next_cmd == b);

	// delete command A
	mu_check(pop_command() == a);
	delete_command(a);

	// check command A is not in the queue
	mu_check(search_command(name) == NULL);

	// check command B is in the queue (both start and end)
	mu_check(search_command("B") != NULL);
	mu_check(command_set == b);
	mu_check(command_set_end == b);
	mu_check(NUM_COMMANDS == 1);

	// delete command B
	mu_check(pop_command() == b);
	delete_command(b);

	// check queue is empty
	mu_check(command_set == NULL);
	mu_check(command_set_end == NULL);
	mu_check(NUM_COMMANDS == 0);
}

MU_TEST(test_parameter_queue){
	// create test command
	COMMAND* c = add_command("A", "test command", "usage", 0, 2, &test_function);

	// check parameter queue is empty
	mu_check(c->first_param == NULL);
	mu_check(c->last_param == NULL);

	// create parameter A
	char* sn = "-a";
	char* ln = "--all";
	char* desc = "test description";
	PARAMETER* p = add_parameter_in(c, false, sn, ln, 0, desc);

	// check parameter A is in the queue (both start and end)
	mu_check(c->first_param == p);
	mu_check(c->last_param == p);
	mu_check(search_parameter(c, sn) == p);

	// check fields inside
	mu_check(p->mandatory == false);
	mu_check(strcmp(p->short_name, sn) == 0);
	mu_check(strcmp(p->long_name, ln) == 0);
	mu_check(p->numbers_required == 0);
	mu_check(strcmp(p->description, desc) == 0);
	mu_check(p->next_param == NULL);

	// create parameter B
	char* bn = "-bb";
	PARAMETER* b = add_parameter_in(c, false, bn, NULL, 0, NULL);

	// check parameter B is in the queue (at the end)
	mu_check(c->last_param == b);
	mu_check(b->next_param == NULL);
	mu_check(search_parameter(c, bn) == b);

	// check parameter B is after command A
	mu_check(p->next_param == b);

	// delete parameter A
	mu_check(pop_parameter(c) == p);
	delete_parameter(p);

	// check parameter A is not in the queue
	mu_check(search_parameter(c, sn) == NULL);

	// check parameter B is in the queue (both start and end)
	mu_check(c->first_param == b);
	mu_check(c->last_param == b);
	mu_check(search_parameter(c, bn) == b);

	// delete parameter B
	mu_check(pop_parameter(c) == b);
	delete_parameter(b);

	// check parameter queue is empty
	mu_check(c->first_param == NULL);
	mu_check(c->last_param == NULL);

	// delete test command
	delete_command(pop_command());
}

MU_TEST_SUITE(test_commands){
	MU_SUITE_CONFIGURE(NULL, &clear_command_set);

	MU_RUN_TEST(test_command_queue);
	MU_RUN_TEST(test_parameter_queue);
}

int main(){

	MU_RUN_SUITE(test_commands);
	MU_REPORT();

	return MU_EXIT_CODE;
}