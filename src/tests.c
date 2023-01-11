#include <check.h>

#include "s21_decimal.h"

// <=== TEST CASES: s21_from_int_to_decimal ===>

START_TEST(tc_int_to_decimal_1) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int num = 10;
  s21_from_int_to_decimal(num, &dec_1);

  dec_2.bits[0] = 0b00000000000000000000000000001010;
  dec_2.bits[1] = 0;
  dec_2.bits[2] = 0;
  dec_2.bits[3] = 0;

  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(tc_int_to_decimal_2) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int num = 4535435;
  s21_from_int_to_decimal(num, &dec_1);

  dec_2.bits[0] = 0b00000000010001010011010010001011;
  dec_2.bits[1] = 0;
  dec_2.bits[2] = 0;
  dec_2.bits[3] = 0;

  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(tc_int_to_decimal_3) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int num = -4535435;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &dec_1), 0);

  dec_2.bits[0] = 0b00000000010001010011010010001011;
  dec_2.bits[1] = 0;
  dec_2.bits[2] = 0;
  dec_2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(tc_int_to_decimal_4) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int num = MAXINT;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &dec_1), 0);

  dec_2.bits[0] = 0b01111111111111111111111111111111;
  dec_2.bits[1] = 0;
  dec_2.bits[2] = 0;
  dec_2.bits[3] = 0;

  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(tc_int_to_decimal_5) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int num = -MAXINT;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &dec_1), 0);

  dec_2.bits[0] = 0b01111111111111111111111111111111;
  dec_2.bits[1] = 0;
  dec_2.bits[2] = 0;
  dec_2.bits[3] = 0b10000000000000000000000000000000;

  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

START_TEST(tc_int_to_decimal_6) {
  s21_decimal dec_1 = {0}, dec_2 = {0};
  int num = 0;
  ck_assert_int_eq(s21_from_int_to_decimal(num, &dec_1), 0);

  dec_2.bits[0] = 0;
  dec_2.bits[1] = 0;
  dec_2.bits[2] = 0;
  dec_2.bits[3] = 0;

  ck_assert_int_eq(dec_1.bits[0], dec_2.bits[0]);
  ck_assert_int_eq(dec_1.bits[1], dec_2.bits[1]);
  ck_assert_int_eq(dec_1.bits[2], dec_2.bits[2]);
  ck_assert_int_eq(dec_1.bits[3], dec_2.bits[3]);
}
END_TEST

// <=== TEST CASES: s21_float_to_decimal ===>

START_TEST(tc_float_to_decimal_1) {
  s21_decimal dec = {0};
  float fl = 0.03f;
  s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 3);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0b00000000000000100000000000000000);
}
END_TEST

START_TEST(tc_float_to_decimal_2) {
  s21_decimal dec = {0};
  float fl = -3.0f;
  s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 3);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq((unsigned int)dec.bits[3],
                   0b10000000000000000000000000000000);
}
END_TEST

START_TEST(tc_float_to_decimal_3) {
  s21_decimal dec = {0};
  float fl = 3.0f;
  s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 3);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(tc_float_to_decimal_4) {
  s21_decimal dec = {0};
  float fl = 0.0f;
  s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(tc_float_to_decimal_5) {
  s21_decimal dec = {0};
  float fl = 1e-29f;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(tc_float_to_decimal_6) {
  s21_decimal dec = {0};
  float fl = 123456789.123456789F;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 123456800);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_float_to_decimal_7) {
  s21_decimal dec = {0};
  float fl = 1.234567e-28F;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 1835008U);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_float_to_decimal_8) {
  s21_decimal dec = {0};
  float fl = 1e-28f;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 1);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0b00000000000111000000000000000000);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_float_to_decimal_9) {
  s21_decimal dec = {0};
  float fl = NAN;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(tc_float_to_decimal_10) {
  s21_decimal dec = {0};
  float fl = -5454.354F;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 5454354);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq((unsigned)dec.bits[3], 0b10000000000000110000000000000000);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_float_to_decimal_11) {
  s21_decimal dec = {0};
  float fl = 10000000000.000000001F;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 0b01010100000010111110010000000000);
  ck_assert_int_eq(dec.bits[1], 0b00000000000000000000000000000010);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
  ck_assert_int_eq(error, 0);
}

