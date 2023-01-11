#include "s21_decimal.h"

/**
 * Здесь размещать дополнительные функции
 * которые используются для написания основных
 *
 * ВАЖНО!!!!!!
 * дополнительные обязательно начинать с префикса!!
 * префикс выглядит следующим образом:
 * например вы хотите назвать функцию "set_bit(...){}"
 * если вы разрабатываете функции в 'decimal_arithmetic'
 * то все ваши функции следует начинать с префикса "ari_"
 * и таким образом ваша функция будет называться
 * "ari_set_bit(...){}"
 * если будете разрабатывать функционал для "decimal_comparicon"
 * то функция будет называться "com_set_bit(...){}"
 */

/**
 * @brief Возвращает значение бита по заданной позиции (0 или 1)
 *
 * @param val Переменная, из которой будет считан бит
 *
 * @param bit Номер нужного бита
 *
 * @returns int в значении 0 или 1
 */
int getbit(int val, int bit) { return (val >> bit) & 1; }

/**
 * @brief Выставляет значение бита в еденицу по заданной позиции
 *
 * @param val Переменная, над которой будет происходить операция
 *
 * @param bit Номер нужного бита
 */
void setbit(int* val, int bit) { *val |= (1 << bit); }

/**
 * @brief Выставляет значение бита в ноль по заданной позиции
 *
 * @param val Переменная, над которой будет происходить операция
 *
 * @param bit Номер нужного бита
 */
void unsetbit(int* val, int bit) { *val &= ~(1 << bit); }

/**
 * @brief Задает знак числа структуры s21_decimal
 *
 * @param val Последний элемент массива bits структуры s21_decimal
 *
 * @param sign Выставляемый знак (0 или 1)
 */
void setsign(int* val, int sign) { sign ? setbit(val, 31) : unsetbit(val, 31); }

/**
 * @brief Возвращает знак числа структуры s21_decimal
 *
 * @param val Последний элемент массива bits структуры s21_decimal
 *
 * @returns Знак числа (0 или 1)
 */
int getexp(int val) {
  int exp = val & EXP_MASK;
  return exp >> 16;
}

/**
 * @brief Выставляет экспоненту числа структуры s21_decimal
 *
 * @param val Последний элемент массива bits структуры s21_decimal
 *
 * @param exp Значение экпоненты (0..28)
 */
void setexp(int* val, int exp) {
  int sign = getbit(*val, 31);
  *val = exp << 16;
  setsign(val, sign);
}

/**
 * @brief Инициализирует буфер бит-строки с переданным символом
 *
 * @param bstr Указатель на буфер (размер не менее 97 символов)
 *
 * @param with Символ, которым будет заполнена бит-строка
 */
void bitstr_init(char* bstr, char with) {
  for (int k = 0; k < BITSTR_LEN; k++) bstr[k] = with;
}

void bitstr_from_char(char* dest, char ch) {
  if (dest != NULL) {
    char ch_bits[9] = {0}, *ch_bits_p = ch_bits;
    bitstr_init(dest, '0');

    char digit = ch - 48;
    wbits(&ch_bits_p, sizeof(char), &digit);
    int idx = 0;
    for (int i = BITSTR_LEN - 8; i <= BITSTR_LEN; i++) dest[i] = ch_bits[idx++];
  }
}

void bitstr_from_str(char* dest, char* src_radix_10) {
  if (dest != NULL && src_radix_10 != NULL) {
    // int src_len = strlen(src_radix_10);

    char filtered[BITSTR_LEN + 1] = {0};
    int filtered_len = filter_non_digit(filtered, src_radix_10);

    for (int i = 0; i < filtered_len; i++) {
      char bstr[100] = {0}, *bstr_p = bstr, tmp[100] = {0}, *tmp_p = tmp;
      bitstr_init(tmp_p, '0');
      bitstr_from_char(bstr_p, filtered[i]);
      bitstr_add(dest, bstr_p, tmp_p);

      if (i < filtered_len - 1) {
        bitstr_multen(tmp_p, 1);
      }

      strcpy(dest, tmp);
    }
  }
}

int filter_non_digit(char* dest, char* src) {
  int filtered_len = 0;
  if (dest != NULL && src != NULL) {
    for (int i = 0; i < (int)strlen(src); i++)
      if (src[i] >= '0' && src[i] <= '9') dest[filtered_len++] = src[i];
  }

  return filtered_len;
}

/**
 * @brief Конвертирует строку в структуру s21_decimal
 *
 * @param dest Указатель на результирующую структуру s21_decimal
 *
 * @param bstr Указатель на исходный буфер (размер не менее 97 символов)
 */
