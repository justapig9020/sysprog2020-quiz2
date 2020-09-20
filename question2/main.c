#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define ARR_SZ(arr) (sizeof(arr) / sizeof(arr[0]))

uint8_t hexchar2val(uint8_t in) {
    const uint8_t letter = in & 0x40;
    const uint8_t shift = (letter >> 3) | (letter >> 6);
    return (in + shift) & 0xf;
}

bool isbreak(char c) { return c == '\0' || c == '\n'; }

int main(void) {
    char buf[5];
    size_t sz = 0;

    do {
        buf[sz] = getchar();
    } while (!isbreak(buf[sz]) && ++sz < ARR_SZ(buf) - 1);

    buf[sz] = '\0';

    uint32_t dig = 0;
    for (int i = 0; buf[i]; i++) {
        dig <<= 4;
        dig |= hexchar2val(buf[i]);
    }
    printf("%x\n", dig);
    return 0;
}
