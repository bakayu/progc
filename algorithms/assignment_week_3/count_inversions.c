#include <stdio.h>

int countInversions(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main(void) {
    int testCase1[] = {1, 2, 4, 1, 3, 5};
    int testCase2[] = {2, 3, 4, 5, 6};

    if (countInversions(testCase1, 0, 5) == 3) {
        printf("test case 1 passed.\n");
    } else {
        printf("test case 1 failed.\n");
    }

    if (countInversions(testCase2, 0, 4) == 0) {
        printf("test case 2 passed.\n");
    } else {
        printf("test case 2 failed.\n");
    }

    return 0;
}

int countInversions(int arr[], int left, int right) {
    if (left >= right) {
        return 0;
    }

    int count = 0;
    int mid = left + (right - left) / 2;
    count += countInversions(arr, left, mid);
    count += countInversions(arr, mid + 1, right);

    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && arr[i] > arr[j])
            j++;
        count += (j - mid - 1);
    }

    merge(arr, left, mid, right);

    return count;
}

void merge(int arr[], int left, int mid, int right) {
    int temp[right - left + 1];
    int k = 0, left_idx = left, right_idx = mid + 1;

    while (left_idx <= mid && right_idx <= right) {
        if (arr[left_idx] < arr[right_idx]) {
            temp[k] = arr[left_idx++];
        } else {
            temp[k] = arr[right_idx++];
        }
        k++;
    }

    while (left_idx <= mid)
        temp[k++] = arr[left_idx++];
    while (right_idx <= right)
        temp[k++] = arr[right_idx++];

    for (int i = 0; i < right - left + 1; i++) {
        arr[i + left] = temp[i];
    }
}
