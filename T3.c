#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // For toupper()

void copy_file_with_uppercase(const char *source_filename, const char *destination_filename) {
    FILE *source_file = fopen(source_filename, "r"); // Open the source file in read mode
    if (source_file == NULL) {
        perror("Error opening source file");
        exit(1);
    }

    FILE *destination_file = fopen(destination_filename, "w"); // Open the destination file in write mode
    if (destination_file == NULL) {
        perror("Error opening destination file");
        fclose(source_file); // Don't forget to close the source file before exiting
        exit(1);
    }

    char ch;
    // Read each character from the source file
    while ((ch = fgetc(source_file)) != EOF) {
        // If it's a lowercase letter, convert to uppercase
        if (islower(ch)) {
            ch = toupper(ch);
        }
        
        // Write the processed character to the destination file
        if (fputc(ch, destination_file) == EOF) {
            perror("Error writing to destination file");
            fclose(source_file);
            fclose(destination_file);
            exit(1);
        }
    }

    printf("File copied successfully with lowercase characters converted to uppercase.\n");

    // Close both files
    fclose(source_file);
    fclose(destination_file);
}

int main() {
    char source_filename[100], destination_filename[100];

    // Ask user for the source and destination filenames
    printf("Enter the source filename: ");
    scanf("%s", source_filename);
    printf("Enter the destination filename: ");
    scanf("%s", destination_filename);

    // Call the function to copy the file and convert lowercase to uppercase
    copy_file_with_uppercase(source_filename, destination_filename);

    return 0;
}