void bitstr_to_dec(s21_decimal* dest, const char* bstr) {
  memset(&dest->bits, 0, sizeof(dest->bits));
  int index = BITSTR_LEN - 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      int bit = bstr[index--] - 48;
      if (bit) setbit(&dest->bits[i], j);
    }
  }
}

/**
 * @brief Эквивалент оператора '<<' для бит-строки
 *
 * @param dest Указатель на исходный буфер (размер не менее 97 символов)
 *
 * @param offset Размер сдвига
 */
void bitstr_shift(char* bstr, int offset) {
  for (int i = 0; i < offset; i++) {
    for (int k = 0; k < (int)BITSTR_LEN - 1; k++) bstr[k] = bstr[k + 1];
    bstr[BITSTR_LEN - 1] = '0';
  }
}

/**
 * @brief Сложение бит-строк
 *
 * @param bstr1 Указатель на первый буфер (размер не менее 97 символов)
 *
 * @param bstr2 Указатель на второй буфер (размер не менее 97 символов)
 *
 * @param res Указатель на результирующий буфер (размер не менее 97 символов)
 */
void bitstr_add(const char* bstr1, const char* bstr2, char* res) {
  int carry = 0;
  for (int i = (int)BITSTR_LEN - 1; i >= 0; i--) {
    int bit_v1 = bstr1[i] - 48, bit_v2 = bstr2[i] - 48;
    if (bit_v1 ^ bit_v2 ^ carry) {
      res[i] = '1';
      if (bit_v1 + bit_v2 + carry < 3) carry = 0;
    } else if (bit_v1 && bit_v2) {
      carry = 1;
    }
  }
}

/**
 * @brief Эквивалент функции 'pow()' для бит-строки
 *
 * @param bstr Указатель на исходный буфер (размер не менее 97 символов)
 *
 * @param exp Степень
 */
void bitstr_multen(char* bstr, int exp) {
  int ten = 10;
  char res[100] = {0};
  bitstr_init(res, '0');
  for (int i = 0; i < exp - 1; i++) ten *= 10;

  for (int i = 0; i < 31; i++) {
    if (getbit(ten, i)) {
      char mask[100] = {0}, tmp[100] = {0};
      bitstr_init(tmp, '0');
      strcpy(mask, bstr);
      bitstr_shift(mask, i);
      bitstr_add(res, mask, tmp);
      strcpy(res, tmp);
    }
  }

  strcpy(bstr, res);
}

// for s21_from_float_to_decimal

void rounding_float_seven(char* str_src, int* pow_of_decimal, int* err) {
  int lenstr = strlen(str_src);

  if (*pow_of_decimal - lenstr <= 28 && lenstr - *pow_of_decimal <= 29) {
    if (*pow_of_decimal > 28)
      lenstr -= *pow_of_decimal - 28, *pow_of_decimal = 28;
    if (lenstr > 29) *pow_of_decimal -= lenstr - 29, lenstr = 29;
    if (lenstr > 0 && *pow_of_decimal >= 0) {
      if (lenstr > 7) {
        for (int i = 8; i < (int)strlen(str_src); i++) str_src[i] = '0';

        if (*pow_of_decimal - lenstr + 7 > 0) {
          *pow_of_decimal = *pow_of_decimal - lenstr + 7;
        } else
          *pow_of_decimal = 0;
        lenstr = 7;
      }

      if (str_src[lenstr] >= '5') {
        if (str_src[lenstr - 1] == '9') {
          str_src[lenstr] = '\0';
          lenstr--;
          while (str_src[lenstr] == '9' && lenstr > 0) str_src[lenstr--] = '0';
          if (lenstr == 0 && str_src[lenstr] == '9') {
            str_src[0] = '0';
            for (int j = strlen(str_src); j >= 0; j--)
              str_src[j + 1] = str_src[j];
            str_src[0] = '1';
            lenstr++;
          } else {
            str_src[lenstr]++;
            lenstr++;
          }
        } else {
          str_src[lenstr - 1]++, str_src[lenstr] = '0';
        }
        int val_str = strlen(str_src) - 1;

        if (val_str <= *pow_of_decimal) {
          while ((*pow_of_decimal) > 0 && val_str > 0 &&
                 str_src[val_str] == '0')
            val_str--, (*pow_of_decimal)--;
        }
        str_src[val_str + 1] = '\0';
      }

      if (*pow_of_decimal > 0 || lenstr == 29) str_src[lenstr] = '\0';
    }
    if (*pow_of_decimal <= 0) {
      lenstr -= *pow_of_decimal, *pow_of_decimal = 0;
      if (lenstr > 29) *err = 1;
    }

  } else {
    *err = 1;
  }
}

