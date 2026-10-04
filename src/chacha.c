#include "chacha.h"

uint32_t rotl(const uint32_t a, const int b);

int chacha20_block(uint32_t* state) {
	if (!state) {
		return -1;
	}
	return chacha_block(state, 20);
}

int chacha_block(uint32_t* state, const int rounds) {
	if (!state || (rounds % 2) != 0) {
		return -1;
	}
	int i = 0;
	uint32_t* working_state = malloc(16*sizeof(uint32_t));
	for (i = 0; i < 16; ++i) {
		working_state[i] = state[i];
	}
	for (i = 0; i < rounds/2; ++i) {
		quarter_round(working_state, 0, 4, 8, 12);
		quarter_round(working_state, 1, 5, 9, 13);
		quarter_round(working_state, 2, 6, 10, 14);
		quarter_round(working_state, 3, 7, 11, 15);
		quarter_round(working_state, 0, 5, 10, 15);
		quarter_round(working_state, 1, 6, 11, 12);
		quarter_round(working_state, 2, 7, 8, 13);
		quarter_round(working_state, 3, 4, 9, 14);
	}
	for (i = 0; i < 16; ++i) {
		state[i] += working_state[i];
	}
	free(working_state);
	return 0;
}

int chacha_init(uint32_t* state, const uint8_t* key, size_t key_length, const uint8_t* counter, size_t counter_length, const uint8_t* nonce, size_t nonce_length) {
	if (!state || !key || !counter || !nonce) {
		return -1;
	}
	if (key_length > 64 || counter_length > 64 || nonce_length > 64) {
		return -1;
	}
	if (key_length + counter_length + nonce_length > 64) {
		return -1;
	}
	if (state[0] == 0 && state[1] == 0 && state[2] == 0 && state[3] == 0) {
		set_chacha_constant(state);
	}
	/* TODO: Make this actually happen */
	return 0;
}

int quarter_round(uint32_t* state, const int a, const int b, const int c, const int d) {
	if (!state) {
		return -1;
	}
	state[a] += state[b]; state[d] ^= state[a]; state[d] = rotl(state[d], 16);
	state[c] += state[d]; state[b] ^= state[c]; state[b] = rotl(state[b], 12);
	state[a] += state[b]; state[d] ^= state[a]; state[d] = rotl(state[d], 8);
	state[c] += state[d]; state[b] ^= state[c]; state[b] = rotl(state[b], 7);
	return 0;
}

uint32_t rotl(const uint32_t a, const int b) {
	return ((a << b) | (a >> (32 - b)));
}

int serialize_state(const uint32_t* state, uint8_t* serialized_output) {
	for (int i = 0; i < 16; ++i) {
	}
	return 0;
}

int set_chacha_constant(uint32_t* state){
	if (!state) {
		return -1;
	}
	state[0] = 0x61707865;
	state[1] = 0x3320646e;
	state[2] = 0x79622d32;
	state[3] = 0x6b206574;
	return 0;
}
