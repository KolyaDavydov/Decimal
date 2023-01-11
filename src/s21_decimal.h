#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decstr.h"

#define OK 0
#define FALSE 0
#define TRUE 1
#define MAXINT 2147483647
#define MAXBITS 4294967295U
#define MAXDEC "79228162514264337593543950335"

#define BITSTR_LEN (int)((sizeof(int) * 8) * 3)  // 96
#define BITSTR_ONE                                                             \
  "00000000000000000000000000000000000000000000000000000000000000000000000000" \
  "0000000000000000000001"
#define EXP_MASK 0b00000000111111110000000000000000

typedef struct {
  int bits[4];
} s21_decimal;

/* ===== Arithmetic operations ===== */

int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal* result);  // ГОТОВ

int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal* result);  // ГОТОВ

int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal* result);  // ГОТОВ

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

/* ===== Comparison operations ===== */

int s21_is_less(s21_decimal value_1, s21_decimal value_2);  // ГОТОВ

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);  // ГОТОВ

int s21_is_greater(s21_decimal value_1, s21_decimal value_2);  // ГОТОВ

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);  // ГОТОВ

int s21_is_equal(s21_decimal value_1, s21_decimal value_2);  // ГОТОВ

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);  // ГОТОВ

/* ===== Convertors and parsers ===== */

int s21_from_int_to_decimal(int src, s21_decimal* dst);  // ГОТОВ

int s21_from_float_to_decimal(float src, s21_decimal* dst);  // ГОТОВ

int s21_from_decimal_to_int(s21_decimal src, int* dst);  // ГОТОВ

int s21_from_decimal_to_float(s21_decimal src, float* dst);  // ГОТОВ

/* ===== Other functions ===== */

int s21_floor(s21_decimal value, s21_decimal* result);

int s21_round(s21_decimal value, s21_decimal* result);

int s21_truncate(s21_decimal value, s21_decimal* result);

int s21_negate(s21_decimal value, s21_decimal* result);

/* ===== ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ===== */

/**
 * объявление вспомогательных функции
 * необходимо правильно называть вспомогательные функции
 */

int getbit(int val, int bit);

void setbit(int* val, int bit);

void unsetbit(int* val, int bit);

void invertbit(int* val, int bit);

void setsign(int* val, int sign);

int getexp(int val);

void setexp(int* val, int exp);

void bitstr_init(char* bstr, char with);

void bitstr_from_char(char* dest, char ch);

void bitstr_from_str(char* dest, char* src_radix_10);

int filter_non_digit(char* dest, char* src);

void dec_to_bitstr(char* dest, s21_decimal* dcl);

void bitstr_to_dec(s21_decimal* dest, const char* bstr);

void bitstr_shift(char* bstr, int offset);

void bitstr_invert(char* bstr, int up_to);

int bitstr_msbi(char* bstr);

void bitstr_add(const char* bstr1, const char* bstr2, char* res);

void bitstr_add_upto(const char* bstr1, const char* bstr2, int up_to,
                     char* res);

void bitstr_multen(char* bstr, int exp);

void wbits(char** dest, const size_t size, const void* ptr);

void print_bin(const size_t size, const void* ptr);

void print_highest_bits(int* bits);

void print_debug(s21_decimal* decimal);

void str_decimal_to_bit_decimal(s21_decimal* dst, char* buffer);

void rounding_float_seven(char* str_src, int* pow_of_decimal, int* err);

void decstr_from_decimal(decstr_t* dest, s21_decimal* src);

void decimal_to_str_of_num(const s21_decimal src, char* buffer);

void decimal_to_string(s21_decimal dec, char* strdec);
void init_decimal_str(char* decimal_str);
void add_str(const char* str_1, const char* str_2, char* rezult);
void sub_str(const char* str_1, const char* str_2, char* rezult);
int remove_zeroes(char* str_dec);
int bank_round(char* str_dec, int* exp);
int is_zero_decimal(s21_decimal dec);

void shift_right_decimal_str(char* str);
void shift_left_decimal_str(char* str);
void null_result(s21_decimal* result);

#endif  // SRC_S21_DECIMAL_H_