// преобразует строку с десятичными цифрами в decimal
void str_decimal_to_bit_decimal(s21_decimal* dst, char* str_dec) {
  int bit = 0;
  while (strcspn(str_dec, "123456789") != strlen(str_dec)) {
    int bit_value = 0;
    for (unsigned int j = 0; j < strlen(str_dec); j++) {
      int q = 0;
      if (bit_value == 1) q = 10;
      bit_value = ((str_dec[j] - '0') + q) % 2;
      str_dec[j] = (((str_dec[j] - '0') + q) / 2) + '0';
    }

    if (bit_value) setbit(&dst->bits[bit / 32], bit);
    bit++;
  }
}

/**
 * @brief Записывает в строку побитовое представление любого типа кроме float
 *
 * @param dest Двойной указатель на результирующий буфер (размер не менее 97
 * символов)
 *
 * @param size Размер типа передаваемого значения
 *
 * @param ptr Указатель на конвертируемое значение
 */
void wbits(char** dest, const size_t size, const void* ptr) {
  unsigned char* b = (unsigned char*)ptr;
  int index = 0;

  for (int i = size - 1; i >= 0; i--)
    for (int j = 7; j >= 0; j--) (*dest)[index++] = (b[i] >> j) & 1 ? '1' : '0';
}

/* преобразует decimal в строку цифр */
void decimal_to_str_of_num(const s21_decimal src, char* str_of_int) {
  int bit = 2;  // какой из src.bits[]
  // двигаемся от самого старшего бита к самому младшему
  // и если бит == 1 то прибавляем один к последней цифре
  for (int j = 31; bit >= 0; j--) {
    // двигаемся с конца строки с цифрами
    // когда цифра больше 9 то в младший разряд прибавляем 1
    for (int i = 40 - 2, one = 0; i > 0; i--) {
      int temp = (str_of_int[i] - '0') * 2 + one;
      one = (temp > 9) ? 1 : 0;
      if (temp > 9) temp -= 10;
      str_of_int[i] = temp + '0';
    }
    str_of_int[40 - 2] =
        ((str_of_int[40 - 2] - '0') + getbit(src.bits[bit], j)) + '0';
    if (j == 0) j = 32, bit--;
  }
}

/**
 * @brief преобразование из s21_decimal в строку десятичных цифр
 *
 * @param dec decimal который преобразуем в десятичную строку
 *
 * @param strdec строка длиной 116 символов, куда записываются десятичные
 * цифры, точка (масштабирование) рвно по середине
 */

void decimal_to_string(s21_decimal dec, char* strdec) {
  int bit = 2;  // какой из src.bits[]
  for (int j = 31; bit >= 0; j--) {
    // двигаемся с конца строки с цифрами
    // когда цифра больше 9 то в младший разряд прибавляем 1
    for (int i = 117 - 2, one = 0; i > 0; i--) {
      int temp = (strdec[i] - '0') * 2 + one;
      one = (temp > 9) ? 1 : 0;
      if (temp > 9) temp -= 10;
      strdec[i] = temp + '0';
    }
    strdec[117 - 2] =
        ((strdec[117 - 2] - '0') + getbit(dec.bits[bit], j)) + '0';
    if (j == 0) {
      j = 32, bit--;
    }
  }
  int exp = getexp(dec.bits[3]);
  for (int i = 0; i < 116 / 2 - exp; i++) {
    strdec[116 / 2 - i - 1] = strdec[116 - exp - i - 1];
    strdec[116 - exp - i - 1] = '0';
  }
  int ex = exp;
  for (int i = 0; i < exp; i++) {
    strdec[116 / 2 + i] = strdec[116 - ex];
    strdec[116 - ex] = '0';
    ex--;
  }
}

/**
 * @brief заполняет строку 116 символов нулями
 *
 * @param decimal_str строку длиной 116 символов заполняет нулями
 */
void init_decimal_str(char* decimal_str) {
  for (int i = 0; i < 117; i++) decimal_str[i] = i < 116 ? '0' : '\0';
}

/**
 * @brief складывает число-строку длиной 116
 *
 * @param str_1 первое слагаемое-строка десятичных цифр
 *
 * @param str_2 второе слагаемое-строка десятичных цифр
 *
 * @param rezult сумма в виде строки-числа из десятичных цифр
 */
void add_str(const char* str_1, const char* str_2, char* rezult) {
  for (int i = 116 - 1, buf = 0; i >= 0; i--) {
    if (str_1[i] != '0' || str_2[i] != '0' || buf != 0) {
      int temp = (str_1[i] - '0') + buf + (str_2[i] - '0');
      buf = (temp >= 10) ? 1 : 0;
      if (temp >= 10) temp -= 10;
      rezult[i] = temp + '0';
    }
  }
}

