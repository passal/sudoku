#include <stdlib.h>
#include <stdio.h>
#include "sudoku_board.h"

SudokuBoard* sb_createSudokuBoard(int rows, int columns){
    int i;
    SudokuBoard* res = (SudokuBoard*) malloc(sizeof(SudokuBoard));
    if (!res){ /* allocation failed */
        printf("Error: %s has failed\n", "sb_createSudokuBoard");
        exit(1);
    }
    res->rows = rows;
    res->columns = columns;
    for (i = 0; i < BOARD_SIZE; ++i){
        res->cells[i] = (Cell*)calloc(1, sizeof(Cell));
        if(!res->cells[i]){ /* allocation failed */
            printf("Error: %s has failed\n", "sb_createSudokuBoard");
            exit(1);
        }
    }
    return res;
}

void sb_print(SudokuBoard* sb) {
    int i;
    printf("----------------------------------\n");
    for (i = 0; i < BOARD_SIZE; ++i){
        if (i % (N*M*M) == 0 && i != 0)
            printf("|\n----------------------------------\n| ");
        else if (i % (N*M) == 0 && i != 0)
            printf("|\n| ");
        else if (i % N == 0) {
            printf("| ");
        }
        if (sb->cells[i]->value) {
            if (sb->cells[i]->fixed)
                printf(".");
            else
                printf(" ");
            printf("%d ", sb->cells[i]->value);
        } else {
            printf("   ");
        }
    }
    printf("|\n----------------------------------\n");

}

void sb_removeUnfixedCells(SudokuBoard *sb){
    int i;
    for (i = 0; i < BOARD_SIZE; ++i){
        if (sb->cells[i]->fixed == 0){
            sb->cells[i]->value = 0;
        }
    }
}

SudokuBoard* sb_deepCloneBoard(SudokuBoard *template_sb){
    int i,j;
    SudokuBoard* new_sb = sb_createSudokuBoard(template_sb->rows, template_sb->columns);
    for (i = 0; i < BOARD_SIZE; ++i){
        new_sb->cells[i]->value = template_sb->cells[i]->value;
        new_sb->cells[i]->fixed = template_sb->cells[i]->fixed;
        /* clone impossible values array of cell */
        for (j = 0; j < (N*M); ++j){
            new_sb->cells[i]->impossible_values[j] = template_sb->cells[i]->impossible_values[j];
        }
    }
    return new_sb;
}

void destroyCell(Cell* c) {
    free(c);
}

void sb_destroyBoard(SudokuBoard* sb) {
    int i = 0;
    for (i = 0; i < BOARD_SIZE; i++) {
        destroyCell(sb->cells[i]);
    }
    free(sb);
}


/*
 * This functions checks if the sudoku board is full, i.e there are no cells with value '0'.
 * @return: 1 if full, 0 if not full
 */
int sb_isFull(SudokuBoard *sb){
    int i;
    for (i = 0; i < BOARD_SIZE; ++i){
        if (sb->cells[i]->value == 0){
            return 0;
        }
    }
    return 1;
}


