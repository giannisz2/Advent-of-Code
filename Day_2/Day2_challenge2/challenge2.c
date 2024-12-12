#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to check if a report is safe
bool is_safe(int* report, int size) {
    bool increasing = true;
    bool decreasing = true;

    // Loop through the report to check the conditions
    for (int i = 0; i < size - 1; i++) {
        int diff = abs(report[i] - report[i + 1]);

        // Check if the difference is out of range [1, 3]
        if (diff < 1 || diff > 3) {
            return false; // Unsafe due to the difference out of range
        }

        // Check if the sequence is strictly increasing or decreasing
        if (report[i] >= report[i + 1]) {
            increasing = false;
        }
        if (report[i] <= report[i + 1]) {
            decreasing = false;
        }
    }

    // The report is safe if it is either strictly increasing or strictly decreasing
    return increasing || decreasing;
}

// Function to check if removing a single level makes the report safe
bool is_safe_with_removal(int* report, int size) {
    for (int i = 0; i < size; i++) {
        // Create a new array without the current level
        int new_report[size - 1];
        int new_index = 0;
        for (int j = 0; j < size; j++) {
            if (j != i) {
                new_report[new_index++] = report[j];
            }
        }

        // Check if the new report (after removing the level) is safe
        if (is_safe(new_report, size - 1)) {
            return true; // The report becomes safe after removing this level
        }
    }
    return false; // No single removal made the report safe
}

int main() {
    FILE* file = fopen("input.txt", "r"); // Open the input file
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[256]; // Buffer to read each line
    int safe_count = 0;

    // Read each line from the file
    while (fgets(line, sizeof(line), file)) {
        int report[256];  // Array to store levels of the report
        int size = 0;

        // Parse the line into integers (split by spaces)
        char* token = strtok(line, " \n");
        while (token != NULL) {
            report[size++] = atoi(token);  // Convert string to integer and store in report
            token = strtok(NULL, " \n");
        }

        // Check if the report is safe or can be made safe by removing one level
        if (is_safe(report, size) || is_safe_with_removal(report, size)) {
            safe_count++;
        }
    }

    // Output the number of safe reports
    printf("Number of safe reports: %d\n", safe_count);

    fclose(file); // Close the file
    return 0;
}
