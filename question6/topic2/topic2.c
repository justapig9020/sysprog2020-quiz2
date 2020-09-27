#include <stdio.h>

// leetcode 137
int singleNumber(int *nums, int numsSize)
{
    int higher = 0, lower = 0;
    for (int i=0; i<numsSize; i++) {
        int l_buf = lower;
        lower = ~higher & (lower ^ nums[i]);
        higher = (higher & ~nums[i]) | (l_buf & nums[i]);
    }
    return lower;
}

int main(void) {
    int arr[] = {2, 2, 3, 2};
    printf("%d\n", singleNumber(arr, 4));
    return 0;
}
