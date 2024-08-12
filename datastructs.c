#include "datastructs.h"
#include <stdlib.h>

/* FUNCTION DEFINITIONS */
// Free a header completely. 
void freeHeader(dataHeader *d) {
    for(int i = 0; i < d->numColumns; i++)
        free(d->columnNames[i]);
    free(d->columnNames);
    free(d);
}

// Free a data array completely. 
void freeData(dayData *d, int setSize, int numColumns) {
    for(int i = 0; i < setSize; i++) {
        for(int j = 0; j < numColumns; j++)
            free(d[i].columnValues[j]);
        free(d[i].columnValues);
    }
    free(d);
}