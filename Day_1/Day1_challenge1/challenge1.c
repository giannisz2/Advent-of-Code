#include <stdio.h>
#include <stdlib.h>

#include "quicksort.h"

int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    if(input_file == NULL) {
        perror("Error opening file.");
        return 1;
    }

    // Read the numbers from the file
    int numbers_in_list[1000][2];
    int row = 0;
    while(row < 1000) {
        fscanf(input_file, "%d %d", &numbers_in_list[row][0], &numbers_in_list[row][1]);
        row++;
    }

    fclose(input_file);

    //Print the numbers to verify
    printf("Read %d rows:\n", row);
    for (int i = 0; i < row; i++) {
        printf("%d %d\n", numbers_in_list[i][0], numbers_in_list[i][1]);
    }

    // Place the numbers in different arrays so we can sort them
    int first_col[1000], second_col[1000];
    for(int i = 0; i < 1000; i++) {
        first_col[i] = numbers_in_list[i][0];
        second_col[i] = numbers_in_list[i][1];
    }

    // Find last index of array and sort them using quicksort
    int n = sizeof(first_col) / sizeof(first_col[0]);
    quickSort(first_col, 0, n-1);
    quickSort(second_col, 0, n-1);

    printf("\nArrays sorted\n");
    for(int i = 0; i < 1000; i++) {
        printf("%d %d\n", first_col[i], second_col[i]);
    }

    // Calculate the total sum
    int total_sum = 0;
    for(int i = 0; i < 1000; i++) {
        int distance = abs(first_col[i] - second_col[i]);
        total_sum += distance;
    }

    printf("\nThe total distance is: %d", total_sum);

    return 0;
}
