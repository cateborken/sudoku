#pragma once

#include "sudoku.h"

int hidden_triples(SudokuBoard *p_board);
int find_hidden_triples(Cell **p_cells, int index1, int index2, int index3);