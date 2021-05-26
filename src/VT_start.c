#include "api.h"
#include "command_set/csv_utils.h"
#include "command_set/alias_utils.h"
#include "commands.h"

void VT_start() {
    //This is the first function to be called in this program

    //TODO: change structure to optimize this process
    //hint: avoid calling two times update_all_csv
    create_csv_list();
    update_all_csv();
    load_all_csv();
    update_all_csv();

    create_alias_list();

    create_command_set();

    input("version");
}