/**
 * @brief вычитает число-строку длиной 116
 *
 * @param str_1 первое слагаемое-строка десятичных цифр
 *
 * @param str_2 второе слагаемое-строка десятичных цифр
 *
 * @param rezult разность в виде строки-числа из десятичных цифр
 */
void sub_str(const char* str_1, const char* str_2, char* rezult) {
  for (int i = 116 - 1, buf = 0; i >= 0; i--) {
    if (str_1[i] != '0' || str_2[i] != '0' || buf != 0) {
      int temp = (str_1[i] - '0') - buf - (str_2[i] - '0');
      buf = (temp < 0) ? 1 : 0;
      if (temp < 0) temp += 10;
      rezult[i] = temp + '0';
    }
  }
}

/**
 * @brief удаляет из строки-числа концевые и начальные незначащие нули
 * одновременно степень не может быть больше 28
 *
 * @param str_dec строка-число длиной 116 символов с нулями в начале и в конце
 *
 * @returns коэффицикнт масштабирования
 */
// int remove_zeroes(char *str_dec) {
//   int exp = 58;
//   int len_str_dec = strlen(str_dec) - 1;
//   while(exp > 0 && str_dec[len_str_dec] == '0') {
//     len_str_dec--;
//     exp--;
//   }
//   str_dec[len_str_dec + 1] = '\0';

//   int i = 0;
//   while (str_dec[i] == '0' && str_dec[i + 1] != '\0')
//     i++;

//   for (unsigned int j = 0; j < strlen(str_dec) - 1; j++)
//     str_dec[j] = str_dec[j + i];
//   str_dec[strlen(str_dec)] = '\0';

//   return exp;
// }

int remove_zeroes(char* str_dec) {
  int exp = 58;
  int len_str_dec = strlen(str_dec) - 1;

  while (exp > 28) {
    len_str_dec--;
    exp--;
  }

  if (exp == 28) {
    if ((str_dec[len_str_dec + 1] == '5' && str_dec[len_str_dec] % 2 == 1) ||
        str_dec[len_str_dec + 1] > '5')
      str_dec[len_str_dec]++;
  }

  while (exp > 0 && str_dec[len_str_dec] == '0') {
    len_str_dec--;
    exp--;
  }

  str_dec[len_str_dec + 1] = '\0';

  int i = 0;
  while (str_dec[i] == '0' && str_dec[i + 1] != '\0') i++;

  for (unsigned int j = 0; j < strlen(str_dec) - 1; j++)
    str_dec[j] = str_dec[j + i];
  str_dec[strlen(str_dec)] = '\0';

  return exp;
}

/**
 * @brief банковское округление числа строки
 *
 * @param str_dec строка-число длиной без незначащих нулей
 *
 * @param exp коэффициент масштабирования
 *
 * @returns номер ошибки
 */
int bank_round(char* str_dec, int* exp) {
  int err = 0;
  // printf("strdec %s\n", str_dec);
  if (strlen(str_dec) > 29) {
    if ((str_dec[29] == '5' && str_dec[28] % 2 == 1) || str_dec[29] > '5') {
      str_dec[28]++;
    }
    *exp = *exp - (strlen(str_dec) - 29);
    str_dec[29] = '\0';
  }
  return err;
}

/**
 * @brief смещение "ненулевых" на одну позицию вправо
 *
 * @param str строка десятичных цифр длинной 116 с нулями вначале и в конце
 */
void shift_right_decimal_str(char* str) {
  for (size_t i = strlen(str); i > 3; i--) {
    str[i - 1] = str[i - 2];
  }
}

/**
 * @brief смещение "ненулевых" на одну позицию влево
 *
 * @param str строка десятичных цифр длинной 116 с нулями вначале и в конце
 */
void shift_left_decimal_str(char* str) {
  for (size_t i = 0; i < strlen(str) - 2; i++) {
    str[i] = str[i + 1];
  }
}

/**
 * @brief равняется ли децимал нулю
 *
 * @param dec s21_decimal который определяем на ноль
 *
 * @returns возвращает 1 если децимал = -0 или 0
 */
int is_zero_decimal(s21_decimal dec) {
  int is_zero = 0;
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) is_zero = 1;
  return is_zero;
}

void null_result(s21_decimal* result) {
  result->bits[0] = 0;
  result->bits[1] = 0;
  result->bits[2] = 0;
  result->bits[3] = 0;
}