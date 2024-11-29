#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char* randomizeAnswer() {
    return "apple";
}

void readInputs(char guess[]) {
    while (1) {
        printf("Enter your guess: ");
        if (fgets(guess, 7, stdin) == NULL) {  // Read up to 6 chars + newline
            printf("\nInput terminated. Exiting the game.\n");
	    fprintf(stderr, "\nInput terminated. Exiting the game.\n");
	    exit(1);
        }

        if (guess[strlen(guess) - 1] == '\n') {
            guess[strlen(guess) - 1] = '\0';
        } else {
            while (getchar() != '\n');
        }

        if (strlen(guess) != 5) {
            printf("Please enter exactly 5 characters.\n");
            continue;
        }

        bool valid = true;
        for (int i = 0; i < 5; i++) {
            if (!isalpha(guess[i])) {
                valid = false;
                break;
            }
        }

        if (!valid) {
            printf("Invalid input. Only alphabetic characters are allowed.\n");
        } else {
            break;
        }
    }
}


void playWordle() {
    char *correct_answer = randomizeAnswer();
    char guess[6];
    int attempts = 0;
    char guesses[6][6];

    FILE *wordle_score = fopen("wordle_score.txt", "w");

    while (attempts < 6) {
        readInputs(guess);

        for (int i = 0; i < 5; i++) {
            guesses[attempts][i] = guess[i];
        }
        for (int i = attempts; i >= 0; i--) {
            for (int j = 0; j < 5; j++) {
                if (guesses[i][j] == correct_answer[j]) {
                    printf("\033[32m%c  \033[0m", guesses[i][j]);
                } else if (strchr(correct_answer, guesses[i][j]) != NULL) {
                    printf("\033[33m%c  \033[0m", guesses[i][j]);
                } else {
                    printf("\033[31m%c  \033[0m", guesses[i][j]);
                }
            }
            printf("\n");
        }
        if (strcmp(correct_answer, guess) == 0) {
            printf("Congrats! You guessed the correct word.\n");
            printf("Your score is %d out of 6.\n", 6 - attempts);
            fprintf(wordle_score, "%.2d\n", (6 - attempts) / 6);
            fclose(wordle_score);
            return;
        }
        attempts++;
    }
    printf("Sorry, you've used all attempts. The correct word was: %s\n", correct_answer);
    fprintf(wordle_score, "0.00\n");
    fclose(wordle_score);
    
}

int main(int argc, char *argv[]) {
    playWordle();
    return 0;
}

