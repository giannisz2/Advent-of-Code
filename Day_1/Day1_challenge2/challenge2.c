#include <stdio.h>
#include <stdlib.h>

void count_number(int* similarity, int second_col[], int number, int index) {
    int counter = 0;
    for(int i = 0; i < 1000; i++) {
        if(number == second_col[i])
            counter++;
    }
    similarity[index] = counter;

}
int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    if(input_file == NULL) {
        perror("Error opening file.");
        return 1;
    }

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

    int first_col[1000], second_col[1000];
    for(int i = 0; i < 1000; i++) {
        first_col[i] = numbers_in_list[i][0];
        second_col[i] = numbers_in_list[i][1];
    }

    int index = 0;
    int* number_similarity = malloc(1000*sizeof(int));
    for(int i = 0; i < 1000; i++) {
        count_number(number_similarity, second_col, first_col[i], index);
        index++;
    }

    int total_sum = 0;
    for(int i = 0; i < 1000; i++) {
        total_sum += first_col[i] * number_similarity[i];
    }

    printf("Similarity score is: %d", total_sum);
    return 0;
}
