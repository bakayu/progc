#include <stdio.h>
#include <time.h>

int sum_even_fibonacci_brute_force(int n) {
    int a = 1, b = 1;
    int sum = 0;

    while (a <= n) {
        if (a % 2 == 0) {
            sum += a;
        }

        int next = a + b;
        a = b;
        b = next;
    }

    return sum;
}

int sum_even_fibonacci_optimized(int n) {
    if (n < 2) {
        return 0;
    }

    int sum = 0;
    int even1 = 2;
    int even2 = 8;

    while (even1 <= n) {
        sum += even1;

        int next_even = 4 * even2 + even1;
        even1 = even2;
        even2 = next_even;
    }

    return sum;
}

int main(void) {
    int n;
    clock_t start, end;
    double time_used;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    start = clock();
    int brute_force_sum = sum_even_fibonacci_brute_force(n);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Brute Force Sum: %d (Time: %f seconds)\n", brute_force_sum,
           time_used);

    start = clock();
    int optimized_sum = sum_even_fibonacci_optimized(n);
    end = clock();
    time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Optimized Sum: %d (Time: %f seconds)\n", optimized_sum, time_used);

    return 0;
}
