#include <stdio.h>
#include <assert.h>
#include "lib/ht.h"
#include "lib/ba-ht.h"
#include "lib/bitarray.h"

void bitarray_print(bitarray b) {
    for (int i = BITARRAY_LIMIT - 1; i >= 0; i--) {
        printf("%u", (unsigned int) bitarray_get(b, i));
    }
    puts("");
}

ba_ht_elem get_elem(bitarray ba, int prevMove) {
	ba_ht_elem elem = malloc(sizeof(struct ba_ht_elem_base));
	elem->ba = ba;
	elem->last_move = prevMove;
	return elem;
}

void testA() {
	ht ba_ht = ba_ht_new(12);
	assert(ba_ht != NULL);
	bitarray ba = bitarray_new();
	ba = bitarray_flip(ba, 3);
	ba_ht_insert(ba_ht, get_elem(ba, 0));

	ba_ht_elem e = ba_ht_lookup(ba_ht, &ba);
	bitarray_print(e->ba);
}

int main() {
	testA();
	return 0;
}
