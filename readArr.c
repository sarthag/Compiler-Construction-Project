#include <stdio.h>

int First[74][59];
int Follow[74][59];

#define ROWS 74
#define COLS 59

int main() {
    FILE *g = fopen("firstArr.txt", "r");
    
    // read each line of the file and store its contents in the array
    for (int i = 0; i < ROWS; i++) {
        char line[256];
        fgets(line, sizeof(line), g);
        
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
    printf("   ");
    for (int i = 0; i < COLS; i++) {
        printf("%02d ", i);
    }
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%02d ", i);
        for (int j = 0; j < COLS; j++) {
            printf(" %d ", First[i][j]);
        }
        printf("\n");
    }
    
    // close the file
    fclose(g);

    // FILE *h = fopen("followArr.txt", "r");
    
    // // read each line of the file and store its contents in the array
    // for (int i = 0; i < ROWS; i++) {
    //     char line[256];
    //     fgets(line, sizeof(line), h);
        
    //     // split the line into an array of integers
    //     char *token;
    //     int j = 0;
    //     token = strtok(line, ",");
    //     while (token != NULL) {
    //         Follow[i][j] = atoi(token);
    //         j++;
    //         token = strtok(NULL, ",");
    //     }
    // }
    
    // // print the contents of the array
    // for (int i = 0; i < ROWS; i++) {
    //     for (int j = 0; j < COLS; j++) {
    //         printf("%d ", Follow[i][j]);
    //     }
    //     printf("\n");
    // }
    
    // // close the file
    // fclose(h);
}