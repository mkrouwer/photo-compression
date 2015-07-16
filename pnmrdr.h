
#ifndef PNMRDR_INCLUDED
#define PNMRDR_INCLUDED
#include "except.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define T Pnmrdr_T
typedef struct T *T

#undef T
#endif

extern const Except_T Pnmrdr_Badformat; // raised when not a pnm file
extern T pnmrdr_new(FILE *fp); //raises Pnmrdr_Badformat

typedef enum{ Pnmrdr_bit = 1, Pnmrdr_gray = 2, Pnmrdr_rgb = 3 } Pnmrdr_maptype;
typedef struct {
Pnmrdr_maptype type;
unsigned width, height;
unsigned denominator; //(gray & color) used to scale integers to be read
} Pnmrdr_mapdata;
extern char *Pnmrdr_maptype_names[];

char *Pnmrdr_maptype_names[] = { "invalid map type 0", "bitmap", "greymap", "pixmap"};

extern Pnmrdr_mapdata Pnmrdr_data(T rdr);
extern unsigned pnmrdr_get(T rdr)l
extern const Except_T Pnmrdr_Count;
extern void Pnmrdr_free(T *rdr);

