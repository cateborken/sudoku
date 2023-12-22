#include "hidden_triples.h"
#include <string.h>
#include "sudoku.h"
#include <stdlib.h>

int eliminate_candidates_htriples(Cell **p_cells, int index1, int index2, int index3) {
    int counter = 0;

    // Get the hidden triple candidates
    int* candidates = get_candidates(p_cells[index1]); // get_candidates returns a pointer

    // Eliminate the hidden triple candidates from the cells forming the hidden triple
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i != candidates[0] && i != candidates[1] && i != candidates[2] && p_cells[i]->value == 0) {
            unset_candidate(p_cells[index1],i);
            unset_candidate(p_cells[index2],i);
            unset_candidate(p_cells[index3],i);
            counter++;
        }
    }

    free(candidates); // free the dynamically allocated memory

    return counter;
}

int are_hidden_triples(Cell *cell1, Cell *cell2, Cell *cell3) {
    // Check if three cells have the same three candidates
    if (cell1->num_candidates > 2 && cell2->num_candidates > 2 && cell3->num_candidates > 2 && memcmp(cell1->candidates, cell2->candidates, BOARD_SIZE) && memcmp(cell1->candidates, cell3->candidates, BOARD_SIZE)){
        return 1;                       //must have more than 2 num_candidate and the array is identical (memcmp)
    }
    return 0;
}

int check_hidden_triples(Cell **p_cells) {
    int counter = 0;

    // Iterate through all triples of cells
    for (int i = 0; i < BOARD_SIZE - 2; i++) {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++) {
            for (int k = j + 1; k < BOARD_SIZE; k++) {
                if (are_hidden_triples(p_cells[i], p_cells[j], p_cells[k])) {
                    // Eliminate hidden triple candidates from the cells forming the hidden triple
                    counter += eliminate_candidates_htriples(p_cells, i, j, k);
                }
            }
        }
    }

    return counter;
}

int hidden_triples(SudokuBoard *p_board) {
    int counter = 0;

    // Check hidden triples in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        counter += check_hidden_triples(p_board->p_rows[i]);
        counter += check_hidden_triples(p_board->p_cols[i]);
        counter += check_hidden_triples(p_board->p_boxes[i]);
    }

    return counter;
}