START_TEST(tc_float_to_decimal_12) {
  s21_decimal dec = {0};
  float fl = 79328162514264337593543950335.0F;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(tc_float_to_decimal_13) {
  s21_decimal dec = {0};
  float fl = 7.961328E+08F;
  int error = s21_from_float_to_decimal(fl, &dec);
  ck_assert_int_eq(dec.bits[0], 796132800);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(dec.bits[3], 0);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_float_to_decimal_14) {
  s21_decimal val = {0};
  s21_from_float_to_decimal(0.03F, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0b00000000000000100000000000000000);

  s21_from_float_to_decimal(-0.03F, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000000100000000000000000);

  s21_from_float_to_decimal(3.0F, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_float_to_decimal(-3.0F, &val);
  ck_assert_int_eq(val.bits[0], 3);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000000000000000000000000);

  s21_from_float_to_decimal(0.0F, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_float_to_decimal(10.5F, &val);
  ck_assert_int_eq(val.bits[0], 105);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 65536);

  int err = s21_from_float_to_decimal(1e-29F, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(err, 1);

  err = s21_from_float_to_decimal(NAN, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(err, 1);

  err = s21_from_float_to_decimal(-1.0F / 0.0F, &val);
  ck_assert_int_eq(err, 1);

  err = s21_from_float_to_decimal(1.0F / 0.0F, &val);
  ck_assert_int_eq(err, 1);

  err = s21_from_float_to_decimal(1.234567e-28F, &val);
  ck_assert_int_eq(val.bits[0], 1);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 1835008U);
  ck_assert_int_eq(err, 0);

  s21_from_float_to_decimal(1.02E+09F, &val);
  ck_assert_int_eq(val.bits[0], 1020000000);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  err = s21_from_float_to_decimal(1.0F / 0.0F, &val);
  ck_assert_int_eq(err, 1);

  err = s21_from_float_to_decimal(-1.0F / 0.0F, &val);
  ck_assert_int_eq(err, 1);

  float vall = NAN;
  s21_from_float_to_decimal(vall, &val);
  ck_assert_int_eq(err, 1);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  float x = 0.0;
  s21_from_float_to_decimal(x, &val);
  ck_assert_int_eq(val.bits[0], 0);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  err = s21_from_float_to_decimal(123456789.123456789F, &val);
  ck_assert_int_eq(val.bits[0], 123456800);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(err, 0);

  s21_from_float_to_decimal(0.000000002F, &val);
  ck_assert_int_eq(val.bits[0], 2);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0b00000000000010010000000000000000);

  err = s21_from_float_to_decimal(10000000000.000000001F, &val);
  ck_assert_int_eq(val.bits[0], 0b01010100000010111110010000000000);
  ck_assert_int_eq(val.bits[1], 0b00000000000000000000000000000010);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);
  ck_assert_int_eq(err, 0);

  s21_from_float_to_decimal(-5454.353F, &val);
  ck_assert_int_eq(val.bits[0], 5454353);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000000110000000000000000);

  s21_from_float_to_decimal(-5.492654F, &val);
  ck_assert_int_eq(val.bits[0], 5492654);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000001100000000000000000);

  s21_from_float_to_decimal(7.961328E+08F, &val);
  ck_assert_int_eq(val.bits[0], 796132800);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq(val.bits[3], 0);

  s21_from_float_to_decimal(-1.234568E+07F, &val);
  ck_assert_int_eq(val.bits[0], 12345680);
  ck_assert_int_eq(val.bits[1], 0);
  ck_assert_int_eq(val.bits[2], 0);
  ck_assert_int_eq((unsigned)val.bits[3], 0b10000000000000000000000000000000);
}
END_TEST

// <=== TEST CASES: s21_from_decimal_to_int ===>

