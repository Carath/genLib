#include <stdio.h>
#include <stdlib.h>
// #include <time.h> // for initializing the RNG.
// #include <math.h>

#include "GenLib.h"
#include "sinus_example.h"
#include "salesman.h"
#include "sales_gen.h"
#include "driver_TSPLIB.h"
#include "local_search.h"


void test_TSP(void);


int main(void)
{
	///////////////////////////////////////////////////////

	test_TSP();

	///////////////////////////////////////////////////////

	// sinus_example();

	///////////////////////////////////////////////////////

	return 0;
}


void test_TSP(void)
{
	// Same map each run:

	// DistanceRounding distMode = EXACT;
	DistanceRounding distMode = ROUNDED;

	// Map *map = createMap(50, RANDOM, distMode); // Same map every time!
	Map *map = getMapFromDataset("datasets/berlin52.tsp", distMode); // from TSPLIB
	// Map *map = getMapFromDataset("datasets/a280.tsp", distMode); // from TSPLIB

	// printMap(map);

	// For berlin52:
	int population_size = 1000;
	int epoch_number = 100000 * map -> CitiesNumber;

	// printf("%d\n", map -> CitiesNumber);

	// For a280:
	// int population_size = 512;
	// int epoch_number = 100000 * map -> CitiesNumber;


	// For berlin52:
	localSearch(NULL, map, 2 * population_size, 5.7 * epoch_number, STOCHASTIC);
	localSearch(NULL, map, 2 * population_size, 1 * epoch_number, GREEDY);

	float temperature = 0.1f;
	localSearch(&temperature, map, 1 * population_size, 2 * epoch_number, SA);
	localSearch(&temperature, map, 1 * population_size, 2 * epoch_number, TA);


	// For a280:
	// localSearch(NULL, map, population_size * 2, 12 * epoch_number, STOCHASTIC);
	// localSearch(NULL, map, population_size, 0.004 * epoch_number, GREEDY);

	// float temperature = 1.5f;
	// localSearch(&temperature, map, 0.5 * population_size, 6 * epoch_number, SA);
	// localSearch(&temperature, map, 0.5 * population_size, 6 * epoch_number, TA);


	///////////////////////////////////////////////////////
	// Without crossover:

	Species *species_1 = createSpecies(&GeneMeth_salesman_1, map, population_size);

	geneticSearch(species_1, epoch_number);

	double found_length_1 = pathLength(map, species_1 -> bestGene);

	printPath(species_1 -> bestGene, map -> CitiesNumber);
	printf("\nShortest found path: %.3f km\n", found_length_1);

	destroySpecies(&species_1);

	///////////////////////////////////////////////////////
	// With crossover 2:

	Species *species_2 = createSpecies(&GeneMeth_salesman_2, map, population_size / 4);

	geneticSearch(species_2, 0.5 * epoch_number);

	double found_length_2 = pathLength(map, species_2 -> bestGene);

	printPath(species_2 -> bestGene, map -> CitiesNumber);
	printf("\nShortest found path: %.3f km\n", found_length_2);

	destroySpecies(&species_2);

	///////////////////////////////////////////////////////
	// // With crossover 3:

	// Species *species_3 = createSpecies(&GeneMeth_salesman_3, map, population_size);

	// geneticSearch(species_3, epoch_number);

	// double found_length_3 = pathLength(map, species_3 -> bestGene);

	// printPath(species_3 -> bestGene, map -> CitiesNumber);
	// printf("\nShortest found path: %.3f km\n", found_length_3);

	// destroySpecies(&species_3);


	freeMap(&map);
}
