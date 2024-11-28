#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4
#define MAX_TRIES 10

typedef struct {
    const char *object;
    const char *trait;
} objectTrait;

void makeBoard(char *board[SIZE][SIZE], char *traitsBoard[SIZE][SIZE]) {
    const objectTrait hardcodedPairs[SIZE * SIZE / 2] = {
        {"Crown", "Royalty"}, {"Scepter", "Royalty"},
        {"Fur Coat", "Elegance"}, {"Necklace", "Elegance"},
        {"Tentacles", "Power"}, {"Staff", "Power"},
        {"Mirror", "Glamour"}, {"Heels", "Glamour"}
    };

    int index = 0;
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            board[r][c] = (char *)hardcodedPairs[index / 2].object;
            traitsBoard[r][c] = (char *)hardcodedPairs[index / 2].trait;
            index++;
        }
    }
}

void showBoard(char *board[SIZE][SIZE], int shown[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%2d        ", i); // Column header
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i); // Row header
        for (int j = 0; j < SIZE; j++) {
            if (shown[i][j]) {
                printf("%-10s ", board[i][j] ? board[i][j] : "[??]");
            } else {
                printf("[?]       ");
            }
        }
        printf("\n");
    }
}

int isMatch(const char *trait1, const char *trait2) {
    return strcmp(trait1, trait2) == 0;
}

int main() {

    for (int game = 0; game < 2; game++) {  // Run the game twice
        printf("Welcome to Disney Villain Memory Match!\n\n");

        char *board[SIZE][SIZE] = {NULL};
        char *traitsBoard[SIZE][SIZE] = {NULL};
        int shown[SIZE][SIZE] = {0};

        FILE *memoryMatch_score = fopen("memoryMatch_score.txt", "w");

        printf("\nGame %d\n", game + 1);
        
        makeBoard(board, traitsBoard);
        showBoard(board, shown);

        float points = 0.0;
        int tries = 0;
        int matches = 0;

        while (matches < SIZE * SIZE / 2) {
            if (tries >= MAX_TRIES) {
                printf("\nYou've reached the maximum number of tries (%d). Game over!\n", MAX_TRIES);
                printf("Your final score: %.2f\n", points);
                fprintf(memoryMatch_score, "%.2f\n", points / tries);
                break;
            }

            int r1, c1, r2, c2;

            while (1) {
                printf("Enter the coordinates of the first object(row col): ");
                if (scanf("%d %d", &r1, &c1) == 2 && 
                    r1 >= 0 && r1 < SIZE && c1 >= 0 && c1 < SIZE &&
                    !shown[r1][c1]) {
                    break;
                }
                printf("Invalid input. Try again.\n");
                while (getchar() != '\n');
            }

            while (1) {
                printf("Enter the coordinates of the second object(row col): ");
                if (scanf("%d %d", &r2, &c2) == 2 && 
                    r2 >= 0 && r2 < SIZE && c2 >= 0 && c2 < SIZE &&
                    !shown[r2][c2] && !(r1 == r2 && c1 == c2)) {
                    break;
                }
                printf("Invalid input. Try again.\n");
                while (getchar() != '\n');
            }

            shown[r1][c1] = 1;
            shown[r2][c2] = 1;
            showBoard(board, shown);

            if (isMatch(traitsBoard[r1][c1], traitsBoard[r2][c2])) {
                printf("Matched objects: %s and %s\n", board[r1][c1], board[r2][c2]);
                printf("Trait: %s\n", traitsBoard[r1][c1]);
                points += 1.0;
                matches++;
            } else {
                printf("No match. Try again.\n");
                shown[r1][c1] = 0;
                shown[r2][c2] = 0;
                points -= 0.25;
                if (points < 0.0) {
                    points = 0.0;
                }
            }

            tries++;
            printf("Current points: %.2f\n", points);
            printf("Efficiency: %.2f points/turn\n", points / tries);
            printf("Remaining tries: %d\n", MAX_TRIES - tries);
        }

        if (matches == (SIZE * SIZE / 2) && tries <= MAX_TRIES) {
            printf("\nCongratulations! You matched all objects in %d tries.\n", tries);
            printf("Your final points is %.2f.\n", points);
        }

        printf(" %.2f \n", points / tries);
        fprintf(memoryMatch_score, "%.2f\n", points / tries);

        fclose(memoryMatch_score);
    }

    
    return 0;
}