START_TEST(tc_decimal_to_int_1) {
  s21_decimal dec = {0};
  int num = 10;
  int result = 0;
  dec.bits[0] = 0b00000000000000000000000000001010;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  int error = s21_from_decimal_to_int(dec, &result);
  ck_assert_int_eq(num, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_int_2) {
  s21_decimal dec = {0};
  int num = -1234567;
  int result = 0;
  dec.bits[0] = 1234567;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000000000000000000000;
  ;
  int error = s21_from_decimal_to_int(dec, &result);
  ck_assert_int_eq(num, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_int_3) {
  s21_decimal dec = {0};
  int num = -MAXINT;
  int result = 0;
  dec.bits[0] = MAXINT;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000000000000000000000;
  ;
  int error = s21_from_decimal_to_int(dec, &result);
  ck_assert_int_eq(num, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_int_4) {
  s21_decimal dec = {0};
  int result = 0;
  dec.bits[0] = 0;
  dec.bits[1] = 0;
  dec.bits[2] = 1;
  dec.bits[3] = 0b10000000000000000000000000000000;
  int error = s21_from_decimal_to_int(dec, &result);

  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(tc_decimal_to_int_5) {
  s21_decimal dec = {0};
  s21_from_float_to_decimal(-7.1f, &dec);
  int num = -7;
  int result = 0;
  int error = s21_from_decimal_to_int(dec, &result);
  ck_assert_int_eq(num, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

// <=== TEST CASES: s21_from_decimal_to_float ===>

START_TEST(tc_decimal_to_float_1) {
  s21_decimal dec = {0};
  float num = 12.12;
  float result = 0;
  dec.bits[0] = 1212;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b00000000000000100000000000000000;
  int error = s21_from_decimal_to_float(dec, &result);
  ck_assert_ldouble_eq_tol(num, result, 1e-28);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_float_2) {
  s21_decimal dec = {0};
  float num = -0.03f;
  float result = 0;
  dec.bits[0] = 3;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000100000000000000000;
  int error = s21_from_decimal_to_float(dec, &result);
  ck_assert_ldouble_eq_tol(num, result, 1e-28);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_float_3) {
  s21_decimal dec = {0};
  float num = 12345.6789;
  float result = 0;
  dec.bits[0] = 123456789;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  setexp(&dec.bits[3], 4);
  int error = s21_from_decimal_to_float(dec, &result);
  ck_assert_float_eq(num, result);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_float_4) {
  s21_decimal dec = {0};
  float num = -18446744073709551615.0f;
  float result = 0;
  dec.bits[0] = 0b11111111111111111111111111111111;
  dec.bits[1] = 0b11111111111111111111111111111111;
  dec.bits[2] = 0;
  dec.bits[3] = 0b10000000000000000000000000000000;
  int error = s21_from_decimal_to_float(dec, &result);
  ck_assert_float_eq(result, num);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_float_5) {
  s21_decimal dec = {0};
  float num = 0.0f;
  float result = 0;
  dec.bits[0] = 0;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0;
  int error = s21_from_decimal_to_float(dec, &result);
  ck_assert_float_eq(result, num);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(tc_decimal_to_float_6) {
  s21_decimal dec = {0};
  float result = 0.0f;
  float num = 79228162514264337593543950335.0f;
  dec.bits[0] = 0b11111111111111111111111111111111;
  dec.bits[1] = 0b11111111111111111111111111111111;
  dec.bits[2] = 0b11111111111111111111111111111111;
  setexp(&dec.bits[3], 0);
  int error = s21_from_decimal_to_float(dec, &result);
  ck_assert_float_eq(result, num);
  ck_assert_int_eq(error, 0);
}
END_TEST

// <=== TEST CASES: s21_sub ===>

// -0 - 2 = -2
START_TEST(tc_sub_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 2;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -2);
}
END_TEST

// 0 - 2 = -2
START_TEST(tc_sub_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 2;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 1234567 - 568 = 1233999
START_TEST(tc_sub_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1234567;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 568;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 1233999);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -7 - -5 = -2
START_TEST(tc_sub_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 7;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -1 - -12345 = 12344
START_TEST(tc_sub_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 12345;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 12344);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 1 - -12345 = 12346
START_TEST(tc_sub_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 12345;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 12346);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 3 - 5 = -2
START_TEST(tc_sub_7) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 3;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 3 - -5 = 8
START_TEST(tc_sub_8) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 3;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 8);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -3 - 5 = -8
START_TEST(tc_sub_9) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 3;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -8);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -5 - 3 = -8
START_TEST(tc_sub_10) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 3;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -8);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 5 - -3 = 8
START_TEST(tc_sub_11) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 3;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 8);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 10.9 - 3.1 = 7.8
START_TEST(tc_sub_12) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  s21_from_float_to_decimal(0.0195, &value_1);
  s21_from_float_to_decimal(0.0001, &value_2);

  int error = s21_sub(value_1, value_2, &result);
  float res = 0.0f;
  s21_from_decimal_to_float(result, &res);
  ck_assert_float_eq(res, 0.0194);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335-0.6=79228162514264337593543950334
START_TEST(tc_sub_13) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = 6;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 4294967295U - 1);
  ck_assert_int_eq((unsigned)result.bits[1], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[2], 4294967295U);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335-0.4=79228162514264337593543950334
START_TEST(tc_sub_14) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = 4;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[1], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[2], 4294967295U);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335- -0.5=ошибка 1
START_TEST(tc_sub_15) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000010000000000000000;

  int error = s21_sub(value_1, value_2, &result);

  ck_assert_int_eq(error, 1);
}
END_TEST

// 7.9228162514264337593543950335-79228162514264337593543950335=-79228162514264337593543950327
START_TEST(tc_sub_16) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0b00000000000111000000000000000000;

  value_2.bits[0] = MAXBITS;
  value_2.bits[1] = MAXBITS;
  value_2.bits[2] = MAXBITS;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 4294967287U);
  ck_assert_int_eq((unsigned)result.bits[1], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[2], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[3],
                   0b10000000000000000000000000000000);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335-79228162514264337593543950335=0
START_TEST(tc_sub_17) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = MAXBITS;
  value_2.bits[1] = MAXBITS;
  value_2.bits[2] = MAXBITS;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0);
  ck_assert_int_eq((unsigned)result.bits[1], 0);
  ck_assert_int_eq((unsigned)result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 5 - -5 = 0
START_TEST(tc_sub_18) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 10);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -5 - 5 = 0
START_TEST(tc_sub_19) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_sub(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -10);

  ck_assert_int_eq(error, 0);
}
END_TEST

// <=== TEST CASES: s21_add ===>

// -0 + 2 = 2
START_TEST(tc_add_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 2;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 2);
}
END_TEST

