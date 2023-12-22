#include "hidden_pairs.h"
#include <stdlib.h>

// find hidden pair values (the values that are unique among all the candidates for a row, a collumn, or a box)
int find_hidden_pair_values(Cell **p_cells, int (*hidden_pair_values)[2])
{
    int counter = 0;
    int counts_candidate[BOARD_SIZE] = {0}; 
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        int *candidates = get_candidates(p_cells[i]);
        if (p_cells[i]->num_candidates > 1)
        {
            for (int j = 0; j < p_cells[i]->num_candidates; j++)
            {
                counts_candidate[candidates[j]-1]++;
            }
        }
        free(candidates);
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (counts_candidate[i] == 2)
        {
            for (int j = i + 1; j < BOARD_SIZE; j++)
            {
                if (counts_candidate[j] == 2)
                {
                    hidden_pair_values[counter][0] = i + 1;
                    hidden_pair_values[counter][1] = j + 1;
                    counter++;
                }
            }
        }
    }        
    return counter;
}

// find hidden pair cells in a row, in a collumn or in a box
void find_hidden_pair(Cell **p_cells, HiddenPair *p_hidden_pairs, int *p_counter)
{
    int hidden_pair_values[BOARD_SIZE][2];
    int num_hidden_pair_values = find_hidden_pair_values(p_cells, hidden_pair_values);

    for (int i = 0; i < num_hidden_pair_values; i++)
    {
        int pair_counter = 0;
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->num_candidates > 1)
            {
                int *candidates = get_candidates(p_cells[j]);
                for (int k = 0; k < p_cells[j]->num_candidates; k++)
                {
                    if (candidates[k] == hidden_pair_values[i][0] || candidates[k] == hidden_pair_values[i][1])
                    {
                        p_hidden_pairs[*p_counter].p_cells[pair_counter] = p_cells[j];
                        pair_counter++;
                        if (pair_counter == 2)
                        {
                            p_hidden_pairs[*p_counter].values[0] = hidden_pair_values[i][0];
                            p_hidden_pairs[*p_counter].values[1] = hidden_pair_values[i][1];
                            (*p_counter)++;
                            break;
                        }
                    }
                }
                free(candidates);  // free the memory allocated by get_candidates
            }
        }
    }
}

// find hidden pair cells in a board, return the number of hidden pair cells
int hidden_pairs(SudokuBoard *p_board)
{
    HiddenPair hidden_pairs[BOARD_SIZE * BOARD_SIZE];
    int counter = 0;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_hidden_pair(p_board->p_rows[i], hidden_pairs, &counter);
        find_hidden_pair(p_board->p_cols[i], hidden_pairs, &counter);
        find_hidden_pair(p_board->p_boxes[i], hidden_pairs, &counter);
    }

    int offset = 0;
    for (int i = 0; i < counter; i++)
    {
        Cell *cell1 = hidden_pairs[i].p_cells[0];
        Cell *cell2 = hidden_pairs[i].p_cells[1];
        int values[2] = {hidden_pairs[i].values[0], hidden_pairs[i].values[1]};
        if (cell1->num_candidates == 2 && cell2->num_candidates == 2 && 
            is_candidate(cell1, values[0]) && is_candidate(cell1, values[1]) && 
            is_candidate(cell2, values[0]) && is_candidate(cell2, values[1])) 
        {
            set_candidates(cell1, values, 2);
            set_candidates(cell2, values, 2);
            offset++;
        }
    }
    return offset;
}