
#include "assert.h"
#include "bit.h"
#include "bit2.h"
#include "mem.h"
#include "uarray.h"

#define T Bit2_T

struct T {
  int width, height;
  UArray_T rows; // UArray_T of 'height' Bit_Ts, each of length 'width'
   // Element (i, j) in the world of ideas maps to
   //   bit number 'i' in *(Bit_T*)UArray_at(rows, j)
};
#line 51 "www/solutions/bit2.nw"
static inline Bit_T row(T a, int j) {/Users/Margot/Desktop/Comp_40/pnmrdr.c
  return *(Bit_T *)UArray_at(a->rows, j); // cast is Hanson idiom
}
#line 57 "www/solutions/bit2.nw"
static int is_ok(T b) {
  return b && UArray_length(b->rows) == b->height &&
              (b->height == 0 || Bit_length(row(b, 0)) == b->width);
}
#line 130 "www/solutions/bit2.nw"
struct bitcl {
  void (*apply)(int i, int j, T bitmap2, int bit, void *cl); // original apply
  void *cl;   // original cl
  int rownum; // row number of this bitmap
  T bitmap;   // bitmap we're visiting 
};
static void bit_apply(int n, int bit, void *cl) { // apply the original
  struct bitcl *orig = cl; // contains the original 'apply' and 'cl'
  orig->apply(n, orig->rownum, orig->bitmap, bit, orig->cl);
}

T Bit2_new(int width, int height) {
  int i;  /* interates over row number */
  T bitmap;
  NEW(bitmap);
  bitmap->width  = width;
  bitmap->height = height;
  bitmap->rows   = UArray_new(height, sizeof(Bit_T));
  for (i = 0; i < height; i++) {
    Bit_T *element = UArray_at(bitmap->rows, i);
    *element = Bit_new(width);
  }
  assert(is_ok(bitmap));
  return bitmap;
}

void Bit2_free(T *bitmap) {
  int i;
  assert(bitmap && *bitmap);
  for (i = 0; i < (*bitmap)->height; i++) {
    Bit_T p = row(*bitmap, i);
    Bit_free(&p);
  }
  UArray_free(&(*bitmap)->rows);
  FREE(*bitmap);
}

int Bit2_get(T bitmap, int i, int j) {
  assert(bitmap);
  return Bit_get(row(bitmap, j), i);
}
int Bit2_put(T bitmap, int i, int j, int bit) {
  assert(bitmap);
  return Bit_put(row(bitmap, j), i, bit);
}

int Bit2_height(T bitmap) {
        assert(bitmap);
        return bitmap->height;
}
int Bit2_width(T bitmap) {
        assert(bitmap);
        return bitmap->width;
}

void Bit2_map_row_major(T bitmap, 
    void apply(int i, int j, T bitmap, int bit, void *cl), void *cl) {
  assert(bitmap);
  int h = bitmap->height;
  for (int i = 0; i < h; i++) {
    struct bitcl wrapper = { apply, cl, i, bitmap };
    Bit_map(row(bitmap, i), bit_apply, &wrapper);
  }
}

void Bit2_map_col_major(T bitmap, 
    void apply(int i, int j, T bitmap, int bit, void *cl), void *cl) {
  assert(bitmap);
  int h = bitmap->height;
  int w = bitmap->width;
  for (int j = 0; j < w; j++)
    for (int i = 0; i < h; i++)
      apply(i, j, bitmap, Bit_get(row(bitmap, i), j), cl);
}
