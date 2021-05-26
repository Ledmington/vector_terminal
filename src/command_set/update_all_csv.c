#include "csv_utils.h"
#include "../utils.h"

void update_all_csv(){
	//Function to be called at the very start of each call to 'input'
	//Updates the values of every CSV

	save = search_csv("save")->actual_value.b;

	csvfile = new_string(search_csv("csvfile")->actual_value.s);

	cout = search_csv("cout")->actual_value.b;

	fout = new_string(search_csv("fout")->actual_value.s);

	fin = new_string(search_csv("fin")->actual_value.s);

	sep = new_string(search_csv("sep")->actual_value.s);

	illchar = new_string(search_csv("illchar")->actual_value.s);

	upall = search_csv("upall")->actual_value.b;

	maxin = search_csv("maxin")->actual_value.x;

	maxarr = search_csv("maxarr")->actual_value.x;

	maxdep = search_csv("maxdep")->actual_value.x;

	hist = search_csv("hist")->actual_value.b;

	histal = search_csv("histal")->actual_value.b;

	maxdiff = search_csv("maxdiff")->actual_value.x;

	linestart = new_string(search_csv("linestart")->actual_value.s);
}