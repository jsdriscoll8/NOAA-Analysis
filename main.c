#include <stdio.h>
#include <stdlib.h>
#include "datastructs.h"

int main() {
    
    return 0;
}

int test() {
    // Test day struct
    char testDate[DATELEN] = "2023-08-30";
    char **columnNames = malloc(2 * sizeof(char *));
    char *column1 = malloc(5 * sizeof(char));
    char *column2 = malloc(5 * sizeof(char));
    
    // Build column 1 name
    column1[0] = 't';
    column1[1] = 'e';
    column1[2] = 'm';
    column1[3] = 'p';
    column1[4] = '\0';
    columnNames[0] = column1;

    // Build column 2 name
    column2[0] = 'w';
    column2[1] = 'i';
    column2[2] = 'n';
    column2[3] = 'd';
    column2[4] = '\0';
    columnNames[1] = column2;

    // Build the values
    float *columnValues = malloc(2 * sizeof(float));
    columnValues[0] = 77.0;
    columnValues[1] = 5.0;

    // Construct the day
    dayData *d = malloc(sizeof(dayData));
    d = init_day(testDate, columnNames, columnValues, 2);

    // Print 
    int i = 0;
    while(d->columnNames[1][i] != '\0') {
        printf("%c", d->columnNames[1][i]);
        i++;
    }
    printf("\n");

    free(columnNames);
    free(column1);
    free(column2); 
    return 0;
}