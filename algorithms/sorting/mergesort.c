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

// merge sort helper
void helper(int arr[], int low, int mid, int high) {
    int temp[high - low + 1];

    int i = low;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= high) {
        temp[k++] = arr[j++];
    }

    k = 0;
    for (int idx = low; idx <= high; idx++) {
        arr[idx] = temp[k++];
    }
}

// merge sort implementation
void mergeSort(int arr[], int low, int high) {
    if (low >= high)
        return;

    int mid = low + (high - low) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);

    helper(arr, low, mid, high);
}

// Sorts the given array using Mergesort
void applyMergeSort(int arr[], int size) { mergeSort(arr, 0, size - 1); }

// Returns true if the array is sorted, otherwise false.
bool verifySort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1])
            return false;
    }

    return true;
}

// Analyses the time taken
void analyze(int arr[], int size) {
    // Start timer
    clock_t start = clock();

    // Apply sorting algorithm
    applyMergeSort(arr, size);

    // Stop timer
    clock_t end = clock();

    // Calculate execution time
    double executionTime = (double)(end - start) / CLOCKS_PER_SEC;

    if (!verifySort(arr, size)) {
        printf("Failed: array not sorted.");
        exit(-1);
    }

    printf("%.3f\n", executionTime * 1000);

    // Free dynamically allocated memory
    free(arr);
}

int main() {
    printf("Merge sort for random data (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateRandomArray(size);
        analyze(arr, size);
    }

    printf("Merge sort for data in Ascending order (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateAscArray(size);
        analyze(arr, size);
    }

    printf("Merge sort for data in Descending order (execution time in "
           "ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateDescArray(size);
        analyze(arr, size);
    }
    return 0;
}
