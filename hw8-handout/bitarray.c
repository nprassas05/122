#include "lib/bitarray.h"
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/* return a bit array with all bits set to false */
bitarray bitarray_new() {
    bitarray ba = 0;
    return ba;
}

/* get the ith bit of a bit array */
bool bitarray_get(bitarray ba, uint8_t i) {
    assert(0 <= i && i < BITARRAY_LIMIT);
    uint8_t mask = 1;
    return (ba >> i) & mask;
}

/* toggle the ith bit of the bitarray ba, returning
   a new bitarray and leaving the old one unchanged */
bitarray bitarray_flip(bitarray ba, uint8_t i) {
    assert(0 <= i && i < BITARRAY_LIMIT);
    bitarray b2 = ba ^ (1 << i);
    return b2;
}
