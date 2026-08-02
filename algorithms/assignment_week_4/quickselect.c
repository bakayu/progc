#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot_idx = low + rand() % (high - low + 1);
    swap(&arr[pivot_idx], &arr[high]);

    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }
    swap(&arr[i], &arr[high]);
    return i;
}

void quickselect(int arr[], int low, int high, int k) {
    while (low <= high) {
        int p = partition(arr, low, high);
        if (p == k - 1) {
            return;
        } else if (p > k - 1) {
            high = p - 1;
        } else {
            low = p + 1;
        }
    }
}

int *generateRandomArray(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = rand();
    return arr;
}

int *generateAscArray(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = i;
    return arr;
}

int *generateDescArray(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = size - i;
    return arr;
}

void analyze(int *arr, int size) {
    int k = size / 2;

    clock_t start = clock();
    quickselect(arr, 0, size - 1, k);
    clock_t end = clock();

    double elapsed_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("%d, %.4f\n", size, elapsed_ms);

    free(arr);
}

int main() {
    srand((unsigned int)time(NULL));

    printf("Quickselect for random data (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateRandomArray(size);
        analyze(arr, size);
    }

    printf(
        "\nQuickselect for data in Ascending order (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateAscArray(size);
        analyze(arr, size);
    }

    printf(
        "\nQuickselect for data in Descending order (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateDescArray(size);
        analyze(arr, size);
    }

    return 0;
}
