
#include <stdio.h>
#include <stdbool.h>
#define N 9
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%2d ", grid[row][col]);
        printf("\n");
    }
}
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}
bool solveSudoku(int grid[N][N], int row, int col) {

    if (row == N - 1 && col == N)
        return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= N; num++) {

        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid, row, col + 1))
                return true;
        }
        grid[row][col] = 0;
    }
    return false;
}
void readGridFromFile(const char *filename, int grid[N][N]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            fscanf(file, "%d", &grid[row][col]);
        }
    }
    fclose(file);
}
int main() {
    int grid[N][N];
    readGridFromFile("sudoko_input.txt", grid);
    if (solveSudoku(grid, 0, 0))
        printGrid(grid);
    else
        printf("No solution exists");

    return 0;
}