// 0 + 2 = 2
START_TEST(tc_add_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 2;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 1234567 + 568 = 1235135
START_TEST(tc_add_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1234567;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 568;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 1235135);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -7 + -5 = -12
START_TEST(tc_add_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 7;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -12);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -1 + -12345 = -12346
START_TEST(tc_add_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 12345;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -12346);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 1 + -12345 = -12344
START_TEST(tc_add_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 12345;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -12344);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 3 + 5 = 8
START_TEST(tc_add_7) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 3;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 8);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 3 + -5 = -2
START_TEST(tc_add_8) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 3;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -3 + 5 = 2
START_TEST(tc_add_9) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 3;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -5 + 3 = -2
START_TEST(tc_add_10) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 3;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 5 + -3 = 2
START_TEST(tc_add_11) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 3;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 2);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 10.9 - 3.1 = 7.8
START_TEST(tc_add_12) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  s21_from_float_to_decimal(0.0195, &value_1);
  s21_from_float_to_decimal(0.0001, &value_2);

  int error = s21_add(value_1, value_2, &result);
  float res;
  s21_from_decimal_to_float(result, &res);
  ck_assert_float_eq(res, 0.0196);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335 + 0.4=79228162514264337593543950335
START_TEST(tc_add_13) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = 4;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_add(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[1], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[2], 4294967295U);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335+(-0.5)=79228162514264337593543950334
START_TEST(tc_add_14) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000010000000000000000;

  int error = s21_add(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 4294967294U);
  ck_assert_int_eq((unsigned)result.bits[1], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[2], 4294967295U);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335+ 0.5=ошибка 1
START_TEST(tc_add_15) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_add(value_1, value_2, &result);

  ck_assert_int_eq(error, 1);
}
END_TEST

// -7.9228162514264337593543950335+79228162514264337593543950335=+79228162514264337593543950327
START_TEST(tc_add_16) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0b10000000000111000000000000000000;

  value_2.bits[0] = MAXBITS;
  value_2.bits[1] = MAXBITS;
  value_2.bits[2] = MAXBITS;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 4294967287U);
  ck_assert_int_eq((unsigned)result.bits[1], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[2], 4294967295U);
  ck_assert_int_eq((unsigned)result.bits[3],
                   0b00000000000000000000000000000000);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 79228162514264337593543950335+-79228162514264337593543950335=0
START_TEST(tc_add_17) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0;

  value_2.bits[0] = MAXBITS;
  value_2.bits[1] = MAXBITS;
  value_2.bits[2] = MAXBITS;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  ck_assert_int_eq((unsigned)result.bits[0], 0);
  ck_assert_int_eq((unsigned)result.bits[1], 0);
  ck_assert_int_eq((unsigned)result.bits[2], 0);
  ck_assert_int_eq((unsigned)result.bits[3], 0);

  ck_assert_int_eq(error, 0);
}
END_TEST

// -5 + -5 = 0
START_TEST(tc_add_18) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -10);

  ck_assert_int_eq(error, 0);
}
END_TEST

// 5 + 5 = 0
START_TEST(tc_add_19) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_add(value_1, value_2, &result);
  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 10);

  ck_assert_int_eq(error, 0);
}
END_TEST

// <=== TEST CASES: s21_mul ===>

// -132 * -34 = 4488
START_TEST(tc_mul_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 132;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 34;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 4488);
}
END_TEST

// -79228162514264337593543950335* 0.00321 = -254322401670788523675276080.58
START_TEST(tc_mul_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};
  // s21_decimal result_origin;

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 321;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 2);

  // result_origin.bits[0] = 0b10111100011010100111111011111010;
  // result_origin.bits[1] = 0b00000100000110001001001101110100;
  // result_origin.bits[2] = 0b01010010001011010000111001010110;
  // result_origin.bits[3] = 0b10000000000000100000000000000000;

  // ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
  // ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  // ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  // ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
}
END_TEST

// -79228162514264337593543950335*1.1= ошбка 2
START_TEST(tc_mul_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 11;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 2);
}
END_TEST

// *0 = 0
START_TEST(tc_mul_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 132;
  value_1.bits[1] = 132;
  value_1.bits[2] = 123;
  value_1.bits[3] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);
}
END_TEST

// 1е-15 * 15e-14 = 1.5e-28 ~~~ 2e-28
START_TEST(tc_mul_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b00000000000011110000000000000000;  // степень 15

  value_2.bits[0] = 15;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000011100000000000000000;  // степень 14

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(2, result.bits[0]);
  ck_assert_int_eq(0b00000000000111000000000000000000, result.bits[3]);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);
}
END_TEST

// 1е-28 * 15e-28 = 0
START_TEST(tc_mul_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 1;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b00000000000111000000000000000000;  // степень 28

  value_2.bits[0] = 15;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000111000000000000000000;  // степень 28

  int error = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(0, result.bits[0]);
  ck_assert_int_eq(0, result.bits[3]);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);
}
END_TEST

// <=== TEST CASES: s21_compare ===>

