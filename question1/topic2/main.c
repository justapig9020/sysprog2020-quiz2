#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#define ARR_SIZE(a) (sizeof(a) / sizeof(a[0]))

const uint64_t MASK = 0x0101010101010101;
char BUF[100];

bool isalph_char(char c) {
    c |= 0x20;
    char lz = c + (0x80 - 'z' - 1);
    char ga = c + (0x80 - 'a');
    return ((lz ^ ga) & 0x80) == 0x80;
}

bool isalph_ward(uint64_t w) {
    w |= 0x20 * MASK;
    uint64_t lz = w + (0x80 - 'z' - 1) * MASK;
    uint64_t ga = w + (0x80 - 'a') * MASK;
    return ((lz ^ ga) & (0x80 * MASK)) == (0x80 * MASK);
}

bool isalph_str(char str[], size_t size) {
    bool alph = true;

    printf("size: %zu\n", size);
    while (alph && size >= 8) {
        alph = isalph_ward(*(uint64_t*)str);
        str += sizeof(uint64_t);
        size -= 8;
    }

    while (alph && size) {
        alph = isalph_char(*str);
        str++;
        size--;
    }

    return alph;
}

bool isbreak(char c) { return c == '\0' || c == '\n'; }

int main(void) {
    size_t i = 0;
    do {
        BUF[i] = getchar();
    } while (i < ARR_SIZE(BUF) - 1 && !isbreak(BUF[i++]));
    BUF[i] = '\0';

    bool alph = isalph_str(BUF, i - 1);

    if (alph)
        puts("Shark!!!");
    else
        puts("A");
    return 0;
}
