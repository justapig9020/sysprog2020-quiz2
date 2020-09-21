#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 100
bool is_ascii(const char str[], size_t size) {
    if (size == 0) return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080) return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80) return false;
        i++;
    }
    return true;
}

bool is_break(char c) { return c == '\0' || c == '\n'; }

size_t get_str(char buf[], size_t len) {
    size_t i = 0;
    while (1) {
        buf[i] = getchar();
        if (is_break(buf[i])) {
            buf[i] = '\0';
            return i;
        }
        if (++i == len) break;
    }
    buf[--i] = '\0';
    return i;
}

int main(void) {
    char buf[BUFSIZE];
    while (1) {
        size_t size = get_str(buf, BUFSIZE);
        if (strncmp(buf, "exit", size) == 0) break;
        if (is_ascii(buf, size))
            puts("Is ascii");
        else
            puts("Isn't ascii");
    }
    return 0;
}
