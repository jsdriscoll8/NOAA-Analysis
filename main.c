#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "datastructs.h"

#define PATHLENLIM 100

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
dayData *gatherData(char *dataPath, int setSize) {
    // Setup: file pointer, 
    FILE *fptr = fopen(dataPath, "r");
    char *entry;
    size_t len = 0; 
    ssize_t line = 0; 
    int numEntriesAdded = 0; 
    dayData *dayEntries = malloc(setSize * sizeof(dayData));

    char inQuotes = 0;
    int i = 0;
    while((line = getline(&entry, &len, fptr)) != -1 && numEntriesAdded < setSize) {
        for(i = 0; i < strlen(entry); i++)
           printf("%c", entry[i]);
        numEntriesAdded++;
    }

    free(entry);
    fclose(fptr); 
    return dayEntries;
}

int main() {
    // Gather file path
    char *dataPath = getDataPath();
    printf("Selected file: %s\n", dataPath);

    // Get size of dataset.
    int setSize = getDataSize(); 
    printf("Selected dataset size: %d\n", setSize);

    // Gather data
    dayData *dayEntries = gatherData(dataPath, setSize);

    free(dataPath); 
    free(dayEntries); 
    return 0;
}
