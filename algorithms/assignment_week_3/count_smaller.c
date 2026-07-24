#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int original_idx;
} Element;

void merge(Element arr[], int left, int mid, int right, int counts[]) {
    Element temp[right - left + 1];
    int left_idx = left, right_idx = mid + 1, k = 0;
    int right_count = 0;

    while (left_idx <= mid && right_idx <= right) {
        if (arr[right_idx].val < arr[left_idx].val) {
            right_count++;
            temp[k++] = arr[right_idx++];
        } else {
            counts[arr[left_idx].original_idx] += right_count;
            temp[k++] = arr[left_idx++];
        }
    }

    while (left_idx <= mid) {
        counts[arr[left_idx].original_idx] += right_count;
        temp[k++] = arr[left_idx++];
    }

    while (right_idx <= right) {
        temp[k++] = arr[right_idx++];
    }

    for (int i = 0; i < right - left + 1; i++) {
        arr[left + i] = temp[i];
    }
}

void helper(Element arr[], int left, int right, int counts[]) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    helper(arr, left, mid, counts);
    helper(arr, mid + 1, right, counts);
    merge(arr, left, mid, right, counts);
}

int *countSmaller(int *nums, int n) {
    int *counts = (int *)calloc(n, sizeof(int));
    Element *arr = (Element *)malloc(n * sizeof(Element));

    for (int i = 0; i < n; i++) {
        arr[i].val = nums[i];
        arr[i].original_idx = i;
    }

    helper(arr, 0, n - 1, counts);

    free(arr);
    return counts;
}

int compareArrays(int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}
int main(void) {
    int test1[] = {5, 2, 6, 1};
    int expected1[] = {2, 1, 1, 0};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    int *res1 = countSmaller(test1, n1);

    if (compareArrays(res1, expected1, n1)) {
        printf("test case 1 passed.\n");
    } else {
        printf("test case 1 failed.\n");
    }
    free(res1);

    int test2[] = {-1};
    int expected2[] = {0};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    int *res2 = countSmaller(test2, n2);

    if (compareArrays(res2, expected2, n2)) {
        printf("test case 2 passed.\n");
    } else {
        printf("test case 2 failed.\n");
    }
    free(res2);

    int test3[] = {-1, -1};
    int expected3[] = {0, 0};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    int *res3 = countSmaller(test3, n3);

    if (compareArrays(res3, expected3, n3)) {
        printf("test case 3 passed.\n");
    } else {
        printf("test case 3 failed.\n");
    }
    free(res3);

    return 0;
}
