#include "naked_triples.h"
#include <stdlib.h>

typedef struct {
    int val1;
    int val2;
    int val3;
} Triple;

int triple_exists(Triple *triples, int triple_count, int val1, int val2, int val3) {
    for (int i = 0; i < triple_count; i++) {
        if ((triples[i].val1 == val1 || triples[i].val1 == val2 || triples[i].val1 == val3) &&
            (triples[i].val2 == val1 || triples[i].val2 == val2 || triples[i].val2 == val3) &&
            (triples[i].val3 == val1 || triples[i].val3 == val2 || triples[i].val3 == val3)) {
            return 1;
        }
    }
    return 0;
}

int naked_triples(SudokuBoard *p_board) {
    Triple triples[BOARD_SIZE * BOARD_SIZE];
    int triple_count = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell *cell = &(p_board->data[i][j]);
            if (cell->num_candidates != 3)
                continue;

            int *candidates = get_candidates(cell);

            // Check row, column, and box
            for (int unitType = 0; unitType < 3; unitType++) {
                Cell **unit;
                switch (unitType) {
                    case 0:
                        unit = p_board->p_rows[i];
                        break;
                    case 1:
                        unit = p_board->p_cols[j];
                        break;
                    case 2:
                        unit = p_board->p_boxes[(i / 3) * 3 + j / 3];
                        break;
                }

                for (int k = 0; k < BOARD_SIZE; k++) {
                    if (unit[k] == cell)
                        continue;

                    Cell *other = unit[k];
                    if (other->num_candidates != 3)
                        continue;

                    int *other_candidates = get_candidates(other);
                    if ((candidates[0] == other_candidates[0] || candidates[0] == other_candidates[1] || candidates[0] == other_candidates[2]) &&
                        (candidates[1] == other_candidates[0] || candidates[1] == other_candidates[1] || candidates[1] == other_candidates[2]) &&
                        (candidates[2] == other_candidates[0] || candidates[2] == other_candidates[1] || candidates[2] == other_candidates[2])) {
                        if (!triple_exists(triples, triple_count, candidates[0], candidates[1], candidates[2])) {
                            triples[triple_count].val1 = candidates[0];
                            triples[triple_count].val2 = candidates[1];
                            triples[triple_count].val3 = candidates[2];
                            triple_count++;
                        }
                        for (int l = 0; l < BOARD_SIZE; l++) {
                            if (unit[l] == cell || unit[l] == other)
                                continue;

                            Cell *remove = unit[l];
                            if (is_candidate(remove, candidates[0])) {
                                unset_candidate(remove, candidates[0]);
                            }
                            if (is_candidate(remove, candidates[1])) {
                                unset_candidate(remove, candidates[1]);
                            }
                            if (is_candidate(remove, candidates[2])) {
                                unset_candidate(remove, candidates[2]);
                            }
                        }
                    }
                    free(other_candidates);
                }
            }
            free(candidates);
        }
    }
    return triple_count;
}
