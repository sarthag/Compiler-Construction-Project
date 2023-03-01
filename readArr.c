#include <stdio.h>

int First[74][59];
int Follow[74][59];

#define ROWS 74
#define COLS 59

int main()
{
    FILE *f = fopen("firstArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < ROWS; i++) {
        char line[256];
        fgets(line, sizeof(line), f);
        
        // split the line into an array of integers
        char *token;
        int j = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            First[i][j] = atoi(token);
            j++;
            token = strtok(NULL, ",");
        }
    }
    
    // print the contents of the array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", First[i][j]);
        }
        printf("\n");
    }
    
    // close the file
    fclose(f);

    FILE *f = fopen("followArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < ROWS; i++) {
        char line[256];
        fgets(line, sizeof(line), f);
        
        // split the line into an array of integers
        char *token;
        int j = 0;
        token = strtok(line, ",");
        while (token != NULL) {
            Follow[i][j] = atoi(token);
            j++;
            token = strtok(NULL, ",");
        }
    }
    
    // print the contents of the array
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", Follow[i][j]);
        }
        printf("\n");
    }
    
    // close the file
    fclose(f);
}