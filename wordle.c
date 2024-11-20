#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void help() {
    printf("How to Play Wordle:\n\n");
    printf("1. Objective: Guess the secret 5-letter word within six tries.\n\n");
    printf("2. Guess a Word: Type a 5-letter word and press 'Enter' to submit your guess.\n\n");
    printf("3. Feedback on Guesses:\n");
    printf("   - \033[32mGreen\033[0m\n: A letter is in the correct position.\n");
    printf("   - \033[33mYellow\033[0m: A letter is in the word but not in the correct position.\n");
    printf("   - \033[31mRed\033[0m: A letter is not in the word at all.\n\n");
    printf("4. Continue Guessing: Use the feedback from each guess to narrow down the possibilities.\n");
    printf("   Keep guessing until you find the word or run out of tries.\n\n");
    printf("5. Win or Lose: If you guess the word correctly, you win! If you run out of attempts, the correct word is revealed.\n\n");
}

bool validateGuess(char guess[]) {
    char* correct_answer = randomizedWords();
    for (int i = 0; i < strlen(guess); i++) {
        if (guess[i] == correct_answer[i]) {
            printf("\033[32m%s  \033[0m", guess[i]);
        } else if (strchr(correct_answer, guess[i]) != NULL) {
            printf("\033[33m%s  \033[0m", guess[i]);
        } else {
            printf("\033[31m%s  \033[0m", guess[i]);
        }
    }

    if (strcmp(correct_answer, guess) == 0) {
        return true;
    }
    return false;
}

char* randomizedWords() {
    char* answer_bank[] = {"apple", "stone", "green", "smile", "blaze", "crash", "flick", "beach", "grape", 
    "sweep", "flame", "stone", "grasp", "plume", "drain", "sword", "blunt", "flock", "sharp", "swoop", 
    "lunar", "trick", "vivid", "cloud", "flint", "haste", "charm", "pouch", "spoon", "dance", "flock", 
    "vivid", "haste", "brick", "gleam", "swirl", "skirt", "plaza", "stoic", "march", "plume", "blaze", 
    "swoop", "crisp", "fluff", "jumpy", "waste", "throb"};

    int num_words = sizeof(answer_bank) / sizeof(answer_bank[0]);

    srand(time(NULL));

    int random_index = rand() % num_words;

    return answer_bank[random_index];
}

int main(int argc, char *argv[]) {
    char guess;
    bool result;
    int attempts = 0;

    if (argv[0] == "--help") {
        help();
        return 0;
    }

    while (attempts <= 6) {
        printf("Enter your guess: ");
        scanf("%s", guess);
        result = validateGuess(guess);

        if (result == true) {
            printf("\n Congrats! You guessed the correct word.");
            printf("Your score is %d out of 5.", attempts);
            return (4 / 5);
        } else {
            attempts += 1;
        }     
    }
    printf("\n That is incorrect and you have used your last attempt.");
    printf("Your score is 0 out of 5.");
    return (0 / 5);
}
