#include "s21_decimal.h"

/**
 * @brief Сравнение двух чисел Decimal
 *
 * @param val_1 первое число
 *
 * @param val_2 второе число
 *
 * @return 0 - FALSE, 1 - TRUE (value_1 меньше value_2)
 */
int s21_is_less(s21_decimal val_1, s21_decimal val_2) {
  int ret = 0;

  char decimal_str_1[117] = {0};
  init_decimal_str(decimal_str_1);
  decimal_to_string(val_1, decimal_str_1);
  int val_1_is_neg = getbit(val_1.bits[3], 31);

  char decimal_str_2[117] = {0};
  init_decimal_str(decimal_str_2);
  decimal_to_string(val_2, decimal_str_2);
  int val_2_is_neg = getbit(val_2.bits[3], 31);

  if (is_zero_decimal(val_1) == 1 && is_zero_decimal(val_2) == 1) {
    ret = 0;
  } else if (val_1_is_neg + val_2_is_neg == 1) {
    ret = val_1_is_neg == 1 ? 1 : 0;
  } else if (val_1_is_neg == 0 && val_2_is_neg == 0) {
    ret = strcmp(decimal_str_2, decimal_str_1);
  } else if (val_1_is_neg == 1 && val_2_is_neg == 1) {
    ret = strcmp(decimal_str_1, decimal_str_2);
  }

  ret = ret > 0 ? 1 : 0;

  return ret;
}

/**
 * @brief Сравнение двух чисел Decimal
 *
 * @param val_1 первое число
 *
 * @param val_2 второе число
 *
 * @return 0 - FALSE, 1 - TRUE (value_1 меньше или равно value_2)
 */
int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2) {
  return (s21_is_less(val_1, val_2) || s21_is_equal(val_1, val_2));
}

/**
 * @brief Сравнение двух чисел Decimal
 *
 * @param val_1 первое число
 *
 * @param val_2 второе число
 *
 * @return 0 - FALSE, 1 - TRUE (value_1 больше value_2)
 */
int s21_is_greater(s21_decimal val_1, s21_decimal val_2) {
  int ret = 0;

  char decimal_str_1[117] = {0};
  init_decimal_str(decimal_str_1);
  decimal_to_string(val_1, decimal_str_1);
  int val_1_is_neg = getbit(val_1.bits[3], 31);

  char decimal_str_2[117] = {0};
  init_decimal_str(decimal_str_2);
  decimal_to_string(val_2, decimal_str_2);
  int val_2_is_neg = getbit(val_2.bits[3], 31);

  if (is_zero_decimal(val_1) == 1 && is_zero_decimal(val_2) == 1) {
    ret = 0;
  } else if (val_1_is_neg + val_2_is_neg == 1) {
    ret = val_1_is_neg == 1 ? 0 : 1;
  } else if (val_1_is_neg == 0 && val_2_is_neg == 0) {
    if (strcmp(decimal_str_1, decimal_str_2) > 0) ret = 1;
  } else if (val_1_is_neg == 1 && val_2_is_neg == 1) {
    if (strcmp(decimal_str_2, decimal_str_1) > 0) ret = 1;
  }

  return ret;
}

/**
 * @brief Сравнение двух чисел Decimal
 *
 * @param val_1 первое число
 *
 * @param val_2 второе число
 *
 * @return 0 - FALSE, 1 - TRUE (value_1 больше или равно value_2)
 */
int s21_is_greater_or_equal(s21_decimal val_1, s21_decimal val_2) {
  return (s21_is_greater(val_1, val_2) || s21_is_equal(val_1, val_2));
}

/**
 * @brief Сравнение двух чисел Decimal
 *
 * @param val_1 первое число
 *
 * @param val_2 второе число
 *
 * @return 0 - FALSE, 1 - TRUE (value_1 равен value_2)
 */
int s21_is_equal(s21_decimal val_1, s21_decimal val_2) {
  int ret = 0;

  char decimal_str_1[117] = {0};
  init_decimal_str(decimal_str_1);
  decimal_to_string(val_1, decimal_str_1);
  int val_1_is_neg = getbit(val_1.bits[3], 31);

  char decimal_str_2[117] = {0};
  init_decimal_str(decimal_str_2);
  decimal_to_string(val_2, decimal_str_2);
  int val_2_is_neg = getbit(val_2.bits[3], 31);

  if (is_zero_decimal(val_1) == 1 && is_zero_decimal(val_2) == 1) {
    ret = 1;
  } else if (val_1_is_neg + val_2_is_neg == 1) {
    ret = 0;
  } else {
    if (strcmp(decimal_str_2, decimal_str_1) == 0) ret = 1;
  }

  return ret;
}

/**
 * @brief Сравнение двух чисел Decimal
 *
 * @param val_1 первое число
 *
 * @param val_2 второе число
 *
 * @return 0 - FALSE, 1 - TRUE (value_1 не равны value_2)
 */
int s21_is_not_equal(s21_decimal val_1, s21_decimal val_2) {
  int ret = 0;
  if (s21_is_equal(val_1, val_2) == 0) ret = 1;

  return ret;
}

/**
 * вспомогательные функции размещать в файле decimal_utils
 * необходимо правильно называть вспомогательные функции
 *
 * объявление функций не забывать в в файле s21_decimal.h
 */