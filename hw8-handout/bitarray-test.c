#include <stdio.h>
#include "lib/bitarray.h"
#include <assert.h>

void bitarray_print(bitarray b) {
    for (int i = BITARRAY_LIMIT - 1; i >= 0; i--) {
        printf("%u", (unsigned int) bitarray_get(b, i));
    }
    puts("");
}

void testA() {
    bitarray b = bitarray_new();
    for (int i = 0; i < BITARRAY_LIMIT; i++)
        assert(bitarray_get(b, i) == 0);
    bitarray b2 = bitarray_flip(b, 3);
    assert(bitarray_get(b2, 3) == 1);
    bitarray_print(b2);
}

void testB() {
    bitarray b = bitarray_new();
    for (int i = 1; i < BITARRAY_LIMIT; i += 2) {
        b = bitarray_flip(b, i);
    }
    bitarray_print(b);
}

int main() {
    testA();
    testB();
    return 0;
}
