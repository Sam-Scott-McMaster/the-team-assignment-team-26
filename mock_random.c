#include <stdio.h>
#include <stdlib.h>

static FILE *rand_file = NULL;

int rand() {
    if (rand_file == NULL) {
        rand_file = fopen("fake_random_numbers.txt", "r");
        if (rand_file == NULL) {
            fprintf(stderr, "Error: Could not open fake_random_numbers.txt\n");
            exit(EXIT_FAILURE);
        }
    }
    int value;
    if (fscanf(rand_file, "%d", &value) == 1) {
        return value;
    }
    // Fallback to a fixed value if the file ends unexpectedly
    return 42;
}

// Ensure the file is closed when the program exits
__attribute__((destructor)) void cleanup() {
    if (rand_file != NULL) {
        fclose(rand_file);
    }
}
