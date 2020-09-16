#include <stdbool.h>
#include <stdio.h>

bool isalph(char c) {
    c |= 0x20;
    char lz = c + (128 - 'z' - 1);
    char ga = c + (128 - 'a');
    return (lz ^ ga) & 0x80;
}

int main(void) {
    char c;
    c = getchar();
    if (isalph(c))
        puts("Shark!");
    else
        puts("Nooo");
    return 0;
}
