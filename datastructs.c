#include <datastructs.h>
#include <stdlib.h>

/* FUNCTION DEFINITIONS */
dayData *init_day(char date[DATELEN], char **columnNames, float *columnValues, int numColumns) {
    dayData *d = malloc(sizeof(dayData));

    // Load date
    d->date = malloc(DATELEN * sizeof(char));
    for(int i = 0; i < DATELEN; i++) {
        d->date[i] = date[i];
    }
    
    // Load column names, values 
    d->columnNames = malloc(numColumns * sizeof(char*));
    d->columnValues = malloc(numColumns * sizeof(float)); 
    for(int i = 0; i < numColumns; i++) {
        d->columnNames[i] = columnNames[i];
        d->columnValues[i] = columnValues[i];
    }
    return d; 
}