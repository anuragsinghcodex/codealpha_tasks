#include <stdio.h>

#define MAX 10

void readMatrix(int matrix[MAX][MAX], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            scanf("%d", &matrix[i][j]);
}

void printMatrix(int matrix[MAX][MAX], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            printf("%d\t", matrix[i][j]);
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            result[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX],
                      int r1, int c1, int c2) {
    int i, j, k;
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (k = 0; k < c1; k++)
                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

void transposeMatrix(int matrix[MAX][MAX], int result[MAX][MAX],
                     int rows, int cols) {
    int i, j;
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            result[j][i] = matrix[i][j];
}

int main() {
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX], trans[MAX][MAX];
    int r1, c1, r2, c2, choice;

    printf("===== Matrix Operations =====\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Transpose\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter rows and columns: ");
        scanf("%d %d", &r1, &c1);

        if (r1 > MAX || c1 > MAX || r1 <= 0 || c1 <= 0) {
            printf("Invalid matrix size.\n");
            return 0;
        }

        printf("Enter Matrix A:\n");
        readMatrix(a, r1, c1);
        printf("Enter Matrix B:\n");
        readMatrix(b, r1, c1);

        addMatrices(a, b, result, r1, c1);
        printf("\nA + B =\n");
        printMatrix(result, r1, c1);

    } else if (choice == 2) {
        printf("Enter rows and columns of Matrix A: ");
        scanf("%d %d", &r1, &c1);
        printf("Enter rows and columns of Matrix B: ");
        scanf("%d %d", &r2, &c2);

        if (r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0 ||
            r1 > MAX || c1 > MAX || r2 > MAX || c2 > MAX) {
            printf("Invalid matrix size.\n");
            return 0;
        }

        if (c1 != r2) {
            printf("Matrix multiplication not possible: columns of A must equal rows of B.\n");
            return 0;
        }

        printf("Enter Matrix A:\n");
        readMatrix(a, r1, c1);
        printf("Enter Matrix B:\n");
        readMatrix(b, r2, c2);

        multiplyMatrices(a, b, result, r1, c1, c2);
        printf("\nA x B =\n");
        printMatrix(result, r1, c2);

    } else if (choice == 3) {
        printf("Enter rows and columns: ");
        scanf("%d %d", &r1, &c1);

        if (r1 <= 0 || c1 <= 0 || r1 > MAX || c1 > MAX) {
            printf("Invalid matrix size.\n");
            return 0;
        }

        printf("Enter Matrix:\n");
        readMatrix(a, r1, c1);

        transposeMatrix(a, trans, r1, c1);
        printf("\nTranspose =\n");
        printMatrix(trans, c1, r1);

    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
