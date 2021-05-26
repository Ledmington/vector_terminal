#ifndef OUT_BUFFER_H_INCLUDED
#define OUT_BUFFER_H_INCLUDED

typedef struct out_buff {
	char* message;
	struct out_buff* next;
} out_buffer;

#endif // OUT_BUFFER_H_INCLUDED