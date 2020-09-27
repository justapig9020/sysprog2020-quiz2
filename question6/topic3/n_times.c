#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define REP 11
#define JUNK 5
#define ARR_SZ(arr) (sizeof(arr)/sizeof(arr[0]))

bool is_pow2(int n) {
    return n>2 && !(n & (n-1));
}

int buf_len(int n) {
    return (int)log2((double)n) + !is_pow2(n);
}

int single_num(int nums[], int sz, int times) {
    int len = buf_len(times);
    printf("Buf len: %d\n", len);
    int *state = malloc(sizeof(int) * len);
    int *mask = malloc(sizeof(int) * len);

    for (int i=0; i<len; i++)
        state[i] = 0;

    times--;
    for (int i=0; i<len; i++) {
        mask[i] = !!(times & (1 << i)) * -1;
        printf("%x\n", mask[i]);
    }

    for (int i=0; i<sz; i++) {
        int carry = nums[i];
        int chk = carry;
        for (int j=0; j<len; j++) {
            chk &= ~(state[j]^mask[j]);
            int c_buf = carry & state[j];
            state[j] ^= carry;
            carry = c_buf;
        }
        for (int j=0; j<len; j++)
            printf("ST%d %x\n", j, state[j]);
        printf("CHK %x\n\n", chk);
        chk = ~chk;
        for (int j=0; j<len; j++) {
            state[j] &= chk;
        }
    }
    int rst = state[0];
    free(state);
    free(mask);
    return rst;
}

int main(void) {
    int arr[JUNK * REP + 1];
    int i;
    for (i=0; i<ARR_SZ(arr)-1; i++)
        arr[i] = i/REP + 1;
    arr[i] = JUNK+1;
    for (i=0; i<ARR_SZ(arr)-1; i++)
        printf("%d\n", arr[i]);

    int rst = single_num(arr, ARR_SZ(arr), REP);
    if (JUNK+1 == rst)
        puts("Pass");
    else
        printf("Fail, rst: %d\n", rst);
    return 0;
}
