#include <stdio.h>

// int getReverseSignificantPairs(int arr[], int size);
int getReverseSignificantPairs(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

int main(void) {
    int testCase1[] = {1, 3, 2, 3, 1};
    int testCase2[] = {2, 4, 3, 5, 1};

    if (getReverseSignificantPairs(testCase1, 0, 4) == 2) {
        printf("test case 1 passed.\n");
    } else {
        printf("test case 1 failed.\n");
    }

    if (getReverseSignificantPairs(testCase2, 0, 4) == 3) {
        printf("test case 2 passed.\n");
    } else {
        printf("test case 2 failed.\n");
    }

    return 0;
}

int getReverseSignificantPairs(int arr[], int left, int right) {
    if (left >= right) {
        return 0;
    }

    int count = 0;
    int mid = left + (right - left) / 2;
    count += getReverseSignificantPairs(arr, left, mid);
    count += getReverseSignificantPairs(arr, mid + 1, right);

    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && (long long)arr[i] > 2LL * arr[j])
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

// NOTE: Brute force O(n^2)
// int getReverseSignificantPairs(int arr[], int size) {
//     int res = 0;
//     for (int i = 0; i < size; i++) {
//         for (int j = i + 1; j < size; j++) {
//             if (arr[i] > 2 * arr[j])
//                 res++;
//         }
//     }

//     return res;
// }
