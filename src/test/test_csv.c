#include "../../lib/minunit/minunit.h"

#include <stdio.h>

#include "../command_set/csv_utils.h"

MU_TEST(csv_input){
	char* n = "name_example";
	char* sn = "short_name_example";
	char* d = "description example";
	char* v = "new value";
	char* p = "*";
	VALUE tmp;
	VALUE_INFO vi;

	// Check full input (correct)
	tmp.s = v;
	vi.pattern = p;
	mu_check(add_csv(n, sn, d, STRING, tmp, &vi) != NULL);

	// Check without name
	mu_check(add_csv(NULL, sn, d, STRING, tmp, &vi) == NULL);
	mu_check(add_csv("", sn, d, STRING, tmp, &vi) == NULL);

	// Check without short_name
	mu_check(add_csv(n, NULL, d, STRING, tmp, &vi) == NULL);
	mu_check(add_csv(n, "", d, STRING, tmp, &vi) == NULL);

	// Check without description
	mu_check(add_csv(n, sn, NULL, STRING, tmp, &vi) == NULL);
	mu_check(add_csv(n, sn, "", STRING, tmp, &vi) == NULL);

	// Check with type STRING and without value
	tmp.s = NULL;
	mu_check(add_csv(n, sn, d, STRING, tmp, &vi) == NULL);
	tmp.s = v;

	// Check without pattern
	mu_check(add_csv(n, sn, d, STRING, tmp, NULL) == NULL);
	vi.pattern = NULL;
	mu_check(add_csv(n, sn, "", STRING, tmp, &vi) == NULL);

	free_all_csv();
}

MU_TEST(csv_stack){
	char* n = "name_example";
	char* sn = "short_name_example";
	char* d = "description example";
	char* v = "new value";
	char* p = "*";
	VALUE tmp;
	VALUE_INFO vi;
	tmp.s = v;
	vi.pattern = p;

	mu_check(csv_list == NULL);

	CSV* csv = add_csv(n, sn, d, STRING, tmp, &vi);
	mu_check(csv != NULL);
	mu_check(csv_list == csv);

	mu_check(csv == pop_csv());
	mu_check(csv_list == NULL);

	free_all_csv();
}

MU_TEST_SUITE(test_csv){
	MU_RUN_TEST(csv_input);
	MU_RUN_TEST(csv_stack);
}

int main(){

	MU_RUN_SUITE(test_csv);
	MU_REPORT();

	return MU_EXIT_CODE;
}