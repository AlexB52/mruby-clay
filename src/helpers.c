#include <math.h>

float round_to_2_decimal(float value) {
  return roundf(value * 100.0f) / 100.0f;
}