/* CONSTANTS */
#define DATELEN 11

/* STRUCT DEFINITIONS */
// Base data struct. Contains a date and a number of columns and their associated data points.
typedef struct day{
    char *date; 
    char **columnNames;
    float *columnValues;
    int numColumns; 
} dayData;

typedef struct info{
    char *location;
    char **columnNames; 
} header;

/* FUNCTION TEMPLATES */
dayData *initDay(char *date, float *columnValues, int numColumns); 

header *buildHeader(char *location, char **columnNames); 
