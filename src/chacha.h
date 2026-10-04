#ifndef LUNA_CHACHA_H
#define LUNA_CHACHA_H
#include <stdint.h>
#include <stdlib.h>

int chacha20_block(uint32_t* state);
int chacha_block(uint32_t* state, const int rounds);
int chacha_init(uint32_t* state, const uint8_t* key, size_t key_length, const uint8_t* counter, size_t counter_length, const uint8_t* nonce, size_t nonce_length);
int quarter_round(uint32_t* state, const int a, const int b, const int c, const int d);
int serialize_state(const uint32_t* state, uint8_t* octets);
int set_chacha_constant(uint32_t* state);
#endif
