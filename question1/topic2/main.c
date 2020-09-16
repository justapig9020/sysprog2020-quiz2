#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

const uint64_t MASK = 0x0101010101010101;

bool isalph(uint64_t w) {
    w |= 0x20 * MASK;
    uint64_t lz = w + (0x80 - 'z' - 1) * MASK;
    uint64_t ga = w + (0x80 - 'a') * MASK;
    return ((lz ^ ga) & (0x80 * MASK)) == (0x80 * MASK);
}

void veri_ward(uint64_t w) {
    if (isalph(w))
        puts("Shark!");
    else
        puts("Nooo");
}

int main(void) {
    char *test1 = "abC1eFGH";
    char *test2 = "abCdeFGH";

    veri_ward(*(uint64_t *)test1);
    veri_ward(*(uint64_t *)test2);

    return 0;
}
