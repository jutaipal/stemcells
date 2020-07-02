// RADIAL SPREAD STEM CELL SIMULATOR
//  simulator.c
//  
//
//  Created by Jussi Taipale on 10/07/2019.
//

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)>(b))?(b):(a))

short int winner = 60;
short int number_of_stem_cells = 6;
short int stemcell[50];
long int counter;
long int number_of_cell_divisions = 1000;
long int number_of_iterations = 100000;
long int wins = 0;
long int losses = 0;
long int iteration = 0;
long int cell_division = 0;
short int mutant_stem_cells = 1;
short int current_mutant_stem_cells;
short int current_stem_cell;
short int mutant_winners;
long int total_cell_divisions = 0;
long int total_wins = 0;
short int radial_start_position;
short int state;

int main (int argc, char *argv[])
{

for (winner = 0; winner < 101; winner++)
{
    
for(wins = 0, losses = 0, iteration = 0; iteration < number_of_iterations; iteration++)
{
    // initialize stem cells
    for(counter = 0; counter <= number_of_stem_cells; counter++) {stemcell[counter] = 0;}
    stemcell[rand() % 6] = 1;
    
    for(cell_division = 0; cell_division < number_of_cell_divisions; cell_division++)
    {
        // set pairs
        radial_start_position = rand() % 2;
        
        for(current_stem_cell = radial_start_position, mutant_winners = 0; current_stem_cell < number_of_stem_cells; current_stem_cell += 2)
        {
        // continue if both stem cells are the same type
            if (stemcell[current_stem_cell] == stemcell[current_stem_cell+1]) continue;
        // check if mutant stem cell wins over neighbor or wild-type wins over mutant
        state = 0;
        if (rand() % 100 < winner) state = 1;
        {
        // winner spreads to both sites
            stemcell[current_stem_cell] = state;
            stemcell[current_stem_cell+1] = state;
        // CARRY to rotate
        if (current_stem_cell == 0) stemcell[number_of_stem_cells] = state;
        if (current_stem_cell + 1 == number_of_stem_cells) stemcell[0] = state;
        }
        }
        
        for (current_mutant_stem_cells = 0, current_stem_cell = 0; current_stem_cell < number_of_stem_cells; current_stem_cell++) current_mutant_stem_cells += stemcell[current_stem_cell];
        
        if (current_mutant_stem_cells == 0 || current_mutant_stem_cells == number_of_stem_cells) break;
    }
    if(current_mutant_stem_cells == 0) losses++;
    if(current_mutant_stem_cells == number_of_stem_cells)
    {
    wins++;
    total_wins++;
    total_cell_divisions++;
    total_cell_divisions += cell_division;
    }
}
printf("\nTakeover percentage %.2f\%% at cell win percentage %i\%% after average of %.1f divisions", 100 * (float) wins / (float) number_of_iterations, winner, (float) total_cell_divisions / (float) total_wins);
    
}
printf("\n");
exit(0);
}

