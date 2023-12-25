#pragma once
#include "sudoku.h"

typedef struct HiddenPairs_impl {
    Cell **p_cells;
    int index;
    int values[2];
} HiddenPairs;

int hidden_pairs(SudokuBoard *board);

