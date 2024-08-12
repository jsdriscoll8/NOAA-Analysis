#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "datastructs.h"


// -------------------------- CONSTANT DEFINITIONS ----------------------------------------------------
#define PATHLENLIM 100
#define MAXCOLLEN 50

// -------------------------- FUNCTION DEFINITIONS ----------------------------------------------------
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

dataHeader *getHeader(char *dataPath) {
    // Open first line of file, set getline vars
    FILE *fptr = fopen(dataPath, "r");
    char *entry;
    size_t len = 0; 
    ssize_t line = 0;
    char **columnNames = malloc(MAXNUMCOLS * sizeof(char *));
    line = getline(&entry, &len, fptr);
    int i = 0, inQuotes = 0, numCols = 0, curChar = 0;

    // Run through the first line of file char by char. Get column names.
    while(entry[i] != '\n') {
        // printf("%c", entry[i]);
        // Keep track of when we are inside of quotes, e.g. a column value.
        // We don't want a contained comma to escape a column.
        
        if(entry[i] == '"') {
            // Switch to inQuotes. Malloc a new char *.
            if(inQuotes == 0) {
                inQuotes = 1;
                columnNames[numCols] = malloc(MAXCOLLEN * sizeof(char)); 
                printf("Now in quotes.\n");
            }
            // End of column value. Terminate the value, append numCols, reset inQuotes & curChar. 
            else {
                columnNames[numCols][curChar + 1] = '\0'; 
                numCols++;
                curChar = 0, inQuotes = 0;
                printf("Now out of quotes.\n");
            }
        }
        // If we're in quotes, append the column value.
        else if(inQuotes == 1) {
            columnNames[numCols][curChar] = entry[i];
            curChar++;
        }
        i++;
    }

    // Free, close, construct the header & return it. 
    free(entry);
    fclose(fptr); 
    dataHeader *d = malloc(sizeof(dataHeader));
    d->columnNames = columnNames;
    return d;
}

// Gather the entries from the dataset. 
dayData *gatherData(char *dataPath, int setSize) {
    // Setup: file pointer, 
    FILE *fptr = fopen(dataPath, "r");
    char *entry;
    size_t len = 0; 
    ssize_t line = 0; 
    int numEntriesAdded = 0; 
    dayData *entries;

    while((line = getline(&entry, &len, fptr)) != -1 && numEntriesAdded < setSize) {
    }

    free(entry);
    fclose(fptr); 
    return entries;
}


// -------------------------------- MAIN LOOP ----------------------------------------------------------
int main() {
    // Gather file path
    char *dataPath = getDataPath();
    printf("Selected file: %s\n", dataPath);

    // Get size of dataset.
    int setSize = getDataSize(); 
    printf("Selected dataset size: %d\n", setSize);

    // Build header
    dataHeader *header = getHeader(dataPath);

    free(dataPath); 
    freeHeader(header);
    return 0;
}