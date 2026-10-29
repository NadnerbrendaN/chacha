#include <stdio.h>
#include <stdlib.h>

#include "chacha.h"

void print_matrix(uint32_t* cha_arr) { /* a quick helper function to print the chacha matrix */
	printf("%x, %x, %x, %x\n%x, %x, %x, %x\n%x, %x, %x, %x\n%x, %x, %x, %x\n",
			cha_arr[0], cha_arr[1], cha_arr[2], cha_arr[3],
			cha_arr[4], cha_arr[5], cha_arr[6], cha_arr[7],
			cha_arr[8], cha_arr[9], cha_arr[10],cha_arr[11],
			cha_arr[12],cha_arr[13],cha_arr[14],cha_arr[15]);
}

int main() {
	uint32_t* cha_arr = malloc(16*sizeof(uint32_t));
	uint8_t key[32] = {0};
	for (int i = 0; i < 32; ++i) {
		key[i] = i;
	} /* initialize key to the example value given in RFC 8439 */
	uint8_t nonce[12] = {0,0,0,9,0,0,0,0x4a,0,0,0,0}; /* initialize nonce to the example value */
	chacha_init(cha_arr, key, 32, nonce, 12); 
	/* initialize the chacha state with our key and nonce.
	 * sizes are necessary to ensure the user knows they should pass pointers to sufficient memory */
	print_matrix(cha_arr);
	chacha20_block(cha_arr);
	/* run the actual chacha20 block function on our initialized state.
	 * use chacha_block(num_rounds) to run a different number of rounds */
	print_matrix(cha_arr);
	uint8_t* out = malloc(64);
	serialize_state(cha_arr, out); /* serialize output from the function, if you need that (and for compliance) */
	for (int i = 0; i < 64; ++i) {
		if (i % 16 == 0) {
			printf("\n");
		}
		printf("%x ", out[i]);
	}
	printf("\n");
	free(out);
	free(cha_arr);
	return 0;
}