// -132 & -34
START_TEST(tc_compare_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 132;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 34;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, TRUE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, FALSE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, FALSE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, TRUE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, FALSE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, TRUE);
}
END_TEST

// 132... & -34....
START_TEST(tc_compare_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 132;
  value_1.bits[3] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 34;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, FALSE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, FALSE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, TRUE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, FALSE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, TRUE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, TRUE);
}
END_TEST

// 13,2... & 34....
START_TEST(tc_compare_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 132;
  value_1.bits[3] = 0b00000000000000010000000000000000;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 34;
  value_2.bits[3] = 0;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, TRUE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, FALSE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, FALSE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, TRUE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, FALSE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, TRUE);
}
END_TEST

// 132... & 34....
START_TEST(tc_compare_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 132;
  value_1.bits[3] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 34;
  value_2.bits[3] = 0;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, FALSE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, FALSE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, TRUE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, FALSE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, TRUE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, TRUE);
}
END_TEST

// -0 & 0
START_TEST(tc_compare_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, FALSE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, TRUE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, FALSE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, TRUE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, TRUE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, FALSE);
}
END_TEST

// 132... & 132....
START_TEST(tc_compare_6) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 132;
  value_1.bits[3] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 132;
  value_2.bits[3] = 0;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, FALSE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, TRUE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, FALSE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, TRUE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, TRUE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, FALSE);
}
END_TEST

// 132... & -132....
START_TEST(tc_compare_7) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};

  value_1.bits[0] = 0;
  value_1.bits[1] = 0;
  value_1.bits[2] = 132;
  value_1.bits[3] = 0;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 132;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int less_is_true = s21_is_less(value_1, value_2);
  ck_assert_int_eq(less_is_true, FALSE);

  int is_equal = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(is_equal, FALSE);

  int is_greater = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(is_greater, TRUE);

  int is_less_or_equal = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(is_less_or_equal, FALSE);

  int is_greater_or_equal = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(is_greater_or_equal, TRUE);

  int is_not_equal = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(is_not_equal, TRUE);
}
END_TEST

// <=== TEST CASES: s21_div ===>

// 135 / -0,5 = 270
START_TEST(tc_div_1) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 135;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 5;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000010000000000000000;

  int error = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -270);
}
END_TEST

// -0,5 / -4 000 000 = 125e-9
START_TEST(tc_div_2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 5;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0b10000000000000010000000000000000;

  value_2.bits[0] = 4000000;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(result.bits[0], 125);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0b00000000000010010000000000000000);  // 9
}
END_TEST

// -MAXDECIMAL / 0,9 = ошибка 2
START_TEST(tc_div_3) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 9;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(error, 2);
}
END_TEST

// -MAXDECIMAL / 0 = ошибка 3
START_TEST(tc_div_4) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = MAXBITS;
  value_1.bits[1] = MAXBITS;
  value_1.bits[2] = MAXBITS;
  value_1.bits[3] = 0b10000000000000000000000000000000;

  value_2.bits[0] = 0;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0;

  int error = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(error, 3);
}
END_TEST

// 15 / 0.2 = 75
START_TEST(tc_div_5) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value_1.bits[0] = 0b00000000000000000000000000001111;
  value_1.bits[1] = 0;
  value_1.bits[2] = 0;
  value_1.bits[3] = 0;

  value_2.bits[0] = 0b00000000000000000000000000000010;
  value_2.bits[1] = 0;
  value_2.bits[2] = 0;
  value_2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  int error = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(result.bits[0], 75);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

// <=== TEST CASES: s21_floor ===>

// -13.5 -> -14
START_TEST(tc_floor_1) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 135;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000000010000000000000000;

  s21_floor(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -14);
}

// 13.5 -> 13
START_TEST(tc_floor_2) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 135;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b00000000000000010000000000000000;

  s21_floor(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 13);
}

// 0.9 -> 0
START_TEST(tc_floor_3) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 9;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b00000000000000010000000000000000;

  s21_floor(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);
}

// -0.0001 -> -1
START_TEST(tc_floor_4) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 1;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000001000000000000000000;

  s21_floor(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -1);
}

// <=== TEST CASES: s21_round ===>

// -13.5 -> -14
START_TEST(tc_round_1) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 135;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000000010000000000000000;

  s21_round(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -14);
}

// 99.5 -> 100
START_TEST(tc_round_2) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 995;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b00000000000000010000000000000000;

  s21_round(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 100);
}

// -0.0001 -> -0
START_TEST(tc_round_3) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 1;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000001000000000000000000;

  s21_round(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);
}

// <=== TEST CASES: s21_truncate ===>

// -13.5 -> -13
START_TEST(tc_truncate_1) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 13500;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000000110000000000000000;

  s21_truncate(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, -13);
  ck_assert_int_eq((unsigned)result.bits[3],
                   0b10000000000000000000000000000000);
}

// 99.5 -> 100
START_TEST(tc_truncate_2) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 9995;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b00000000000000010000000000000000;

  s21_truncate(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 999);
  ck_assert_int_eq(result.bits[3], 0);
}

