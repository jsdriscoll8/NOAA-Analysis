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

// TODO: Reconfigure so that header mallocs based on # of quotes!
dataHeader *getHeader(char *dataPath) {
    // Open first line of file, set getline vars, set loop fars, get number of cols. 
    FILE *fptr = fopen(dataPath, "r");
    char *entry;
    size_t len = 0; 
    ssize_t line = 0;
    line = getline(&entry, &len, fptr);
    int i = 0, inQuotes = 0, curCol = 0, curChar = 0, totalCols = 0;
    while(entry[i] != '\n') {
        if(entry[i] == '"')
            totalCols++;
        i++;
    }
    i = 0; 
    char **columnNames = malloc(totalCols * sizeof(char *));

    // Run through the first line of file char by char. Get column names.
    while(entry[i] != '\n') {
        // printf("%c", entry[i]);
        // Keep track of when we are inside of quotes, e.g. a column value.
        // We don't want a contained comma to escape a column.
        
        if(entry[i] == '"') {
            // Switch to inQuotes. Malloc a new char *.
            if(inQuotes == 0) {
                inQuotes = 1;
                columnNames[curCol] = malloc(MAXCOLLEN * sizeof(char)); 
            }
            // End of column value. Terminate the value, append numCols, reset inQuotes & curChar. 
            else {
                columnNames[curCol][curChar + 1] = '\0'; 
                curCol++;
                curChar = 0, inQuotes = 0;
            }
        }
        // If we're in quotes, append the column value.
        else if(inQuotes == 1) {
            columnNames[curCol][curChar] = entry[i];
            curChar++;
        }
        i++;
    }

    // Free, close, construct the header & return it. 
    free(entry);
    fclose(fptr); 
    dataHeader *d = malloc(sizeof(dataHeader));
    d->columnNames = columnNames;
    d->numColumns = curCol;
    return d;
}

// Gather the entries from the dataset. 
dayData *gatherData(char *dataPath, int setSize, int numColumns) {
    // Setup: file pointer, loop vars
    FILE *fptr = fopen(dataPath, "r");
    char *entry, *token;
    const char c[2] = "\""; 
    size_t len = 0; 
    ssize_t line = 0; 
    int numEntriesAdded = 0, column = 0; 
    dayData *entries = malloc(setSize * sizeof(dayData));

    // Loop: feed in column data. Skip the first line (header) 
    line = getline(&entry, &len, fptr);
    while((line = getline(&entry, &len, fptr)) != -1 && numEntriesAdded < setSize) {
        // 0. Setup 
        char **columnValues = malloc(numColumns * sizeof(char *));

        // 1. Parse the line with strtok
        token = strtok(entry, c);
        while(token != NULL) {
            if(token != ",") {
                char *column = malloc(MAXCOLLEN * sizeof(char));
                printf("%s ", token);
                column++;
            }
        }
        print(" "); 

        // 3. Place inside of dayDatas.
        entries[numEntriesAdded].columnValues = columnValues; 
        // 4. Return. 
        printf("\n");
        numEntriesAdded++;
        column = 0;
    }

    // Free and return.
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

    // Build header, print columns.
    dataHeader *header = getHeader(dataPath); 
    int j = 0;
    printf("DATA COLUMNS: "); 
    for(int i = 0; i < header->numColumns; i++) {
        j = 0;
        while(header->columnNames[i][j] != '\0') {
            printf("%c", header->columnNames[i][j]);
            j++; 
        }
        printf(" "); 
    }
    printf("\n"); 

    // Get data values.
    dayData *data = gatherData(dataPath, setSize, header->numColumns); 

    // Free and finish.
    free(dataPath); 
    freeHeader(header);
    for(int i = 0; i < setSize; i++)
        freeData(data, setSize, header->numColumns);
    return 0;
}