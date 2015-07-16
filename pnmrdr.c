
#include <stdio.h>
#include <stdbool.h>
#include "assert.h"
#include "mem.h"
#include "pnmrdr.h"
#include "stackoverflow.h"

#define T Pnmrdr_T
struct T {
	Pnmrdr_mapdata data;
	FILE *source;
	const char *plain_format; //for a plain format, format string used to
				  //read a pixel:  %1d for bitmaps; %u for others.
				  //For a raw format, NULL.
	unsigned (*read)(T);      //read next integer
	unsigned ints_left;
	bool got_an_int;
	unsigned bits_left_in_row; //number of bits left in current row
	unsigned char current_byte; //last byte read in raw format
	unsigned char next_bit_mask; //mask of next bit to be read (0 if all bits read)
	};

Pnmrdr_mapdata Pnmrdr_data (T rdr) { return rdr->data;}

static unsigned read_plain(T rdr) {
	unsigned n;
	int rc = fscanf(rdr->source, rdr->plain_format, &n);
	if(rc != 1)
		RAISE(Pnmrdr_Badformat);
	return n;
	}
