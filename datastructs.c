#include "datastructs.h"
#include <stdlib.h>

/* FUNCTION DEFINITIONS */
dayData *initDay(char *date, char **columnNames, float *columnValues, int *numColumns) {
    dayData *d = malloc(sizeof(dayData));
    d->date = date;
    d->columnNames = columnNames;
    d->columnValues = columnValues;
    d->numColumns = numColumns; 
    return d; 
}
