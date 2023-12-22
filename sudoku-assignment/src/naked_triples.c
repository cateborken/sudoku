#include "naked_triples.h"
#include <string.h>
#include "sudoku.h"
#include <stdlib.h>

int eliminate_candidates_ntriples(Cell **p_cells, int index1, int index2, int index3) {
    int counter = 0;

    // Get the naked triple candidates
    int* candidates = get_candidates(p_cells[index1]); // get_candidates returns a pointer

    // Eliminate the naked triple candidates from other cells in the group
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (i != index1 && i != index2 && i != index3 && p_cells[i]->value == 0) {       //also eliminate in other cells in group
            unset_candidate(p_cells[i],candidates[0]);
            unset_candidate(p_cells[i],candidates[1]);
            unset_candidate(p_cells[i],candidates[2]);
            counter++;
        }
    }

    free(candidates); // free the dynamically allocated memory

    return counter;
}

int are_naked_triples(Cell *cell1, Cell *cell2, Cell *cell3) {
    // Check if three cells have the same three candidates
    if (cell1->num_candidates == 3 && cell2->num_candidates == 3 && cell3->num_candidates == 3 && memcmp(cell1->candidates, cell2->candidates, BOARD_SIZE) && memcmp(cell1->candidates, cell3->candidates, BOARD_SIZE)){
        return 1;                       //must have 3 num_candidate (a triple) and the array is identical (memcmp)
    }
    return 0;
}

int check_naked_triples(Cell **p_cells) {
    int counter = 0;

    // Iterate through all triples of cells
    for (int i = 0; i < BOARD_SIZE - 2; i++) {
        for (int j = i + 1; j < BOARD_SIZE - 1; j++) {
            for (int k = j + 1; k < BOARD_SIZE; k++) {
                if (are_naked_triples(p_cells[i], p_cells[j], p_cells[k])) {
                    // Eliminate naked triple candidates from other cells in the group
                    counter += eliminate_candidates_ntriples(p_cells, i, j, k);
                }
            }
        }
    }

    return counter;
}

int naked_triples(SudokuBoard *p_board) {
    int counter = 0;

    // Check naked triples in rows, columns, and boxes
    for (int i = 0; i < BOARD_SIZE; i++) {
        counter += check_naked_triples(p_board->p_rows[i]);
        counter += check_naked_triples(p_board->p_cols[i]);
        counter += check_naked_triples(p_board->p_boxes[i]);
    }

    return counter;
}
