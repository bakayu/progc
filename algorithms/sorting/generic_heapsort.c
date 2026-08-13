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

int cmpFloat(void *left, void *right) {
    if (*(float *)left == *(float *)right)
        return 0;
    return *(float *)left > *(float *)right ? 1 : -1;
}

int cmpChar(void *left, void *right) {
    if (*(char *)left == *(char *)right)
        return 0;
    return *(char *)left > *(char *)right ? 1 : -1;
}

int cmpString(void *left, void *right) {
    return strcmp(*(char **)left, *(char **)right);
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

void print_int_arr(int *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void print_float_arr(float *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
}

void print_char_arr(char *arr, int size) {
    for (int i = 0; i < size; i++)
        printf("'%c' ", arr[i]);
    printf("\n");
}

void print_string_arr(char **arr, int size) {
    for (int i = 0; i < size; i++)
        printf("'%s' ", arr[i]);
    printf("\n");
}

int main(void) {
    int arr_int[] = {2, 8, 11, 12, 5, 34, 99, 0};
    printf("int array before: ");
    print_int_arr(arr_int, sizeof(arr_int) / sizeof(arr_int[0]));
    heap_sort(arr_int, sizeof(arr_int) / sizeof(arr_int[0]), sizeof(int),
              cmpInt);
    printf("int array after: ");
    print_int_arr(arr_int, sizeof(arr_int) / sizeof(arr_int[0]));
    printf("\n");

    float arr_float[] = {0.5, 24.5, 6.9, 6.7, 100.0, 0.0, 1.0, 78.78};
    printf("float array before: ");
    print_float_arr(arr_float, sizeof(arr_float) / sizeof(arr_float[0]));
    heap_sort(arr_float, sizeof(arr_float) / sizeof(arr_float[0]),
              sizeof(float), cmpFloat);
    printf("float array after: ");
    print_float_arr(arr_float, sizeof(arr_float) / sizeof(arr_float[0]));
    printf("\n");

    char arr_char[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
    printf("char array before: ");
    print_char_arr(arr_char, sizeof(arr_char) / sizeof(arr_char[0]));
    heap_sort(arr_char, sizeof(arr_char) / sizeof(arr_char[0]), sizeof(char),
              cmpChar);
    printf("char array after: ");
    print_char_arr(arr_char, sizeof(arr_char) / sizeof(arr_char[0]));
    printf("\n");

    char *arr_str[] = {"hello world", "this is a string in C", "abcd", "0-9/="};
    printf("string array before: ");
    print_string_arr(arr_str, sizeof(arr_str) / sizeof(arr_str[0]));
    heap_sort(arr_str, sizeof(arr_str) / sizeof(arr_str[0]), sizeof(char *),
              cmpString);
    printf("string array after: ");
    print_string_arr(arr_str, sizeof(arr_str) / sizeof(arr_str[0]));

    return 0;
}
