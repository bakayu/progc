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

// quick sort helper, gets the median of arr as pivot
int helper(int arr[], int low, int high) {
    int pivotValue = arr[low];

    int i = low, j = high;
    while (i < j) {
        while (i <= high && arr[i] <= pivotValue) {
            i++;
        }
        while (j >= low && arr[j] > pivotValue) {
            j--;
        }
        if (i < j)
            swap(&arr[i], &arr[j]);
    }

    swap(&arr[low], &arr[j]);
    return j;
}

// quick sort implementation
void quickSort(int arr[], int low, int high) {
    if (low >= high)
        return;

    int partitionIndex = helper(arr, low, high);
    quickSort(arr, low, partitionIndex - 1);
    quickSort(arr, partitionIndex + 1, high);
}

// Sorts the given array using Quicksort.
void applyQuickSort(int arr[], int size) { quickSort(arr, 0, size - 1); }

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
    applyQuickSort(arr, size);

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
    printf("Quicksort for random data (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateRandomArray(size);
        analyze(arr, size);
    }

    printf("Quicksort for data in Ascending order (execution time in ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateAscArray(size);
        analyze(arr, size);
    }

    printf("Quicksort for data in Descending order (execution time in "
           "ms):\n");
    for (int size = 8000; size <= 36000; size += 4000) {
        int *arr = generateDescArray(size);
        analyze(arr, size);
    }
    return 0;
}
