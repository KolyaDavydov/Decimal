#include <stdint.h>

#include "s21_decimal.h"

/**
 * @brief Функция преобразования из int в Decimal
 *
 * @param src исходное число int
 *
 * @param dst указатель на число decimal, в которое сохраняем результат
 *
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  memset(&dst->bits, 0, sizeof(dst->bits));

  if (src < 0) {
    setbit(&(dst->bits[3]), 31);
    src = -src;
  }

  dst->bits[0] = src;
  return 0;
}

/**
 * @brief Функция преобразования из float в Decimal
 *
 * @param src исходное число float
 *
 * @param dst указатель на число decimal, в которое сохраняем результат
 *
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  memset(&dst->bits, 0, sizeof(dst->bits));
  if (src < 0) {
    setbit(&(dst->bits[3]), 31);
    src = -src;
  }
  int err = 0;
  if (fabs(src) < 1e-28 || isnan(src) || isinf(src) ||
      fabs(src) > 79228162514264337593543950335.0F) {
    err = 1;
  } else {
    char str_src[100] = {'0'};
    str_src[100] = '\0';
    snprintf(str_src, 100, "%.29f", src);

    int length_str_src = strlen(str_src) - 1;
    // устанавливаем указатель на точку в строке
    char *ptr_to_point = strchr(str_src, '.');
    // считаем коэффициент масштабирования
    if (ptr_to_point != NULL) {
      int pow_of_decimal = 0;
      pow_of_decimal = ptr_to_point - str_src + 1;
      // смещаем точто после точки каждый символ на позицию влево
      for (unsigned int i = pow_of_decimal - 1; i < strlen(str_src); i++)
        str_src[i] = str_src[i + 1];
      pow_of_decimal = strlen(str_src) - pow_of_decimal + 1;
      str_src[length_str_src--] = '\0';
      // rounding_float_seven(str_src, &pow_of_decimal, &err);

      // удаляем все незначащие нули в начале и в конце
      // так же уменьшаем соответственно коэффициент масштабирования
      int val_str = strlen(str_src) - 1;
      while (pow_of_decimal > 0 && val_str > 0 && str_src[val_str] == '0')
        val_str--, pow_of_decimal--;
      str_src[val_str + 1] = '\0';

      int i = 0;
      while (str_src[i] == '0' && str_src[i + 1] != '\0') i++;
      for (unsigned int j = 0; j < strlen(str_src) - i; j++)
        str_src[j] = str_src[j + i];
      str_src[strlen(str_src) - i] = '\0';

      // округляем до семи значащих цифр согласно условию
      rounding_float_seven(str_src, &pow_of_decimal, &err);

      val_str = strlen(str_src) - 1;
      while (pow_of_decimal > 0 && val_str > 0 && str_src[val_str] == '0')
        val_str--, pow_of_decimal--;
      str_src[val_str + 1] = '\0';

      //  printf("строка флофт %s степень %d \n", str_src, pow_of_decimal);
      if (pow_of_decimal) {
        dst->bits[3] ^= (pow_of_decimal << 16);
        // setexp(dst->bits[3], pow_of_decimal);
      }
      // dst->bits[3] ^= (pow_of_decimal << 16);

    } else {
      err = 1;
    }

    str_decimal_to_bit_decimal(dst, str_src);
  }
  return err;
}

/**
 * @brief Функция преобразования из  Decimal в int
 *
 * @param src исходное число Decimal
 *
 * @param dst указатель на число int, в которое сохраняем результат
 *
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  int exp = getexp(src.bits[3]);
  char str_of_int[40] = {0};
  for (int i = 0; i < 39; i++) str_of_int[i] = '0';

  int sign = 0;
  if (getbit(src.bits[3], 31) == 0) {
    sign = 1;
  } else {
    sign = -1;
  }
  // decimal переводим в строку цифр
  decimal_to_str_of_num(src, str_of_int);

  *dst = atoi(str_of_int) * sign;
  int tmp = *dst;
  while (exp > 0) {
    tmp = tmp / 10;
    exp--;
  }
  *dst = tmp;
  if (src.bits[1] > 0 || src.bits[2] > 0) {
    *dst = 0;
    error = 1;
  }
  return error;
}

/**
 * @brief Функция преобразования из  Decimal в float
 *
 * @param src исходное число Decimal
 *
 * @param dst указатель на число float, в которое сохраняем результат
 *
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int err = 0;
  char str_of_int[40] = {0};
  for (int i = 0; i < 39; i++) str_of_int[i] = '0';
  
  // decimal переводим в строку цифр длиной 40 цифр, где в начале будут нули
  decimal_to_str_of_num(src, str_of_int);

  int exp = getexp(src.bits[3]);
  // printf("     float %s exp %d\n", str_of_int, exp);
  // копируем в левую ячейку все что с правад до точки
  for (unsigned int i = 0; i < strlen(str_of_int) - exp - 1; i++)
    str_of_int[i] = str_of_int[i + 1];
  // вставляем точку
  str_of_int[strlen(str_of_int) - exp - 1] = '.';

  // получаем количество нулей в начале строки либо до точки либо до значащих
  // цифр
  int val = strcspn(str_of_int, ".123456789");
  char temp[40] = {0};
  for (int i = 0; i < 39; i++) temp[i] = '0';
  
  snprintf(temp, strlen(&str_of_int[val - 1]) + 1, "%s", &str_of_int[val - 1]);
  *dst = atof(temp);
  if (getbit(src.bits[3], 31)) *dst *= -1;
  if ((fabs(*dst) < 1e-28 && fabs(*dst) > 0) || isinf(*dst))
    err = 1, *dst = 0.0;
  return err;
}
