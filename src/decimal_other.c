#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  null_result(result);
  if (getbit(value.bits[3], 31)) {
    s21_decimal one = {{1, 0, 0, 0}}, tmp = {{0, 0, 0, 0}};
    setsign(&one.bits[3], 1);

    s21_truncate(value, &tmp);
    s21_add(tmp, one, result);
    setsign(&result->bits[3], 1);
  } else {
    s21_truncate(value, result);
  }

  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  null_result(result);
  int sign = getbit(value.bits[3], 31);
  decstr_t dstr = {0};
  decstr_from_decimal(&dstr, &value);

  if (*decstr_fraction(&dstr) - 48 < 5) {
    s21_truncate(value, result);
  } else {
    s21_decimal one = {{1, 0, 0, 0}}, tmp = {{0, 0, 0, 0}};
    setsign(&value.bits[3], 0);

    s21_truncate(value, &tmp);
    s21_add(tmp, one, result);
    setsign(&result->bits[3], sign);
  }

  return 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  null_result(result);
  decstr_t dstr = {0};
  char bits[100] = {0}, *bits_p = bits;
  bitstr_init(bits_p, '0');

  decstr_from_decimal(&dstr, &value);
  decstr_truncate(&dstr, &dstr);

  bitstr_from_str(bits_p, decstr_mantissa(&dstr));
  bitstr_to_dec(result, bits);

  setsign(&result->bits[3], getbit(value.bits[3], 31));
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  null_result(result);

  setsign(&result->bits[3], !getbit(value.bits[3], 31));

  setexp(&result->bits[3], getexp(value.bits[3]));
  for (int i = 0; i < 3; i++) result->bits[i] = value.bits[i];
  return 0;
}

/**
 * вспомогательные функции размещать в файле decimal_utils
 * необходимо правильно называть вспомогательные функции
 *
 * объявление функций не забывать в в файле s21_decimal.h
 */