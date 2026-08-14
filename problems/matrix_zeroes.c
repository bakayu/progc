#include <stdio.h>

void make_zeroes(int rows, int cols, int matrix[rows][cols]) {
    int first_row_zero = 0, first_col_zero = 0;
    for (int row = 0; row < rows; row++) {
        if (matrix[row][0] == 0)
            first_col_zero = 1;
    }
    for (int col = 0; col < cols; col++) {
        if (matrix[0][col] == 0)
            first_row_zero = 1;
    }

    for (int row = 1; row < rows; row++) {
        for (int col = 1; col < cols; col++) {
            if (matrix[row][col] == 0) {
                matrix[row][0] = 0;
                matrix[0][col] = 0;
            }
        }
    }

    for (int row = 1; row < rows; row++) {
        for (int col = 1; col < cols; col++) {
            if (matrix[row][0] == 0 || matrix[0][col] == 0) {
                matrix[row][col] = 0;
            }
        }
    }

    if (first_row_zero) {
        for (int col = 0; col < cols; col++) {
            matrix[0][col] = 0;
        }
    }
    if (first_col_zero) {
        for (int row = 0; row < rows; row++) {
            matrix[row][0] = 0;
        }
    }
}

void print_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
}

int main(void) {
    int test_case_1[3][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    int test_case_2[3][4] = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};

    printf("Test case 1 - before:\n");
    print_matrix(3, 3, test_case_1);
    make_zeroes(3, 3, test_case_1);
    printf("Test case 1 - after:\n");
    print_matrix(3, 3, test_case_1);

    printf("\nTest case 2 - before:\n");
    print_matrix(3, 4, test_case_2);
    make_zeroes(3, 4, test_case_2);
    printf("Test case 2 - after:\n");
    print_matrix(3, 4, test_case_2);

    return 0;
}
