#include "datastructs.h"
#include <stdlib.h>

/* FUNCTION DEFINITIONS */
void freeHeader(dataHeader *d){
    for(int i = 0; i < MAXNUMCOLS; i++)
        free(d->columnNames[i]);
    free(d->columnNames);
    free(d);
}