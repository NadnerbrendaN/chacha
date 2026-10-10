#ifndef LUNA_CHACHA_H
#define LUNA_CHACHA_H
#include <stdint.h>
#include <stdlib.h>

int chacha20_block(uint32_t* state);
int chacha_block(uint32_t* state, const int rounds);
int chacha_init(uint32_t* state, const uint8_t* key, const size_t key_length, const uint8_t* nonce, const size_t nonce_length);
int serialize_state(const uint32_t* state, uint8_t* octets);
#endif
