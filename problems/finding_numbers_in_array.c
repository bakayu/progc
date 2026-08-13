/*
Given an Array of size n. It has integers where all the numbers are repeated 3
times but one number is repeated 4 times. Write a code to find the number
repeating 4 times.

Constraints:

    size of array: 0 > n > 10^5
    Each element i : 0 < i < n
    Expected Run time complexity: O(n)
    Expected Space complexity: O(1)

Example:

    input: [1, 2, 3, 4, 1, 2, 4, 1, 2, 3, 4, 3, 3]
    Expected output: 3
    Explanation: 3 comes 4 times but others are 3 times in array.
*/

#include <stdio.h>

int helper(int arr[], int size) {
    int ones = 0;
    int twos = 0;
    for (int i = 0; i < size; i++) {
        int num = arr[i];

        twos |= (ones & num);
        ones ^= num;

        int threes = ones & twos;

        ones &= ~threes;
        twos &= ~threes;
    }

    return ones;
}

int main(void) {
    int test_case[] = {1, 2, 3, 4, 1, 2, 4, 1, 2, 3, 4, 3, 3};
    int size = sizeof(test_case) / sizeof(test_case[0]);

    printf("result: %d\n", helper(test_case, size));

    return 0;
}