// 0.9 -> 0
START_TEST(tc_truncate_3) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 900;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b00000000000000110000000000000000;

  s21_truncate(value, &result);

  int res = 0;
  s21_from_decimal_to_int(result, &res);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[3], 0);
}

// <=== TEST CASES: s21_truncate ===>

// -13.5 -> 13.5
START_TEST(tc_negate_1) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 135;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000000110000000000000000;

  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(result.bits[0], value.bits[0]);
  ck_assert_int_eq(result.bits[1], value.bits[1]);
  ck_assert_int_eq(result.bits[2], value.bits[2]);
  ck_assert_int_eq((unsigned)result.bits[3],
                   0b00000000000000110000000000000000);
}

START_TEST(tc_negate_2) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 135;
  value.bits[1] = 3453;
  value.bits[2] = 349863985;
  value.bits[3] = 0b00000000000000010000000000000000;

  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(result.bits[0], value.bits[0]);
  ck_assert_int_eq(result.bits[1], value.bits[1]);
  ck_assert_int_eq(result.bits[2], value.bits[2]);
  ck_assert_int_eq((unsigned)result.bits[3],
                   0b10000000000000010000000000000000);
}

START_TEST(tc_negate_3) {
  s21_decimal value = {0};
  s21_decimal result = {{0, 0, 0, 0}};

  value.bits[0] = 0;
  value.bits[1] = 0;
  value.bits[2] = 0;
  value.bits[3] = 0b10000000000000000000000000000000;

  int error = s21_negate(value, &result);

  ck_assert_int_eq(error, 0);

  ck_assert_int_eq(result.bits[0], value.bits[0]);
  ck_assert_int_eq(result.bits[1], value.bits[1]);
  ck_assert_int_eq(result.bits[2], value.bits[2]);
  ck_assert_int_eq((unsigned)result.bits[3],
                   0b00000000000000000000000000000000);
}

START_TEST(tc_mod) {
  s21_decimal val1 = {0}, val2 = {0}, rez = {0};
  s21_decimal our_rez = {{0, 0, 0, 0}};

  // test 1
  val1.bits[0] = 7;
  val1.bits[1] = 0;
  val1.bits[2] = 0;
  val1.bits[3] = 0;

  val2.bits[0] = 2;
  val2.bits[1] = 0;
  val2.bits[2] = 0;
  val2.bits[3] = 0;

  rez.bits[0] = 1;
  rez.bits[1] = 0;
  rez.bits[2] = 0;
  rez.bits[3] = 0;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

  // test 2
  val1.bits[0] = 0b00000000000000000000000000000111;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b10000000000000000000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000000000000000000000;

  rez.bits[0] = 0b00000000000000000000000000000001;
  rez.bits[1] = 0b00000000000000000000000000000000;
  rez.bits[2] = 0b00000000000000000000000000000000;
  rez.bits[3] = 0b00000000000000000000000000000000;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

  // test 3
  val1.bits[0] = 0b00000000000000000000000000000111;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b10000000000000000000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b10000000000000000000000000000000;

  rez.bits[0] = 0b00000000000000000000000000000001;
  rez.bits[1] = 0b00000000000000000000000000000000;
  rez.bits[2] = 0b00000000000000000000000000000000;
  rez.bits[3] = 0b00000000000000000000000000000000;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

  // test 4
  val1.bits[0] = 0b00000000000000000000000000001010;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b00000000000000000000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000000000000000000000;

  rez.bits[0] = 0b00000000000000000000000000000000;
  rez.bits[1] = 0b00000000000000000000000000000000;
  rez.bits[2] = 0b00000000000000000000000000000000;
  rez.bits[3] = 0b00000000000000000000000000000000;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

  // test 5
  val1.bits[0] = 0b00000000000000000000000000000111;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  rez.bits[0] = 0b00000000000000000000000000000000;
  rez.bits[1] = 0b00000000000000000000000000000000;
  rez.bits[2] = 0b00000000000000000000000000000000;
  rez.bits[3] = 0b00000000000000000000000000000000;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

  // test 6
  val1.bits[0] = 0b00000000000000000000000000000111;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b00000000000000100000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000000;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  int origin_check = 3, our_check = 0;

  our_check = s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(origin_check, our_check);

  // test 7
  val1.bits[0] = MAXBITS;
  val1.bits[1] = MAXBITS;
  val1.bits[2] = MAXBITS;
  val1.bits[3] = 0b00000000000000000000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  origin_check = 1;
  our_check = 0;

  our_check = s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(origin_check, our_check);

  // test 8
  val1.bits[0] = MAXBITS;
  val1.bits[1] = MAXBITS;
  val1.bits[2] = MAXBITS;
  val1.bits[3] = 0b10000000000000000000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  origin_check = 2;
  our_check = 0;

  our_check = s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(origin_check, our_check);

  // test 9
  our_rez.bits[0] = 0;
  our_rez.bits[1] = 0;
  our_rez.bits[2] = 0;
  our_rez.bits[3] = 0;

  val1.bits[0] = 0b00000000000000000000000000001111;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b00000000000000000000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000010;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  rez.bits[0] = 0b00000000000000000000000000000000;
  rez.bits[1] = 0b00000000000000000000000000000000;
  rez.bits[2] = 0b00000000000000000000000000000000;
  rez.bits[3] = 0b00000000000000000000000000000000;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);

  // test 9
  val1.bits[0] = 0b00000000000000000000000000000010;
  val1.bits[1] = 0b00000000000000000000000000000000;
  val1.bits[2] = 0b00000000000000000000000000000000;
  val1.bits[3] = 0b00000000000000110000000000000000;

  val2.bits[0] = 0b00000000000000000000000000000111;
  val2.bits[1] = 0b00000000000000000000000000000000;
  val2.bits[2] = 0b00000000000000000000000000000000;
  val2.bits[3] = 0b00000000000000010000000000000000;  // степень 1

  rez.bits[0] = 0b00000000000000000000000000000000;
  rez.bits[1] = 0b00000000000000000000000000000000;
  rez.bits[2] = 0b00000000000000000000000000000000;
  rez.bits[3] = 0b00000000000000000000000000000000;

  s21_mod(val1, val2, &our_rez);
  ck_assert_int_eq(rez.bits[0], our_rez.bits[0]);
  ck_assert_int_eq(rez.bits[1], our_rez.bits[1]);
  ck_assert_int_eq(rez.bits[2], our_rez.bits[2]);
  ck_assert_int_eq(rez.bits[3], our_rez.bits[3]);
}
END_TEST

