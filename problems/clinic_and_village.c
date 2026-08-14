#include <stdio.h>

int feasible(int population[], int n, int x, int k) {
    long long total = 0;
    for (int i = 0; i < n; i++) {
        total += (population[i] + x - 1) / x; // ceil(population[i] / x)
        if (total > k)
            return 0;
    }
    return total <= k;
}

int minMaxLoad(int population[], int n, int k) {
    int l = 1;
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (population[i] > r)
            r = population[i];
    }

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (feasible(population, n, mid, k)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return l;
}

int main(void) {
    int population[] = {200, 20, 50};
    int n = 3;
    int k = 5;

    printf("%d\n", minMaxLoad(population, n, k));
    return 0;
}
