#include "hidden_pairs.h"
#include <stdio.h>
#include <stdlib.h>

int hidden_pairs(SudokuBoard *p_board) {
    int counter = 0;
    HiddenPairs p_hidden_pairs[BOARD_SIZE * BOARD_SIZE * 9];

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *cell = p_board->p_rows[i][j];
            if (cell->num_candidates != 2) continue;

            for (int k = j + 1; k < BOARD_SIZE; k++) {
                Cell *next_cell = p_board->p_rows[i][k];
                if (next_cell->num_candidates != 2) continue;

                if (cell->candidates[0] == next_cell->candidates[0] && cell->candidates[1] == next_cell->candidates[1]) {
                    p_hidden_pairs[counter].p_cells[0] = cell;
                    p_hidden_pairs[counter].p_cells[1] = next_cell;
                    p_hidden_pairs[counter].values[0] = cell->candidates[0];
                    p_hidden_pairs[counter].values[1] = cell->candidates[1];
                    counter++;
                }
            }
        }
    }

    for (int i = 0; i < counter; i++) {
        Cell **p_cells = p_hidden_pairs[i].p_cells;
        set_candidates(p_cells[0], p_hidden_pairs[i].values, 2);
        set_candidates(p_cells[1], p_hidden_pairs[i].values, 2);
    }

    return counter;
}
