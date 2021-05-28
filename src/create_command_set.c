#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "commands.h"
#include "parameters.h"
#include "command_set/command_set.h"
#include "command_set/alias_utils.h" // alias
#include "command_set/csv_utils.h"  // config

void create_command_set() {
    /*
        Each command needs to be saved in memory during all the execution
        with all its possible parameters.
        These commands are pushed into the queue in alphabetical order.
    */

    COMMAND* cmd;

    //add
    cmd = add_command("add", "Adds an element/some elements to an existing array", "add <array> <numbers> [-i index]", 2, UINT_MAX, &add);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the existing array where to add the new element.");
    add_parameter_in(cmd, true, "NEW_ELEMENT(S)", NULL, 0, "The element(s) to be added.");
    add_parameter_in(cmd, false, "-i", "--index", 1, "The index where to add the new element (if the array is too short, it gets resized).");

    //alias
    cmd = add_command("alias", "Lets you define some short strings for longer commands", "alias [<string1> <string2>]", 0, 2, &alias);
    add_parameter_in(cmd, false, "STRING_1", NULL, 0, "The string to be substituted");
    add_parameter_in(cmd, false, "STRING_2", NULL, 0, "The string to substitute");

    //append
    cmd = add_command("append", "Appends the contents of two existing arrays.", "append <arr1> <arr2> [-n]", 2, 4, &append);
    add_parameter_in(cmd, true, "ARRAY_1", NULL, 0, "The name of the first array.");
    add_parameter_in(cmd, true, "ARRAY_2", NULL, 0, "The name of the second array.");
    add_parameter_in(cmd, false, "-n", "--new", 0, "The name of the new array.");

    //csv
    cmd = add_command("csv", "Prints all the Configurable System Variables", "csv [-a]", 0, 1, &csv);
    add_parameter_in(cmd, false, "-a", "--all", 0, "Print all the descriptions.");

    //config
    cmd = add_command("config", "Allows you to change the current value of a CSV.", "config [<csv> [<value> | -d]] [-d -a]", 2, 2, &config);
    add_parameter_in(cmd, true, "CSV_NAME", NULL, 0, "The name or alias of the CSV.");
    add_parameter_in(cmd, false, "NEW_VALUE", NULL, 0, "The new value of the CSV.");
    add_parameter_in(cmd, false, "-d", "--default", 0, "Resets the default value.");
    add_parameter_in(cmd, false, "-a", "--all", 0, "Resets the default value for all CSVs (only if specified after \"-d\".");

    //copy
    cmd = add_command("copy", "Creates a new array copying the content from an existing one.", "copy <old_array> <new_array>", 2, 2, &copy);
    add_parameter_in(cmd, true, "ARRAY_TO_COPY", NULL, 0, "The name of the existing array to copy.");
    add_parameter_in(cmd, true, "NEW_ARRAY", NULL, 0, "The name of the new array.");

    //create
    cmd = add_command("create", "Creates a new array.", "create <array> <size> [-s <value>] [-sf <value> <index>]", 2, UINT_MAX, &create);
    add_parameter_in(cmd, true, "NEW_ARRAY", NULL, 0, "The name of the created array.");
    char* tmp = (char*) calloc(100, sizeof(char));
    strcpy(tmp, "The size of the created array (0<ARRAY_SIZE<");
    char tmp2[10] = {'\0'};
    sprintf(tmp2, "%d", maxarr);
    strcat(tmp, tmp2);
    strcat(tmp, ").");
    add_parameter_in(cmd, true, "ARRAY_SIZE", NULL, 1, tmp);
    free(tmp);
    add_parameter_in(cmd, false, "-s", "--set", 1, "Sets all the elements of the new array to n.");
    add_parameter_in(cmd, false, "-sf", "--set-from", 2, "Sets the elements of the array to the given value from the given index.");

    //destroy
    cmd = add_command("destroy", "Deletes an existing array.", "destroy <array>", 1, 1, &destroy);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the array to be deleted.");

    //delete
    cmd = add_command("delete", "Deletes an element from an existing array and resizes it", "delete <array> [<value> | -i <index>]", 1, 4, &delete);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the existing array where to add the new element.");
    add_parameter_in(cmd, false, "ELEMENT_VALUE", NULL, 0, "The value to search and delete.");
    add_parameter_in(cmd, false, "-i", "--index", 1, "The index where to delete the element (if not specified, the last element is deleted).");

    //find
    cmd = add_command("find", "Finds all the elements that satisfy the specified condition.", "find <array> [-f | -l | -a] [-eq N | -lt N | -gt N]", 3, 4, &find);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the array where to search.");
    add_parameter_in(cmd, false, "-f", "--first", 0, "Prints only the first element found.");
    add_parameter_in(cmd, false, "-l", "--last", 0, "Prints only the last element found.");
    add_parameter_in(cmd, false, "-a", "--all", 0, "Prints all the occurrencies.");
    add_parameter_in(cmd, false, "-eq", "--equal", 1, "Condition satisfied if v[i] = N.");
    add_parameter_in(cmd, false, "-lt", "--lessthan", 1, "Condition satisfied if v[i] < N.");
    add_parameter_in(cmd, false, "-gt", "--greaterthan", 1, "Condition satisfied if v[i] > N.");

    //for
    cmd = add_command("for", "Allows you to execute the same command more times in a row.", "for <iterations> <command>", 2, UINT_MAX, &for_exec);
    add_parameter_in(cmd, true, "NUM_ITERATIONS", NULL, 0, "The number of times to execute the given command.");
    add_parameter_in(cmd, true, "COMMAND", NULL, 0, "The command to be executed.");

    //help
    cmd = add_command("help", "Prints useful informations.", "help [<command>] [-s]", 0, 2, &help);
    add_parameter_in(cmd, false, "(none)", NULL, 0, "Prints all the command set with all parameters.");
    add_parameter_in(cmd, false, "COMMAND", NULL, 0, "Prints the description of the command and of all its parameters.");
    add_parameter_in(cmd, false, "-s", "--short", 0, "Prints just the description.");

    //history
    cmd = add_command("history", "Prints a list of all commands sent since this program started.", "history [<number>]", 0, 1, &history);
    add_parameter_in(cmd, false, "COMMAND_NUMBER", NULL, 1, "The number of the command you want to execute.");

    //list
    cmd = add_command("list", "Prints the list of all created arrays.", "list [-a | -d] [-alp | -s]", 0, 2, &list);
    add_parameter_in(cmd, false, "-a", "--ascending", 0, "Sorts the arrays in ascending order.");
    add_parameter_in(cmd, false, "-d", "--descending", 0, "Sorts the arrays in descending order.");
    add_parameter_in(cmd, false, "-alp", "--alphabetical", 0, "Sorts the arrays based on their names.");
    add_parameter_in(cmd, false, "-s", "--size", 0, "Sorts the arrays based on their size.");

    //print
    cmd = add_command("print", "Prints all the elements in a certain range of the specified array.", "print <array> [-i] [-r <start> <end>] [-s]", 1, 6, &print);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the array to print.");
    add_parameter_in(cmd, false, "-i", "--index", 0, "Prints the index of each element.");
    add_parameter_in(cmd, false, "-r", "--range", 2, "Prints only the elements v[i] such that A<=i<=B.");

    //quit
    cmd = add_command("quit", "Closes Vector Terminal.", "quit", 0, 0, &quit);

    //read
    cmd = add_command("read", "Reads commands from an input file. If not specified, it is DEFAULT_INPUT_FILE.", "read [<file>]", 0, 1, &read);
    add_parameter_in(cmd, false, "FILE_NAME", NULL, 0, "The name of the input file, extension is added automatically.");

    //set
    cmd = add_command("set", "Changes the value(s) of some element(s) in an existing array.", "set <array> <numbers> -i <index>", 4, UINT_MAX, &set_values);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the existing array where to change the value.");
    add_parameter_in(cmd, true, "NEW_ELEMENT(S)", NULL, 0, "The new value(s) to be set.");
    add_parameter_in(cmd, true, "-i", "--index", 1, "The starting index where to change values.");

    //sort
    cmd = add_command("sort", "Sorts the given array in the specified order.", "sort <array> [-a | -d]", 1, 2, &sort);
    add_parameter_in(cmd, true, "ARRAY_NAME", NULL, 0, "The name of the existing array to be sorted.");
    add_parameter_in(cmd, false, "-a", "--ascending", 0, "Sorts in ascending order (default).");
    add_parameter_in(cmd, false, "-d", "--descending", 0, "Sorts in descending order.");

    //version
    cmd = add_command("version", "Shows the version number of the terminal.", "version", 0, 0, &version);

    //unalias
    cmd = add_command("unalias", "Lets you undefine an already existing alias", "unalias <alias>", 1, 1, &unalias);
    add_parameter_in(cmd, true, "STRING", NULL, 0, "The alias to be undefined");
}