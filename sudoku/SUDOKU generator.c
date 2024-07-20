#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define SIZE 9
void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            printf("%2d ", grid[row][col]);
        }
        printf("\n");
    }
}

void writeGridToFile(int grid[SIZE][SIZE], const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open file %s\n", filename);
        return;
    }
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            fprintf(file, "%d ", grid[row][col]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

bool isSafe(int grid[SIZE][SIZE], int row, int col, int num) {
    for (int x = 0; x < SIZE; x++)
        if (grid[row][x] == num || grid[x][col] == num)
            return false;

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool fillGrid(int grid[SIZE][SIZE], int row, int col) {
    if (row == SIZE - 1 && col == SIZE)
        return true;
    if (col == SIZE) {
        row++;
        col = 0;
    }
    if (grid[row][col] != 0)
        return fillGrid(grid, row, col + 1);

    for (int num = 1; num <= SIZE; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (fillGrid(grid, row, col + 1))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}
void removeKDigits(int grid[SIZE][SIZE], int k) {
    while (k > 0) {
        int cellId = rand() % (SIZE * SIZE);
        int row = cellId / SIZE;
        int col = cellId % SIZE;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            k--;
        }
    }
}
void generateSudoku(int grid[SIZE][SIZE], int k) {
    fillGrid(grid, 0, 0);
    removeKDigits(grid, k);
}
int main() {
    srand(time(0));
    int grid[SIZE][SIZE] = {0};
    int k = 20;
    generateSudoku(grid, k);
    printGrid(grid);
    const char *filename = "sudoko_input.txt";
    writeGridToFile(grid, filename);
    printf("Sudoku puzzle written to %s\n", filename);

    return 0;
}

