#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*Comparator)(void *, void *);

void swap(void *left, void *right, int size) {
    void *buffer = malloc(size);
    memcpy(buffer, left, size);
    memcpy(left, right, size);
    memcpy(right, buffer, size);
    free(buffer);
}

/*
left == right :  0
left > right  :  1
left < right  : -1
*/
int cmpInt(void *left, void *right) {
    if (*(int *)left == *(int *)right)
        return 0;
    return *(int *)left > *(int *)right ? 1 : -1;
}

// for max heap this acts as siftDown
void heapify(void *arr, int size, int index, int elem_size, Comparator cmp) {
    int largest = index;
    int left = index * 2 + 1;
    int right = index * 2 + 2;

    if (left < size && (cmp((char *)arr + largest * elem_size,
                            (char *)arr + left * elem_size) < 0)) {
        largest = left;
    }
    if (right < size && (cmp((char *)arr + largest * elem_size,
                             (char *)arr + right * elem_size) < 0)) {
        largest = right;
    }

    if (largest != index) {
        swap((char *)arr + largest * elem_size, (char *)arr + index * elem_size,
             elem_size);
        heapify(arr, size, largest, elem_size, cmp);
    }
}

void heap_sort(void *arr, int size, int elem_size, Comparator cmp) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i, elem_size, cmp);
    }

    for (int i = size - 1; i >= 0; i--) {
        swap(arr, (char *)arr + i * elem_size, elem_size);
        heapify(arr, i, 0, elem_size, cmp);
    }
}

int main(void) {
    int arr[8] = {2, 8, 11, 12, 5, 34, 99, 0};
    printf("Input array: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // heapify demonstration:
    for (int i = 4; i >= 0; i--) {
        heapify(arr, 8, i, sizeof(int), cmpInt);
    }
    printf("Heapify: ");
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // heapsort demonstration:
    printf("heap sort: ");
    heap_sort(arr, 8, sizeof(int), cmpInt);
    for (int i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
