#include "main_aux.h"
#include "sudoku_board.h"

void aux_emptyArray(int *arr) {
    int i;
    for (i = 0; i < N*M; ++i) {
        arr[i] = 0;
    }
}