/**
    --------------------------------------------------
            <========== TEST SUITES ==========>
    --------------------------------------------------
**/

Suite *ts_int_to_decimal() {
  Suite *suite = suite_create("ts_int_to_decimal");
  TCase *test_case = tcase_create("tc_int_to_decimal");

  tcase_add_test(test_case, tc_int_to_decimal_1);
  tcase_add_test(test_case, tc_int_to_decimal_2);
  tcase_add_test(test_case, tc_int_to_decimal_3);
  tcase_add_test(test_case, tc_int_to_decimal_4);
  tcase_add_test(test_case, tc_int_to_decimal_5);
  tcase_add_test(test_case, tc_int_to_decimal_6);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_float_to_decimal() {
  Suite *suite = suite_create("ts_float_to_decimal");
  TCase *test_case = tcase_create("tc_float_to_decimal");

  tcase_add_test(test_case, tc_float_to_decimal_1);
  tcase_add_test(test_case, tc_float_to_decimal_2);
  tcase_add_test(test_case, tc_float_to_decimal_3);
  tcase_add_test(test_case, tc_float_to_decimal_4);
  tcase_add_test(test_case, tc_float_to_decimal_5);
  tcase_add_test(test_case, tc_float_to_decimal_6);
  tcase_add_test(test_case, tc_float_to_decimal_7);
  tcase_add_test(test_case, tc_float_to_decimal_8);
  tcase_add_test(test_case, tc_float_to_decimal_9);
  tcase_add_test(test_case, tc_float_to_decimal_10);
  tcase_add_test(test_case, tc_float_to_decimal_11);
  tcase_add_test(test_case, tc_float_to_decimal_12);
  tcase_add_test(test_case, tc_float_to_decimal_13);
  tcase_add_test(test_case, tc_float_to_decimal_14);
  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_decimal_to_int() {
  Suite *suite = suite_create("ts_decimal_to_int");
  TCase *test_case = tcase_create("tc_decimal_to_int");

  tcase_add_test(test_case, tc_decimal_to_int_1);
  tcase_add_test(test_case, tc_decimal_to_int_2);
  tcase_add_test(test_case, tc_decimal_to_int_3);
  tcase_add_test(test_case, tc_decimal_to_int_4);
  tcase_add_test(test_case, tc_decimal_to_int_5);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_decimal_to_float() {
  Suite *suite = suite_create("ts_decimal_to_float");
  TCase *test_case = tcase_create("tc_decimal_to_float");

  tcase_add_test(test_case, tc_decimal_to_float_1);
  tcase_add_test(test_case, tc_decimal_to_float_2);
  tcase_add_test(test_case, tc_decimal_to_float_3);
  tcase_add_test(test_case, tc_decimal_to_float_4);
  tcase_add_test(test_case, tc_decimal_to_float_5);
  tcase_add_test(test_case, tc_decimal_to_float_6);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_sub() {
  Suite *suite = suite_create("ts_sub");
  TCase *test_case = tcase_create("tc_sub");

  tcase_add_test(test_case, tc_sub_1);
  tcase_add_test(test_case, tc_sub_2);
  tcase_add_test(test_case, tc_sub_3);
  tcase_add_test(test_case, tc_sub_4);
  tcase_add_test(test_case, tc_sub_5);
  tcase_add_test(test_case, tc_sub_6);
  tcase_add_test(test_case, tc_sub_7);
  tcase_add_test(test_case, tc_sub_8);
  tcase_add_test(test_case, tc_sub_9);
  tcase_add_test(test_case, tc_sub_10);
  tcase_add_test(test_case, tc_sub_11);
  tcase_add_test(test_case, tc_sub_12);
  tcase_add_test(test_case, tc_sub_13);
  tcase_add_test(test_case, tc_sub_14);
  tcase_add_test(test_case, tc_sub_15);
  tcase_add_test(test_case, tc_sub_16);
  tcase_add_test(test_case, tc_sub_17);
  tcase_add_test(test_case, tc_sub_18);
  tcase_add_test(test_case, tc_sub_19);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_add() {
  Suite *suite = suite_create("ts_sub");
  TCase *test_case = tcase_create("tc_sub");

  tcase_add_test(test_case, tc_add_1);
  tcase_add_test(test_case, tc_add_2);
  tcase_add_test(test_case, tc_add_3);
  tcase_add_test(test_case, tc_add_4);
  tcase_add_test(test_case, tc_add_5);
  tcase_add_test(test_case, tc_add_6);
  tcase_add_test(test_case, tc_add_7);
  tcase_add_test(test_case, tc_add_8);
  tcase_add_test(test_case, tc_add_9);
  tcase_add_test(test_case, tc_add_10);
  tcase_add_test(test_case, tc_add_11);
  tcase_add_test(test_case, tc_add_12);
  tcase_add_test(test_case, tc_add_13);
  tcase_add_test(test_case, tc_add_14);
  tcase_add_test(test_case, tc_add_15);
  tcase_add_test(test_case, tc_add_16);
  tcase_add_test(test_case, tc_add_17);
  tcase_add_test(test_case, tc_add_18);
  tcase_add_test(test_case, tc_add_19);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_mul() {
  Suite *suite = suite_create("ts_mul");
  TCase *test_case = tcase_create("tc_mul");

  tcase_add_test(test_case, tc_mul_1);
  tcase_add_test(test_case, tc_mul_2);
  tcase_add_test(test_case, tc_mul_3);
  tcase_add_test(test_case, tc_mul_4);
  tcase_add_test(test_case, tc_mul_5);
  tcase_add_test(test_case, tc_mul_6);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_compare() {
  Suite *suite = suite_create("ts_compare");
  TCase *test_case = tcase_create("tc_compare");

  tcase_add_test(test_case, tc_compare_1);
  tcase_add_test(test_case, tc_compare_2);
  tcase_add_test(test_case, tc_compare_3);
  tcase_add_test(test_case, tc_compare_4);
  tcase_add_test(test_case, tc_compare_5);
  tcase_add_test(test_case, tc_compare_6);
  tcase_add_test(test_case, tc_compare_7);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_div() {
  Suite *suite = suite_create("ts_div");
  TCase *test_case = tcase_create("tc_div");

  tcase_add_test(test_case, tc_div_1);
  tcase_add_test(test_case, tc_div_2);
  tcase_add_test(test_case, tc_div_3);
  tcase_add_test(test_case, tc_div_4);
  tcase_add_test(test_case, tc_div_5);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_floor() {
  Suite *suite = suite_create("ts_floor");
  TCase *test_case = tcase_create("tc_floor");

  tcase_add_test(test_case, tc_floor_1);
  tcase_add_test(test_case, tc_floor_2);
  tcase_add_test(test_case, tc_floor_3);
  tcase_add_test(test_case, tc_floor_4);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_round() {
  Suite *suite = suite_create("ts_round");
  TCase *test_case = tcase_create("tc_round");

  tcase_add_test(test_case, tc_round_1);
  tcase_add_test(test_case, tc_round_2);
  tcase_add_test(test_case, tc_round_3);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_truncate() {
  Suite *suite = suite_create("ts_truncate");
  TCase *test_case = tcase_create("tc_truncate");

  tcase_add_test(test_case, tc_truncate_1);
  tcase_add_test(test_case, tc_truncate_2);
  tcase_add_test(test_case, tc_truncate_3);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_negate() {
  Suite *suite = suite_create("ts_negate");
  TCase *test_case = tcase_create("tc_negate");

  tcase_add_test(test_case, tc_negate_1);
  tcase_add_test(test_case, tc_negate_2);
  tcase_add_test(test_case, tc_negate_3);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_mod() {
  Suite *suite = suite_create("ts_mod");
  TCase *test_case = tcase_create("tc_mod");

  tcase_add_test(test_case, tc_mod);

  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_int_to_decimal(),
                          ts_float_to_decimal(),
                          ts_decimal_to_int(),
                          ts_decimal_to_float(),
                          ts_sub(),
                          ts_add(),
                          ts_mul(),
                          ts_compare(),
                          ts_div(),
                          ts_floor(),
                          ts_round(),
                          ts_truncate(),
                          ts_negate(),
                          ts_mod(),
                          NULL};
  int failed = 0;

  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}
