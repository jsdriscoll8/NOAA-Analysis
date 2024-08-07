/* CONSTANTS */
#define DATELEN 11

/* STRUCT DEFINITIONS */
// Base data struct. Contains a date and a number of columns and their associated data points.
typedef struct day{
    char *date; 
    char **columnNames;
    float *columnValues;
} dayData;

/* FUNCTION TEMPLATES */
dayData *init_day(char date[DATELEN], char **columnNames, float *columnValues, int numColumns); 
