#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*
  -------|
  |      O
  |     /|\
  |     / \
  |
-----
*/

void displayGame(int attempts) {
    switch (attempts) {
        case 0:
            printf(" \n");
            printf("  -------| \n");
            printf("  | \n");
            printf("  | \n");
            printf("  | \n");
            printf("----- \n");
            break;
        case 1:
            printf(" \n");
            printf("  -------| \n");
            printf("  |      O \n");
            printf("  | \n");
            printf("  | \n");
            printf("----- \n");
            break;
        case 2:
            printf(" \n");
            printf("  -------| \n");
            printf("  |      O \n");
            printf("  |      | \n");
            printf("  | \n");
            printf("----- \n");
            break;
        case 3:
            printf(" \n");
            printf("  -------| \n");
            printf("  |      O \n");
            printf("  |     /| \n");
            printf("  | \n");
            printf("----- \n");
            break;
        case 4:
            printf(" \n");
            printf("  -------| \n");
            printf("  |      O \n");
            printf("  |     /|\\ \n");
            printf("  | \n");
            printf("----- \n");
            break;
        case 5:
            printf(" \n");
            printf("  -------| \n");
            printf("  |      O \n");
            printf("  |     /|\\ \n");
            printf("  |     / \n");
            printf("-----\n");
            break;
        case 6:
            printf(" \n");
            printf("  -------| \n");
            printf("  |      O \n");
            printf("  |     /|\\ \n");
            printf("  |     / \\ \n");
            printf("-----\n");
            break;
    }
}

void displayWord(char word[], int wordLength) {
    printf(" \n");
    for (int i = 0; i < wordLength; i++) {
        if (word[i] == '_') {
            printf("_ ");
        } else if (word[i] == ' ') {
            printf("  "); 
        } else {
            printf("%c ", word[i]);
        }
    }
    printf(" \n");
}


const char* pickWord() {
    const char* options[] = {"argentina", "bahamas", "barbados", "belize", "bolivia", 
    "brazil", "canada", "chile", "colombia", "costa rica", "cuba", "dominica", 
    "dominican republic", "ecuador", "el salvador", "grenada", "guatemala", 
    "guyana", "haiti", "honduras", "jamaica", "mexico", "nicaragua", 
    "panama", "paraguay", "peru", "suriname", "trinidad and tobago", 
    "united states", "uruguay", "venezuela", "belize", "brazil", 
    "canada", "chile", "colombia", "costa rica", "dominica", "dominican republic", 
    "ecuador", "el salvador", "guyana", "haiti", "honduras", "jamaica", "mexico", 
    "nicaragua", "panama", "paraguay", "peru", "united states", 
    "uruguay", "venezuela", "bolivia"};
    int wordCount = sizeof(options) / sizeof(options[0]);

    int index = rand() % wordCount;
    return options[index];
}

int uniqueLetters(const char *word) {
    int uniqueCount = 0;
    char unique[100];

    for (int i = 0; i < strlen(word); i++) {
        if (!isalpha(word[i])) {
            continue;
        }

        int isUnique = 1;
        for (int j = 0; j < uniqueCount; j++) {
            if (unique[j] == word[i]) {
                isUnique = 0;
                break;
            }
        }

        if (isUnique) {
            unique[uniqueCount] = word[i];
            uniqueCount++;
        }
    }
    return uniqueCount;
}

void hangmanGame() {
    const char* gameWord = pickWord();
    int wordLength = strlen(gameWord);
    char word[wordLength + 1];
    int attempts = 0;
    int correctGuesses = 0;
    char guessedLetters[26] = {}; 
    int count = 0;
    int unique = uniqueLetters(gameWord);
    FILE *hangman_score = fopen("hangman_score.txt", "w");

    int letters = 0;
    for (int i = 0; i < wordLength; i++) {
        if (gameWord[i] != ' ') {
            letters++;
        }
        if (gameWord[i] == ' ') {
            word[i] = ' ';
        } else {
            word[i] = '_';
        }
    }
    
    while (attempts < 6) {
        printf(" \n");
        displayGame(attempts);
        displayWord(word, wordLength);
        printf(" \n");

       //player input
        char guess;
        printf("Enter a letter: ");
        int result = scanf(" %c", &guess);

        //exit the loop if eof is detected
        if (result == EOF) {
            printf("\nGame terminated by user.\n");
            break;
        }
        guess = tolower(guess);

        //check if the non-letter is guessed
        if (!isalpha(guess)) {
            printf(" \n");
            printf("Invalid input. Please enter a letter.\n");
            continue;
        }

        //exit the loop if eof is detected
        if (result == EOF) {
            printf("\nGame terminated by user.\n");
            break;
        }

        //check if the letter has already been guessed
        if (strchr(guessedLetters, guess) != NULL) {
            printf(" \n");
            printf("You already guessed '%c'. Try a different letter.\n", guess);
            continue;
        }
        //add the guessed letter to the guessed letters array
        guessedLetters[strlen(guessedLetters)] = guess;

        count++; //count the guesses without the repeats/incorrect inputs

        int correct = 0;
        for (int i = 0; i < wordLength; i++) {
            if (tolower(gameWord[i]) == guess && word[i] == '_') {
                word[i] = gameWord[i];
                correctGuesses++;
                correct = 1;
            }
        }

        if (correct == 0) {
            attempts++;
        }

        //check if the player has won
        if (correctGuesses == letters) {
            double score = (double)count/(unique + 6);
            displayGame(attempts);
            displayWord(word, wordLength);
            printf(" \n");
            printf("You won in %d guesses!\n", count);
            fprintf(hangman_score, "%.2f\n", score);
            break;
        }

        //check if the player has lost
        if (attempts == 6) {
            displayGame(attempts);
            printf(" \n");
            printf("You lost! The word was: %s\n", gameWord);
            fprintf(hangman_score, "0.00");
            break;
        }
    }
    fclose(hangman_score);
}

int main() {
    srand(time(0));  //intialize rng
    hangmanGame();
    return 0;
}
