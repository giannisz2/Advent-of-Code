#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to determine if a report is safe
int is_safe_report(int levels[], int size) {
    int is_increasing = 1;
    int is_decreasing = 1;

    for (int i = 1; i < size; i++) {
        if (levels[i] > levels[i - 1]) {
            is_decreasing = 0;  // It's not decreasing
        }
        if (levels[i] < levels[i - 1]) {
            is_increasing = 0;  // It's not increasing
        }

        // Check if the difference between adjacent levels is between 1 and 3
        int diff = abs(levels[i] - levels[i - 1]);
        if (diff < 1 || diff > 3) {
            return 0;  // If the difference is out of range, the report is unsafe
        }
    }

    // Return true if either increasing or decreasing
    return is_increasing || is_decreasing;
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
        int levels[100];
        int size = 0;

        // Parse integers from the line
        char *token = strtok(line, " ");
        while (token != NULL) {
            levels[size++] = atoi(token);
            token = strtok(NULL, " ");
        }

        // Check if the current report is safe
        if (is_safe_report(levels, size)) {
            safe_reports++;
        }
    }

    fclose(input_file);

    // Print the number of safe reports
    printf("Number of safe reports: %d\n", safe_reports);

    return 0;
}
