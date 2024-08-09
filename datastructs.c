#include "datastructs.h"
#include <stdlib.h>

/* FUNCTION DEFINITIONS */

// Initialize a dayData pointer and return it.
dayData *initDay(char *date, float *columnValues, int numColumns) {
    dayData *d = malloc(sizeof(dayData));
    d->date = date;
    d->columnValues = columnValues;
    d->numColumns = numColumns; 
    return d; 
}

// Free the contained values of day.
void freeDay(dayData *d) {
    free(d->columnValues);
}