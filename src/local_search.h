#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H


#include "salesman.h"


#define STOPPING_THRESHOLD 0.01
#define SA_TEMP_MULTIPLIER 0.99f

#define SAVE_BEST_PATH 1 // only for SA as of now.


typedef enum {STOCHASTIC, GREEDY, SA, TA} localSearchMode;

// N.B: temperature seem better as floats (instead of doubles) for some reason...


// Local search using 2-op heuristic. Returns the best found length:
double localSearch(const void *context, const Map *map, int population_size, int epoch_number, localSearchMode mode);


#endif
