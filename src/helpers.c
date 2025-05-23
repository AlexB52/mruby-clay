#include <math.h>

float round_to_1_decimal(float value) {
    return roundf(value * 10.0f) / 10.0f;
}