/* CONSTANTS */
#define DATELEN 11
#define MAXNUMCOLS 10

/* STRUCT DEFINITIONS */
// Base data struct. Contains a date and a number of columns and their associated data points.
typedef struct day{
    char **columnValues;
    int numColumns; 
} dayData;

typedef struct header {
    char **columnNames;
    int numColumns;
} dataHeader;

// Free the contained pointers within the header.
void freeHeader(dataHeader *d);

void freeData(dayData *d, int setSize, int numColumns);