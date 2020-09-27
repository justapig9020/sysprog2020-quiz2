#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define REP 3
#define JUNK 5
#define ARR_SZ(arr) (sizeof(arr)/sizeof(arr[0]))

int buf_len(int n) {
    return (int)log2((double)n) + 1;
}

int single_num(int nums[], int sz, int times) {
    int len = buf_len(times);
    printf("len: %d\n", len);
    int *state = malloc(sizeof(int) * len);
    int *mask = malloc(sizeof(int) * len);

    for (int i=0; i<len; i++)
        state[i] = 0;

    for (int i=0; i<len; i++) {
        mask[i] = !!(times & (1 << i)) * -1;
        printf("%x\n", mask[i]);
    }

    for (int i=0; i<sz; i++) {
        int chk = -1;
        int carry = nums[i];
        for (int j=0; j<len; j++) {
            int c_buf = carry & state[j];
            state[j] ^= carry;
            carry = c_buf;
            chk &= ~(state[j]^mask[j]);
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
