#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to determine if a report is strictly decreasing
int is_strictly_decreasing(int levels[], int size) {
    for (int i = 1; i < size; i++) {
        if (levels[i] >= levels[i - 1]) {
            return 0;  // Not strictly decreasing
        }
    }
    return 1;  // Strictly decreasing
}

// Function to determine if a report is safe using the Problem Dampener
int is_safe_with_dampener(int levels[], int size) {
    // Check if the report is already strictly decreasing
    if (is_strictly_decreasing(levels, size)) {
        return 1;
    }

    // Try removing each level one by one
    for (int i = 0; i < size; i++) {
        int temp[100]; // Temporary array to hold the modified report
        int temp_size = 0;

        // Copy all levels except the i-th one
        for (int j = 0; j < size; j++) {
            if (j != i) {
                temp[temp_size++] = levels[j];
            }
        }

        // Check if the modified report is strictly decreasing
        if (is_strictly_decreasing(temp, temp_size)) {
            return 1;  // Safe by removing this level
        }
    }

    return 0;  // Not safe even with the Problem Dampener
}

int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        perror("Error opening input.txt");
        return 1;
    }

    char line[1024];
    int safe_reports = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), input_file)) {
        int levels[100]; // Assuming no report has more than 100 levels
        int size = 0;

        // Parse integers from the line
        char *token = strtok(line, " ");
        while (token != NULL) {
            levels[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Check if the current report is safe with the Problem Dampener
        if (is_safe_with_dampener(levels, size)) {
            safe_reports++;
        }
    }

    fclose(input_file);

    // Print the number of safe reports
    printf("Number of safe reports: %d\n", safe_reports);

    return 0;
}
