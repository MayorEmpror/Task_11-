#include <stdio.h>
#include <stdlib.h>

void display_file_with_line_numbers(const char *filename) {
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        // If the file doesn't exist or can't be opened, print an error and exit
        perror("Error opening file");
        exit(1);
    }

    char line[1024]; // Buffer to store each line of the file
    int line_number = 1; // Initialize line number

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        // Print the line number and the corresponding line
        printf("%d: %s", line_number, line);
        line_number++; // Increment the line number for the next line
    }

    fclose(file); // Close the file when done
}

int main() {
    char filename[100];

    // Prompt the user for the filename
    printf("Enter the filename to read: ");
    scanf("%s", filename);

    // Display the file contents with line numbers
    display_file_with_line_numbers(filename);

    return 0;
}
