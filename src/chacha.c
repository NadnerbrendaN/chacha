#include "chacha.h"

uint32_t load_uint32_le(const uint8_t* octets);
void quarter_round(uint32_t* state, const int a, const int b, const int c, const int d);
uint32_t rotl(const uint32_t a, const int b);
void set_chacha_constant(uint32_t* state);

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

int chacha_init(uint32_t* state, const uint8_t* key, const size_t key_length, const uint8_t* nonce, const size_t nonce_length) {
	if (!state || !key || !nonce) {
		return -1;
	}
	if (key_length != 32 || nonce_length != 12) {
		return -1;
	}
	set_chacha_constant(state);
	for (int i = 0; i < 8; ++i) {
		state[4 + i] = load_uint32_le(key + i*4);
	}
	state[12] = 1;
	for (int i = 0; i < 3; ++i) {
		state[13 + i] = load_uint32_le(nonce + i*4);
	}
	return 0;
}

uint32_t load_uint32_le(const uint8_t* octets) { // don't call unless you have four readable bytes at this pointer
	return ( octets[0]
			|octets[1] << 8
			|octets[2] << 16
			|octets[3] << 24 );
}

void quarter_round(uint32_t* state, const int a, const int b, const int c, const int d) {
	state[a] += state[b]; state[d] ^= state[a]; state[d] = rotl(state[d], 16);
	state[c] += state[d]; state[b] ^= state[c]; state[b] = rotl(state[b], 12);
	state[a] += state[b]; state[d] ^= state[a]; state[d] = rotl(state[d], 8);
	state[c] += state[d]; state[b] ^= state[c]; state[b] = rotl(state[b], 7);
}

uint32_t rotl(const uint32_t a, const int b) {
	return ((a << b) | (a >> (32 - b)));
}

int serialize_state(const uint32_t* state, uint8_t* octets) {
	if (!state || !octets) {
		return -1;
	}
	for (int i = 0; i < 16; ++i) {
		octets[i*4]     = state[i] & 0xff;
		octets[i*4 + 1] = (state[i] >> 8) & 0xff;
		octets[i*4 + 2] = (state[i] >> 16) & 0xff;
		octets[i*4 + 3] = (state[i] >> 24) & 0xff;
	}
	return 0;
}

void set_chacha_constant(uint32_t* state) {
	state[0] = 0x61707865;
	state[1] = 0x3320646e;
	state[2] = 0x79622d32;
	state[3] = 0x6b206574;
}
