#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define cols 10
#define rows 10

char game_board[rows][cols] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

void currentPosition(int playerRow, int playerCol) {
    system("clear"); // Refreshes the terminal screen
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == playerRow && j == playerCol)
                printf("S "); // Display the player position as 'S'
            else
                printf("%c ", game_board[i][j]); // Display the game board
        }
        printf("\n");
    }
}

void makeGlitch(int *playerRow, int *playerCol, int destinationRow, int destinationCol, int *glitchCount) {
    if (*glitchCount >= 5) return;  // Stop glitches after 5 times

    printf("\nOops...Something went wrong :(\n");
    sleep(3);  // Simulate delay

    int currentDistance = abs(*playerRow - 2) + abs(*playerCol - 2);
    int newRow, newCol;

    do {
        newRow = rand() % rows;
        newCol = rand() % cols;
    } while ((game_board[newRow][newCol] == '#' || (abs(newRow - destinationRow) + abs(newCol - destinationCol)) <= currentDistance));

    *playerRow = newRow;
    *playerCol = newCol;
    (*glitchCount)++;

    printf("Please be patient while your position gets updated...\n");
    sleep(2);  // Simulate delay
}

int main() {
    int playerRow = 1, playerCol = 1; 
    int destinationRow = 8, destinationCol = 8; 
    char input[10];  
    int moveCount = 0;  
    int glitchCount = 0; 

    srand(time(NULL)); 

    FILE *scoreFile = fopen("maze_score.txt", "w"); 
    if (scoreFile == NULL) {
        fprintf(stderr, "Error: Could not open maze_score.txt for writing.\n");
        return EXIT_FAILURE;
    }

    while (true) {
        currentPosition(playerRow, playerCol);  

        if (playerRow == destinationRow && playerCol == destinationCol) {
            printf("You reached the goal in %d moves.\n", moveCount);
            printf("Impressive dedication! You endured all the glitches.\n");
            fprintf(scoreFile, "%.2f\n", (float)glitchCount / 5);
            fclose(scoreFile);
            break;  
        }

        if (glitchCount < 5 && rand() % 3 == 0) {   
            makeGlitch(&playerRow, &playerCol, destinationRow, destinationCol, &glitchCount);
        }

        printf("Move with W (up), A (left), S (down), D (right), or type 'quit' to exit: ");
        fgets(input, sizeof(input), stdin);  
        input[strcspn(input, "\n")] = 0;  

        if (strcmp(input, "quit") == 0) {
            printf("Game Over! You quit after %d moves and %d glitches.\n", moveCount, glitchCount);

            fprintf(scoreFile, "%.2f\n", (float)glitchCount / 5);

            fclose(scoreFile);
            break;
        }

        int newRow = playerRow, newCol = playerCol;
        if (strcmp(input, "w") == 0 || strcmp(input, "W") == 0) newRow--; // Move up
        else if (strcmp(input, "a") == 0 || strcmp(input, "A") == 0) newCol--; // Move left
        else if (strcmp(input, "s") == 0 || strcmp(input, "S") == 0) newRow++; // Move down
        else if (strcmp(input, "d") == 0 || strcmp(input, "D") == 0) newCol++; // Move right

        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && game_board[newRow][newCol] != '#') {
            playerRow = newRow; 
            playerCol = newCol;
            moveCount++; 
        } else {
            printf("Invalid move! Try again.\n");
            sleep(3); 
        }
    }

    return EXIT_SUCCESS;  
}
