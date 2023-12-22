#pragma once

#include "sudoku.h"

typedef struct {
    Cell *p_cells[2];
    int values[2];
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);