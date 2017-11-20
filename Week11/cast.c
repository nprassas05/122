/*
 * Integer casting
 * 
 * 15-122 Principles of Imperative Computation */
  
#include <assert.h>
#include <stdio.h>
#include "lib/xalloc.h"
#include <stdint.h>
#include <string.h>

int main() {
  uint8_t c = 0xFE;
  int32_t i1 = (int32_t)(uint32_t) c;
  int32_t i2 = (int32_t)(int8_t) c;
  printf("Left path, i1, is %d (254)\n", i1);
  printf("Right path, i2, is %d (-2)\n", i2);
  printf("Directly? We get %d.\n", (int32_t) c);

  uint8_t c1 = 0xBE;
  uint8_t c2 = 0xEF;
  int16_t beef = (((int16_t)(uint16_t)c1) << 8) 
    | (int16_t)(uint16_t)c2;
  (void) beef;
  printf("We got the 0x%hX\n", beef);

  return 0;
}
