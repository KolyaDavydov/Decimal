#include <string.h>

#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;

  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  char decimal_str_1[117] = {0};
  init_decimal_str(decimal_str_1);
  decimal_to_string(value_1, decimal_str_1);
  int value_1_is_neg = getbit(value_1.bits[3], 31);

  char decimal_str_2[117] = {0};
  init_decimal_str(decimal_str_2);
  decimal_to_string(value_2, decimal_str_2);
  int value_2_is_neg = getbit(value_2.bits[3], 31);

  int biggest = strcmp(decimal_str_1, decimal_str_2);

  char rezult_str[117] = {0};
  init_decimal_str(rezult_str);

  int is_negative = 0;

  if ((biggest > 0 && value_1_is_neg == 0 && value_2_is_neg == 0) ||
      (biggest < 0 && value_1_is_neg == 0 && value_2_is_neg == 0)) {
    add_str(decimal_str_1, decimal_str_2, rezult_str);
  } else if ((biggest > 0 && value_1_is_neg == 1 && value_2_is_neg == 1) ||
             (biggest < 0 && value_1_is_neg == 1 && value_2_is_neg == 1)) {
    add_str(decimal_str_1, decimal_str_2, rezult_str);
    is_negative = 1;
  } else if (biggest > 0 && value_1_is_neg == 0 && value_2_is_neg == 1) {
    sub_str(decimal_str_1, decimal_str_2, rezult_str);
  } else if (biggest < 0 && value_1_is_neg == 0 && value_2_is_neg == 1) {
    sub_str(decimal_str_2, decimal_str_1, rezult_str);
    is_negative = 1;
  } else if (biggest > 0 && value_1_is_neg == 1 && value_2_is_neg == 0) {
    sub_str(decimal_str_1, decimal_str_2, rezult_str);
    is_negative = 1;
  } else if (biggest < 0 && value_1_is_neg == 1 && value_2_is_neg == 0) {
    sub_str(decimal_str_2, decimal_str_1, rezult_str);
  } else if (biggest == 0) {
    if ((value_1_is_neg == 0 && value_2_is_neg == 1) ||
        (value_1_is_neg == 1 && value_2_is_neg == 0)) {
      sub_str(decimal_str_1, decimal_str_2, rezult_str);
    } else if (value_1_is_neg == 0 && value_2_is_neg == 0) {
      add_str(decimal_str_1, decimal_str_2, rezult_str);
    } else if (value_1_is_neg == 1 && value_2_is_neg == 1) {
      add_str(decimal_str_1, decimal_str_2, rezult_str);
      is_negative = 1;
    }
  }
  int too_big = 1;  // если строка-число больше максимальной то отрицательное

  for (int i = 0; i < 29; i++) {
    if (rezult_str[i] != '0') {
      too_big = -1;
      err = -1;
    }
  }
  int exp_rezult = remove_zeroes(rezult_str);

  if (too_big == 1) {
    err = bank_round(rezult_str, &exp_rezult);

    if (err == 0) {
      if (strlen(rezult_str) == 29) {
        too_big = strcmp(MAXDEC, rezult_str);
      }
    }
  }

  if (too_big < 0) {
    err = (is_negative) ? 2 : 1;
  } else {
    str_decimal_to_bit_decimal(result, rezult_str);
    if (is_negative) setbit(&result->bits[3], 31);
    if (exp_rezult) result->bits[3] ^= (exp_rezult << 16);
  }

  return err;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;

  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  char decimal_str_1[117] = {0};
  init_decimal_str(decimal_str_1);
  decimal_to_string(value_1, decimal_str_1);
  int value_1_is_neg = getbit(value_1.bits[3], 31);

  char decimal_str_2[117] = {0};
  init_decimal_str(decimal_str_2);
  decimal_to_string(value_2, decimal_str_2);
  int exp_value_2 = remove_zeroes(decimal_str_2);
  int value_2_is_neg = getbit(value_2.bits[3], 31);

  int is_negative = 0;
  if (value_1_is_neg + value_2_is_neg == 1) is_negative = 1;

  char result_str[117] = {0};
  init_decimal_str(result_str);

  int shift = strlen(decimal_str_2) - exp_value_2 - 1;
  if (shift < 0) {
    for (int i = shift; i < 0; i++) shift_right_decimal_str(decimal_str_1);
  } else if (shift > 0) {
    for (int i = shift; i > 0; i--) shift_left_decimal_str(decimal_str_1);
  }

  for (size_t i = 0; i < strlen(decimal_str_2); i++) {
    for (int digit = decimal_str_2[i] - '0'; digit > 0; digit--) {
      add_str(result_str, decimal_str_1, result_str);
    }
    shift_right_decimal_str(decimal_str_1);
  }

  int too_big = 1;  // если строка-число больше максимальной то отрицательное

  for (int i = 0; i < 29; i++) {
    if (result_str[i] != '0') {
      too_big = -1;
      err = -1;
    }
  }
  int exp_rezult = remove_zeroes(result_str);

  if (too_big == 1) {
    err = bank_round(result_str, &exp_rezult);

    if (err == 0) {
      if (strlen(result_str) == 29) {
        too_big = strcmp(MAXDEC, result_str);
      }
    }
  }

  if (too_big < 0) {
    err = (is_negative) ? 2 : 1;
  } else if (exp_rezult <= 28) {
    str_decimal_to_bit_decimal(result, result_str);
    if (is_negative) setbit(&result->bits[3], 31);
    if (exp_rezult) result->bits[3] ^= (exp_rezult << 16);
  }

  return err;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;

  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  char decimal_str_1[117] = {0};
  init_decimal_str(decimal_str_1);
  decimal_to_string(value_1, decimal_str_1);
  int value_1_is_neg = getbit(value_1.bits[3], 31);

  char decimal_str_2[117] = {0};
  init_decimal_str(decimal_str_2);
  decimal_to_string(value_2, decimal_str_2);
  int value_2_is_neg = getbit(value_2.bits[3], 31);

  int biggest = strcmp(decimal_str_1, decimal_str_2);

  char rezult_str[117] = {0};
  init_decimal_str(rezult_str);

  int is_negative = 0;

  if (biggest > 0 && value_1_is_neg == 0 && value_2_is_neg == 0) {
    sub_str(decimal_str_1, decimal_str_2, rezult_str);
  } else if ((biggest > 0 && value_1_is_neg == 0 && value_2_is_neg == 1) ||
             (biggest < 0 && value_1_is_neg == 0 && value_2_is_neg == 1)) {
    add_str(decimal_str_1, decimal_str_2, rezult_str);
  } else if ((biggest > 0 && value_1_is_neg == 1 && value_2_is_neg == 0) ||
             (biggest < 0 && value_1_is_neg == 1 && value_2_is_neg == 0)) {
    add_str(decimal_str_1, decimal_str_2, rezult_str);
    is_negative = 1;
  } else if (biggest > 0 && value_1_is_neg == 1 && value_2_is_neg == 1) {
    sub_str(decimal_str_1, decimal_str_2, rezult_str);
    is_negative = 1;
  } else if (biggest < 0 && value_1_is_neg == 1 && value_2_is_neg == 1) {
    sub_str(decimal_str_2, decimal_str_1, rezult_str);
  } else if (biggest < 0 && value_1_is_neg == 0 && value_2_is_neg == 0) {
    sub_str(decimal_str_2, decimal_str_1, rezult_str);
    is_negative = 1;
  } else if (biggest == 0) {
    if ((value_1_is_neg == 0 && value_2_is_neg == 0) ||
        (value_1_is_neg == 1 && value_2_is_neg == 1)) {
      sub_str(decimal_str_1, decimal_str_2, rezult_str);
    } else if (value_1_is_neg == 0 && value_2_is_neg == 1) {
      add_str(decimal_str_1, decimal_str_2, rezult_str);
    } else if (value_1_is_neg == 1 && value_2_is_neg == 0) {
      add_str(decimal_str_1, decimal_str_2, rezult_str);
      is_negative = 1;
    }
  }
  int too_big = 1;  // если строка-число больше максимальной то отрицательное

  for (int i = 0; i < 29; i++) {
    if (rezult_str[i] != '0') {
      too_big = -1;
      err = -1;
    }
  }
  int exp_rezult = remove_zeroes(rezult_str);

  if (too_big == 1) {
    err = bank_round(rezult_str, &exp_rezult);

    if (err == 0) {
      if (strlen(rezult_str) == 29) {
        too_big = strcmp(MAXDEC, rezult_str);
      }
    }
  }

  if (too_big < 0) {
    err = (is_negative) ? 2 : 1;
  } else {
    str_decimal_to_bit_decimal(result, rezult_str);
    if (is_negative) setbit(&result->bits[3], 31);
    if (exp_rezult) result->bits[3] ^= (exp_rezult << 16);
  }

  return err;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;

  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  if (is_zero_decimal(value_2) == 1) {
    err = 3;
  } else {
    char decimal_str_1[117] = {0};
    init_decimal_str(decimal_str_1);
    decimal_to_string(value_1, decimal_str_1);
    int value_1_is_neg = getbit(value_1.bits[3], 31);

    char decimal_str_2[117] = {0};
    init_decimal_str(decimal_str_2);
    decimal_to_string(value_2, decimal_str_2);
    int value_2_is_neg = getbit(value_2.bits[3], 31);
    int exp_value_2 = getexp(value_2.bits[3]);

    int is_negative = 0;
    if (value_1_is_neg + value_2_is_neg == 1) is_negative = 1;

    char result_str[117] = {0};
    init_decimal_str(result_str);

    // строка из 116 для временного хранения
    char tmp[117] = {0};
    init_decimal_str(tmp);

    int shift = 0;

    while (exp_value_2 > 0) {
      shift_left_decimal_str(decimal_str_1);
      shift_left_decimal_str(decimal_str_2);
      exp_value_2--;
    }

    strcpy(tmp, decimal_str_1);

    if (strcmp(decimal_str_1, decimal_str_2) > 0) {
      while (strcmp(decimal_str_1, decimal_str_2) >= 0) {
        shift_left_decimal_str(decimal_str_2);
        shift--;
      }
      shift_right_decimal_str(decimal_str_2);
      shift++;
    }

    while (shift <= 29) {
      int count_of_sub = 0;
      while (strcmp(decimal_str_2, tmp) <= 0) {
        sub_str(tmp, decimal_str_2, tmp);
        count_of_sub++;
      }
      result_str[57 + shift] += count_of_sub;

      shift_right_decimal_str(decimal_str_2), shift++;
    }
    int exp_rezult = remove_zeroes(result_str);

    err = bank_round(result_str, &exp_rezult);

    int too_big = 1;  // если строка-число больше максимальной то отрицательное

    if ((int)strlen(result_str) - exp_rezult > 29) {
      too_big = -1;
    } else {
      if (err == 0) {
        if (strlen(result_str) == 29) {
          too_big = strcmp(MAXDEC, result_str);
        }
      }
    }

    if (too_big < 0) {
      err = (is_negative) ? 2 : 1;
    } else if (exp_rezult <= 28) {
      str_decimal_to_bit_decimal(result, result_str);
      if (is_negative) setbit(&result->bits[3], 31);
      if (exp_rezult) result->bits[3] ^= (exp_rezult << 16);
    }
  }
  return err;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  int sign_value_1 = 0;
  int flag = 0;

  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;

  s21_decimal int_dec = {{0, 0, 0, 0}};
  s21_decimal mul_int_dec_val_2 = {{0, 0, 0, 0}};
  s21_decimal mod_dec = {{0, 0, 0, 0}};

  if (getbit(value_1.bits[3], 31) == 1) {
    sign_value_1 = 1;
    unsetbit(&value_1.bits[3], 31);
  }

  if (getbit(value_2.bits[3], 31) == 1) {
    unsetbit(&value_2.bits[3], 31);
  }

  flag = s21_div(value_1, value_2, result);
  if (flag != 0) err = flag;

  s21_truncate(*result, &int_dec);
  s21_mul(int_dec, value_2, &mul_int_dec_val_2);
  s21_sub(value_1, mul_int_dec_val_2, &mod_dec);

  if (flag == 1 && sign_value_1 == 1) flag = 2, err = flag;

  *result = mod_dec;

  if (getexp(result->bits[3]) != 0) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;
  }

  return err;
}
