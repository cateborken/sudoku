#include "naked_pairs.h"
#include <stdlib.h>

int naked_pairs(SudokuBoard *p_board)
{
    int found = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cell *cell = &(p_board->data[i][j]);
            if (cell->num_candidates != 2)
                continue;

            int *candidates = get_candidates(cell);

            // Check row
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (k == j)
                    continue;

                Cell *other = &(p_board->data[i][k]);
                if (other->num_candidates != 2)
                    continue;

                int *other_candidates = get_candidates(other);
                if (candidates[0] == other_candidates[0] && candidates[1] == other_candidates[1])
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (l == j || l == k)
                            continue;

                        Cell *remove = &(p_board->data[i][l]);
                        if (is_candidate(remove, candidates[0]))
                        {
                            unset_candidate(remove, candidates[0]);
                            found++;
                        }
                        if (is_candidate(remove, candidates[1]))
                        {
                            unset_candidate(remove, candidates[1]);
                            found++;
                        }
                    }
                }
                free(other_candidates);
            }

            // Check column
            for (int k = 0; k < BOARD_SIZE; k++)
            {
                if (k == i)
                    continue;

                Cell *other = &(p_board->data[k][j]);
                if (other->num_candidates != 2)
                    continue;

                int *other_candidates = get_candidates(other);
                if (candidates[0] == other_candidates[0] && candidates[1] == other_candidates[1])
                {
                    for (int l = 0; l < BOARD_SIZE; l++)
                    {
                        if (l == i || l == k)
                            continue;

                        Cell *remove = &(p_board->data[l][j]);
                        if (is_candidate(remove, candidates[0]))
                        {
                            unset_candidate(remove, candidates[0]);
                            found++;
                        }
                        if (is_candidate(remove, candidates[1]))
                        {
                            unset_candidate(remove, candidates[1]);
                            found++;
                        }
                    }
                }
                free(other_candidates);
            }

            // Check box
            int start_row = (i / 3) * 3;
            int start_col = (j / 3) * 3;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    if (start_row + k == i && start_col + l == j)
                        continue;

                    Cell *other = &(p_board->data[start_row + k][start_col + l]);
                    if (other->num_candidates != 2)
                        continue;

                    int *other_candidates = get_candidates(other);
                    if (candidates[0] == other_candidates[0] && candidates[1] == other_candidates[1])
                    {
                        for (int m = 0; m < 3; m++)
                        {
                            for (int n = 0; n < 3; n++)
                            {
                                if ((start_row + m == i && start_col + n == j) || (start_row + m == start_row + k && start_col + n == start_col + l))
                                    continue;

                                Cell *remove = &(p_board->data[start_row + m][start_col + n]);
                                if (is_candidate(remove, candidates[0]))
                                {
                                    unset_candidate(remove, candidates[0]);
                                    found++;
                                }
                                if (is_candidate(remove, candidates[1]))
                                {
                                    unset_candidate(remove, candidates[1]);
                                    found++;
                                }
                            }
                        }
                    }
                    free(other_candidates);
                }
            }

            free(candidates);
        }
    }
    return found;
}
