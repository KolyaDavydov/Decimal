#include "s21_decimal.h"

void decstr_init(decstr_t* ds) {
  if (ds != NULL) {
    memset(ds, 0, sizeof(decstr_t));

    ds->sign = SIGN_POS;
    ds->scale = 0;
    memset(&ds->bytes, 48, sizeof(char) * DECSTR_LEN);
  }
}

void decstr_copy(decstr_t* dest, decstr_t* src) {
  if (dest != NULL && src != NULL) {
    dest->sign = src->sign;
    dest->scale = src->scale;
    for (int i = 0; i <= DECSTR_LEN; i++) dest->bytes[i] = src->bytes[i];
  }
}

void decstr_from_decimal(decstr_t* dest, s21_decimal* src) {
  if (dest != NULL && src != NULL) {
    decstr_init(dest);
    int idx = 0;

    for (int i = 0; i < 3; i++) {
      for (int bit = 0; bit < 32; bit++) {
        if (getbit(src->bits[i], bit)) {
          decstr_t pow_of_two = {0};
          decstr_from_str(&pow_of_two, "1");

          for (int k = 0; k < idx; k++)
            decstr_add(&pow_of_two, &pow_of_two, &pow_of_two);

          decstr_add(dest, &pow_of_two, dest);
        }

        idx++;
      }
    }

    if (getbit(src->bits[3], 31))
      dest->sign = SIGN_NEG;
    else
      dest->sign = SIGN_POS;

    dest->scale = getexp(src->bits[3]);
  }
}

void decstr_from_str(decstr_t* dest, char* src) {
  if (dest != NULL && src != NULL) {
    // int src_len = strlen(src);
    decstr_init(dest);

    char* point_p = strchr(src, '.');
    if (point_p != NULL) {
      char filtered_fractional[DECSTR_LEN + 1] = {0};
      dest->scale = filter_non_digit(filtered_fractional, point_p + 1);
    }

    if (*src == '-') dest->sign = SIGN_NEG;

    char filtered[DECSTR_LEN + 1] = {0};
    int filtered_len = filter_non_digit(filtered, src);

    if (filtered_len == DECSTR_LEN) {
      for (int i = 0; i <= DECSTR_LEN; i++) dest->bytes[i] = filtered[i];
    } else if (filtered_len < DECSTR_LEN) {
      int diff = DECSTR_LEN - filtered_len;
      for (int i = 0; i <= filtered_len; i++)
        dest->bytes[i + diff] = filtered[i];
    }
  }
}

void decstr_rescale(decstr_t* dest, decstr_t* src, int scale) {
  if (scale < 0 && dest != NULL && src != NULL) {
    decstr_copy(dest, src);
    rotate_right(dest, -scale);
    if (dest->scale > 0) dest->scale -= -scale;
  }
}

void rotate_right(decstr_t* dstr, int mid) {
  for (int i = 0; i < mid && dstr != NULL; i++) {
    for (int k = DECSTR_LEN - 1; k > 0; k--)
      dstr->bytes[k] = dstr->bytes[k - 1];
    dstr->bytes[0] = '0';
  }
}

void decstr_add(decstr_t* lhs, decstr_t* rhs, decstr_t* result) {
  if (lhs != NULL && rhs != NULL && result != NULL)
    _add(lhs, rhs, result, sum_cb);
}

void _add(decstr_t* lhs, decstr_t* rhs, decstr_t* result,
          char (*calc_cb)(char, char, int*)) {
  if (lhs != NULL && rhs != NULL && result != NULL) {
    int carry = 0;
    decstr_t left = {0}, right = {0};
    decstr_copy(&left, lhs);
    decstr_copy(&right, rhs);

    if (left.scale < right.scale)
      decstr_rescale(&left, &left, right.scale - left.scale);
    else if (left.scale > right.scale)
      decstr_rescale(&right, &right, left.scale - right.scale);

    // debug_print(&left);
    // debug_print(&right);

    // if (strcmp(left.bytes, right.bytes) < 0) result->sign = SIGN_NEG;

    result->scale = left.scale;

    for (int i = DECSTR_LEN - 1; i >= 0; i--)
      result->bytes[i] =
          calc_cb(left.bytes[i] - 48, right.bytes[i] - 48, &carry);
  }
}

char sum_cb(char l, char r, int* carry) {
  char sum = l + r + *carry;

  if (*carry > 0) (*carry)--;

  if (sum >= 10) {
    (*carry)++;
    sum -= 10;
  }

  return sum + 48;
}

char* decstr_mantissa(decstr_t* dstr) {
  int offset = 0;
  if (dstr != NULL) {
    for (; offset <= DECSTR_LEN && *(dstr->bytes + offset) == '0'; offset++)
      ;
  }

  return offset == DECSTR_LEN ? (dstr->bytes + 63) : dstr->bytes + offset;
}

char* decstr_fraction(decstr_t* dstr) {
  return dstr->scale ? decstr_mantissa(dstr) + strlen(decstr_mantissa(dstr)) -
                           dstr->scale
                     : decstr_mantissa(dstr);
}

void decstr_truncate(decstr_t* dest, decstr_t* src) {
  if (dest != NULL && src != NULL && src->scale > 0) {
    decstr_rescale(dest, src, -src->scale);
  }
}
