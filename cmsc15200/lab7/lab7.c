#include <stdlib.h>
#include <stdio.h>

int **create_array(unsigned int rows, unsigned int cols) {
    int **matrix = (int**)malloc(sizeof(int*) * rows);
    for (unsigned int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * cols);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    return matrix;
}

void free_array(int **matrix, unsigned int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_array(int **matrix, unsigned int rows, unsigned int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void scale(int **matrix, unsigned int rows, unsigned int cols, int scale_by) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] *= scale_by;
        }
    }
}


int search(int **matrix, unsigned int rows, unsigned int cols,
           int search_for, int *found_row, int *found_col) {
    *found_row = -1;
    *found_col = -1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == search_for) {
                *found_row = i;
                *found_col = j;
                return 1;
            }
        }
    }
    return 0;
}

int *sum_rows(int **matrix, unsigned int rows, unsigned int cols) {
    int *new_mat = (int *)malloc(sizeof(int)*rows);
    for (int i = 0; i < rows; i++) {
        new_mat[i] = 0;
        for (int j = 0; j < cols; j++) {
            new_mat[i] += matrix[i][j];
        }
    }
    return new_mat;
}

int **create_triangle(unsigned int rows) {
    int **mat = (int **)malloc(sizeof(int *)*rows);
    for (int i = 0; i < rows; i++) {
        mat[i] = (int *)malloc(sizeof(int) * (rows - i));
        for (int j = 0; j < rows - i; j++) {
            mat[i][j] = j+1;
        }
    }
    return mat;
}


int main() {
    int **my_mat = create_array(4, 5);
    print_array(my_mat, 4, 5);
    scale(my_mat, 4, 5, 3);
    print_array(my_mat, 4, 5);
    printf("\n");
    int found_row = 0;
    int found_col = 0;
    printf("%d\n", search(my_mat, 4, 5, 90, &found_row, &found_col));
    printf("%d, %d\n", found_row, found_col); 
    printf("%d\n", search(my_mat, 4, 5, 1, &found_row, &found_col));
    printf("%d, %d\n", found_row, found_col);
    int *sum = sum_rows(my_mat, 4, 5);
    for (int i = 0; i < 4; i++) {
        printf("%d ", sum[i]);
    }
    printf("\n");
    int** triangle = create_triangle(5);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5 - i; j++) {
            printf("%d ", triangle[i][j]); 
        }
        printf("\n");
    }
    free_array(my_mat, 4);
    free_array(triangle, 5);
    free(sum);
    return 0;
}

