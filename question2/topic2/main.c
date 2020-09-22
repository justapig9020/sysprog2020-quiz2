#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MASK 0x0101010101010101ul
#define ARR_SZ(arr) (sizeof(arr) / sizeof(arr[0]))
#define HEX_TO_VAL(in, type)                              \
    do {                                                  \
        const type letter = in & (type)(0x40 * MASK);     \
        const type shift = (letter >> 3) | (letter >> 6); \
        in = (in + shift) & (type)(0xf * MASK);           \
        type sh_msk = (type)(0xf * (MASK - 1));           \
        for (size_t i = 0; i < sizeof(type) - 1; i++) {   \
            type forward = in & sh_msk;                   \
            in &= ~sh_msk;                                \
            forward >>= 4;                                \
            in |= forward;                                \
            sh_msk <<= 4;                                 \
        }                                                 \
        in &= (MASK * 0xff) >> (sizeof(type) << 2);       \
    } while (0)

bool isbreak(char c) { return c == '\0' || c == '\n'; }

void get_hexchar(char buf[], size_t len) {
    int i = len - 1;
    while (1) {
        char c = getchar();
        if (isbreak(c) || i < 0) break;
        buf[i--] = c;
    }

    while (i >= 0) buf[i--] = 0;
}

uint8_t byte_hex2val(uint8_t in) {
    HEX_TO_VAL(in, uint8_t);
    return in & 0xf;
}

uint32_t ward_hex2val(uint64_t in) {
    /*
    const uint64_t letter = in & (0x40 * MASK);
    const uint64_t shift = (letter >> 3) | (letter >> 6);

    in = (in + shift) & (0xf * MASK);
    uint64_t sh_msk = 0xf * (MASK - 1);
    for (size_t i = 0; i < 7; i++) {
        uint64_t forward = in & sh_msk;
        in &= ~sh_msk;
        forward >>= 4;
        in |= forward;
        sh_msk <<= 4;
    }
    */
    HEX_TO_VAL(in, uint64_t);
    return in & 0xffffffff;
}

int main(void) {
    char buf[8];
    const size_t len = ARR_SZ(buf);

    get_hexchar(buf, len);
    uint32_t dig = ward_hex2val(*(uint64_t *)buf);

    printf("Hex:\t%x\n", dig);
    printf("Dig:\t%u\n", dig);
    uint8_t b = byte_hex2val('f');
    printf("Hex:\t%x\n", b);
    printf("Dig:\t%u\n", b);
    return 0;
}
