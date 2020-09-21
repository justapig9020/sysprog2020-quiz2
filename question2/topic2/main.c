#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define MASK 0x0101010101010101
#define ARR_SZ(arr) (sizeof(arr) / sizeof(arr[0]))

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

uint32_t hexchar2val(uint64_t in) {
    const uint64_t letter = in & (0x40 * MASK);
    const uint64_t shift = (letter >> 3) | (letter >> 6);

    in = (in + shift) & (0xf * MASK);
    uint64_t sh_msk = 0xf * (MASK - 1);
    for (size_t i = 0; i < 7; i++) {
        uint64_t shift = in & sh_msk;
        in &= ~sh_msk;
        shift >>= 4;
        in |= shift;
        sh_msk <<= 4;
    }
    return in & 0xffffffff;
}

int main(void) {
    char buf[8];
    const size_t len = ARR_SZ(buf);

    get_hexchar(buf, len);
    uint32_t dig = hexchar2val(*(uint64_t *)buf);

    printf("Hex:\t%x\n", dig);
    printf("Dig:\t%u\n", dig);
    return 0;
}
