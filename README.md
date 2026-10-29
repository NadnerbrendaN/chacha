# chacha

This is an implementation of the ChaCha20 stream cipher / CSPRNG. I am using this project to learn more about
cryptography and C programming. My goals for this project include:
- Write simple, hopefully readable (to me) code
- Verify RFC 8439 compliance for ChaCha20
    - Maybe add Poly1305 support later or in another project
- Learn to debug C programs more thoroughly

Goals for this project do not include:
- Write efficient or optimized code
- Defend against a local attacker with access to memory or anything but ciphertext

### Use

If you're in an environment where your CSPRNG needs to be well-tested, optimized, secure against local attackers,
or fulfill other specific requirements, I hope you know not to use this code. If you're looking for a quick and
simple ChaCha20 implementation to use in some personal project or something, continue reading!

Please note: all functions that return an `int` return `0` for success and `-1` for failure.

A minimal implementation would `#include "chacha.h"` and call `chacha20_block` on a pointer to 16 `uint32_t`
values. `main.c` is a reference implementation with more of the basic functions for state initialization from
the component key and nonce and final serialization.
