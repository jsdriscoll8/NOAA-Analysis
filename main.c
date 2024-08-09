#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "datastructs.h"

#define PATHLENLIM 100

/*
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
    
    int *numColumns = malloc(sizeof(int));
    *numColumns = 2; 

    // Construct the day
    dayData *d = init_day(testDate, columnNames, columnValues, numColumns);

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
    free(numColumns); 
    free(d); 
    return 0;
}
*/

// Gather an existing path to the database.
char *getDataPath() {
    char dataPath[PATHLENLIM]; 
    while(access(dataPath, F_OK) != 0) {
        printf("Enter the filepath to your dataset: ");
        scanf("%s", dataPath);
        if(access(dataPath, F_OK) != 0)
            printf("File not found!\n");
    }

    char *pointPath = malloc(PATHLENLIM * sizeof(char));
    strcpy(pointPath, dataPath);
    return pointPath; 
}

// Get the size of the data set.
int getDataSize() {
    int setSize = -1;
    while(setSize <= 0) {
        char checkInt[PATHLENLIM];
        printf("Enter the size of the dataset (must be positive): ");
        scanf("%s", checkInt);
        char isNum = 1; 
        for(int i = 0; i < strlen(checkInt); i++) {
            if(!isdigit(checkInt[i])) {
                printf("Invalid input!\n"); 
                isNum = 0;
                break;
            }
        }
        if(isNum == 1)
            sscanf(checkInt, "%d", &setSize);
    }

    return setSize; 
}

// Gather the entries from the dataset. 
void gatherData(char *dataPath, int setSize) {
    FILE *fptr = fopen(dataPath, 'r');

    fclose(fptr); 
}

int main() {
    // Gather file path
    char *dataPath = getDataPath();
    printf("Selected file: %s\n", dataPath);

    // Get size of dataset.
    int setSize = getDataSize(); 
    printf("Selected dataset size: %d\n", setSize);

    gatherData(dataPath, setSize);

    free(dataPath); 
    return 0;
}
