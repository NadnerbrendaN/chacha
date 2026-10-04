#include <stdio.h>
#include <stdlib.h>

#include "chacha.h"

void print_matrix(uint32_t* cha_arr) {
	printf("%x, %x, %x, %x\n%x, %x, %x, %x\n%x, %x, %x, %x\n%x, %x, %x, %x\n",
			cha_arr[0], cha_arr[1], cha_arr[2], cha_arr[3],
			cha_arr[4], cha_arr[5], cha_arr[6], cha_arr[7],
			cha_arr[8], cha_arr[9], cha_arr[10],cha_arr[11],
			cha_arr[12],cha_arr[13],cha_arr[14],cha_arr[15]);
}

int main() {
	uint32_t* cha_arr = malloc(16*sizeof(uint32_t));
	for (int i = 0; i < 16; ++i) {
		cha_arr[i] = 0;
	}
//	print_matrix(cha_arr);
	set_chacha_constant(cha_arr);
//	print_matrix(cha_arr);
	/* Using this test vector from RFC 8439:
	 * 61707865  3320646e  79622d32  6b206574 <-- done with set_chacha_constant
	 * 03020100  07060504  0b0a0908  0f0e0d0c
	 * 13121110  17161514  1b1a1918  1f1e1d1c
	 * 00000001  09000000  4a000000  00000000
	 */
	cha_arr[4] = 0x03020100;
	cha_arr[5] = 0x07060504;
	cha_arr[6] = 0x0b0a0908;
	cha_arr[7] = 0x0f0e0d0c;
	cha_arr[8] = 0x13121110;
	cha_arr[9] = 0x17161514;
	cha_arr[10]= 0x1b1a1918;
	cha_arr[11]= 0x1f1e1d1c;
	cha_arr[12]= 0x00000001;
	cha_arr[13]= 0x09000000;
	cha_arr[14]= 0x4a000000;
	cha_arr[15]= 0x00000000;
//	print_matrix(cha_arr);
	chacha20_block(cha_arr);
	print_matrix(cha_arr);
	uint8_t* out = malloc(64);
	serialize_state(cha_arr, out);
	for (int i = 0; i < 64; ++i) {
		printf("%x ", out[i]);
	}
	printf("\n");
	free(out);
	free(cha_arr);
	return 0;
}
