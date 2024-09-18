#include <stdio.h>

int main() {
    char line[256];
    FILE *file;

    // Open the file for reading (replace "ASCII.txt" with the file you want to print)
    file = fopen("ASCII.txt", "r");

    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Read and print each line from the file using fgets and fprintf
    while (fgets(line, sizeof(line), file) != NULL) {
        fprintf(stdout, "%s", line); // Print the line to standard output
    }

    // Close the file
    fclose(file);

    return 0;
}



