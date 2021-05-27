#pragma once

typedef struct out_buff {

	// Message to be printed
	char* message;

	// Pointer to the next buffer
	struct out_buff* next;

} out_buffer;