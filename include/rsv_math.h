/*
  rsv_math.h
  Contains math related constants and functions

  C Reservoir Library
  MIT License - https://choosealicense.com/licenses/mit/

  Contributors:
    Jagger Harris
*/

#ifndef RSV_MATH_H
#define RSV_MATH_H

#define RSV_PI 3.14159265358979323846
#define RSV_GOLDEN_RATIO 1.61803398874989484820

/**
 * @brief Get the largest integral value not greater than the argument
 *
 * @param x Integral value
 * @return int Smallest integral value not more than x
 */
static int rsv_floor(float x);

/**
 * @brief Get the smallest integral value not less than the argument
 *
 * @param x Integral value
 * @return int Smallest integral value not less than x
 */
static int rsv_ceil(float x);

/**************** Implementations ****************/

static int rsv_floor(float x) {
  if (x >= 0) {
    return (int)x;
  } else {
    int int_part = (int)x;
    return x == int_part ? x : int_part - 1;
  }
}

static int rsv_ceil(float x) {
  if (x >= 0) {
    int int_part = (int)x;
    return x == int_part ? x : (int_part + 1);
  } else {
    return (int)x;
  }
}

#endif /* RSV_MATH_H */
