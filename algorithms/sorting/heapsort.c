#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generates an array of random integers of given size.
int *generateRandomArray(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
    return arr;
}

// Generates an array of given size in Ascending order
int *generateAscArray(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    return arr;
}

// Generates an array of given size in Descending order
int *generateDescArray(int size) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    return arr;
}

// swap two integers in an array
void swap(int *ptr1, int *ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

// helper for heap sort
void helper(int arr[], int size, int idx) {
    int max = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < size && arr[left] > arr[max]) {
        max = left;
    }

    if (right < size && arr[right] > arr[max]) {
        max = right;
    }

    if (max != idx) {
        swap(&arr[idx], &arr[max]);
        helper(arr, size, max);
    }
}

// Sorts the given array using Heap Sort.
void applyHeapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        helper(arr, size, i);
    }

    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        helper(arr, i, 0);
    }
}

// Analyses the time taken
void analyze(int arr[], int size) {
    // Start timer
    clock_t start = clock();

    // Apply sorting algorithm
    applyHeapSort(arr, size);

    // Stop timer
    clock_t end = clock();

    // Calculate execution time
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%.3f\n", executionTime * 1000);

    // Free dynamically allocated memory
    free(arr);
}

int main() {
    printf("Heap sort for random data (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateRandomArray(size);
        analyze(arr, size);
    }

    printf("Heap sort for data in Ascending order (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateAscArray(size);
        analyze(arr, size);
    }

    printf("Heap sort for data in Descending order (execution time in "
           "ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateDescArray(size);
        analyze(arr, size);
    }
    return 0;
}
