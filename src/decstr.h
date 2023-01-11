#ifndef SRC_STR_REPR_H_
#define SRC_STR_REPR_H_

#include <stdlib.h>
#include <string.h>

#define DECSTR_LEN 64

#define SIGN_POS 0
#define SIGN_NEG 1

typedef struct decstr {
  int sign;
  int scale;
  char bytes[DECSTR_LEN + 1];
} decstr_t;

void decstr_init(decstr_t* ds);

void decstr_copy(decstr_t* dest, decstr_t* src);

void decstr_from_str(decstr_t* dest, char* src);

void decstr_rescale(decstr_t* dest, decstr_t* src, int scale);

void rotate_left(decstr_t* dstr, int mid);

void rotate_right(decstr_t* dstr, int mid);

void decstr_add(decstr_t* lhs, decstr_t* rhs, decstr_t* result);

void _add(decstr_t* lhs, decstr_t* rhs, decstr_t* result,
          char (*calc_cb)(char, char, int*));

char sum_cb(char l, char r, int* carry);

char sub_cb(char l, char r, int* carry);

void decstr_truncate(decstr_t* dest, decstr_t* src);

char* decstr_mantissa(decstr_t* dstr);

char* decstr_fraction(decstr_t* dstr);

void decstr_debug(decstr_t* ds);

#endif  // SRC_STR_REPR_H_