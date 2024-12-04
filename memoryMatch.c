/********************************* 
 * Memory Match game 
 * 
 * This is a memory match game displayed as a 4x4 grid in the terminal and fashion
 * items are randomly shuffled and hidden in the grid.
 * The player uses rows anc column indeces to match identical fashion items OR
 * items that are in the same Disney fashion trait category. There are only 2 items that are in the same category.
 * For example, player can match Crown and Crown or Crown and Scepter as they are both in the same 
 * Disney fashion trait category: Royalty.
 * Players get 10 maximum tries to match all items in the grid.
 * If player matches a pair, they get 1.00 point. If they don't, they lose 0.25 points.
 * Their final score is calculated by dividing their total points by the number of tries they took
 * to complete the game.
 * Player can quit at any time by typing -1 -1 when asked for the row and column indeces of an item.
 * If player quits, their score will automatically be 0.
 * 
 *
 * 
 * Navya Ahuja, McMaster University, 2024 
***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//Define constants of size of board length and max tries
#define SIZE 4
#define MAX_TRIES 10

// Define the struct
typedef struct {
    const char *object;
    const char *trait;
} objectTrait;

// Create an instance array of objectTrait
//2 Objects can match if they are in the same trait, even if they are not identical
objectTrait objectTraits[] = {
    {"Crown", "Royalty"}, {"Scepter", "Royalty"},
    {"Fur Coat", "Elegance"}, {"Necklace", "Elegance"},
    {"Tentacles", "Power"}, {"Staff", "Power"},
    {"Mirror", "Glamour"}, {"Heels", "Glamour"},
    {"Fire", "Mischief"}, {"Skull", "Mischief"},
    {"Snake", "Trickery"}, {"Lamp", "Trickery"},
    {"Claw", "Ambition"}, {"Throne", "Ambition"},
    {"Apple", "Deception"}, {"Dagger", "Deception"},
    {"Pearls", "Wisdom"}, {"Cape", "Wisdom"},
    {"Ring", "Stealth"}, {"Mask", "Stealth"},
    {"Book", "Knowledge"}, {"Lantern", "Knowledge"},
    {"Sword", "Strength"}, {"Shield", "Strength"},
    {"Potion", "Mystery"}, {"Web", "Mystery"},
    {"Crystal", "Magic"}, {"Orb", "Magic"},
    {"Scroll", "Secrets"}, {"Helmet", "Secrets"},
    {"Feather", "Flight"}, {"Bow", "Flight"}
};

//Function to create the board
/*Parameters:
 *  - board: 2D array of strings representing  objects on the board.
 *  - traitsBoard: A 2D array of strings representing the traits corresponding to each object.*/
//Returns: void
void makeBoard(char *board[SIZE][SIZE], char *traitsBoard[SIZE][SIZE]) {
    //Variable to hold indeces of all possible locations
    int locations[SIZE * SIZE];
    //Run for loop to hold the location indeces in the array
    for (int i = 0; i < SIZE * SIZE; i++) {
        locations[i] = i;
    } 

    //Shuffle locations array numbers, creates random board positions
    srand(time(NULL)); //Seed to generate random nunber
    for (int i = 0; i < SIZE * SIZE; i++) {
        int j = rand() % (SIZE * SIZE); //Initializes random index and make sure it is in range of the board size
        //Swap values at locations[i] and locations[j]
        int temp = locations[i];
        locations[i] = locations[j];
        locations[j] = temp;
    }

    //Pair objects and traits
    for (int i = 0; i < SIZE * SIZE / 2; i++) { //Loop iterates over half the total number of locations since each object is paired
        int firstLoc = locations[2 * i];
        int secondLoc = locations[2 * i + 1];

        // Calculate the row and column for each location
        int r1 = firstLoc / SIZE, c1 = firstLoc % SIZE;
        int r2 = secondLoc / SIZE, c2 = secondLoc % SIZE;

        //Place objects on board and traits in the calculated location
        board[r1][c1] = (char *)objectTraits[i].object;
        traitsBoard[r1][c1] = (char *)objectTraits[i].trait;

        //Place duplicate of object at another location and same trait in another calculated location
        board[r2][c2] = (char *)objectTraits[i].object;
        traitsBoard[r2][c2] = (char *)objectTraits[i].trait;
    }
}

//Function to display the board
/*Parameters:
 *  - board: 2D array of strings representing  objects on the board.
 *  - shown: A 2D array of strings representing th objcects that have been shown on the board.*/
//Returns: void
void showBoard(char *board[SIZE][SIZE], int shown[SIZE][SIZE]) {
    //Empty Space for top left corner to create proper board layout
    printf("   ");

    //Print column numbers at the top
    for (int i = 0; i < SIZE; i++) {
        printf("%2d        ", i); // Column header
    }
    printf("\n"); 

    //Iterate through each row and print 
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", i); // Row header at the left most corner
        for (int j = 0; j < SIZE; j++) { //Iterate through each column
            if (shown[i][j]) { //If object is revealed, print the object left aligned 10 spaces 
                printf("%-10s ", board[i][j] ? board[i][j] : "[??]"); //In case the position is null, print [??] 
            } else { //If cell is not revealed, don't show the card
                printf("[?]       ");
            }
        }
        printf("\n"); //New line for next row
    }
}

//Function to check if 2 traits match
/*Parameters:
 *  - trait1: pointer to string of first trait 
 *  - trait2: pointer to string of second trait*/
//Returns: int (1 if identical, 0 if not)
int isMatch(const char *trait1, const char *trait2) {
    return strcmp(trait1, trait2) == 0; //Condition to compare 2 strings  
}

//Function to play main game
//Parameters:None
//Returns: int (always 0 since game always runs successfully)
int main() {

    //Introduction
    printf("Welcome to Disney Villain Memory Match!\n\n");

    //Initialize boards and set to null or 0
    char *board[SIZE][SIZE] = {NULL};
    char *traitsBoard[SIZE][SIZE] = {NULL};
    int shown[SIZE][SIZE] = {0};

    //Initialize boards and set to null or 0
    FILE *memoryMatch_score = fopen("memoryMatch_score.txt", "w");

    //Create board with random objects and display the board
    makeBoard(board, traitsBoard);
    showBoard(board, shown);

    //Initialize variables 
    float points = 0.0; // Float to track points 
    int tries = 0; //Int to track number of tries
    int matches = 0; //Int to track number of object matches
    bool quit = false; //Boolean to track if user quit the game

    //Loop while the number of matches has not reached max limit (half of number of locations on board)
    while (matches < SIZE * SIZE / 2) {

        //If Number of tries exceeds/is equal to max tries, end game
        if (tries >= MAX_TRIES) {
            printf("\nYou've reached the maximum number of tries (%d). Game over!\n", MAX_TRIES);
            printf("Your final score: %.2f\n", points);
            fprintf(memoryMatch_score, "%.2f\n", points / tries); //Print score in .txt file
            fclose(memoryMatch_score); //Close file
            return 0; 
            
        }

        //Initialize variables for inputted rows and column pairs
        int r1, c1, r2, c2;

        //-1 -1 for exiting game
        printf("\nEnter '-1 -1' at any time to quit the game.\n");

        //Reiterate till valid input for first object
        while (1) {
            printf("Enter the coordinates of the first object(row col): ");
            if (scanf("%d %d", &r1, &c1) == 2) { //Check if number of parameters is 2
                if (r1 == -1 && c1 == -1) { //Break if -1 -1
                    quit = true;
                    break; //Break loop
                }
                if (r1 >= 0 && r1 < SIZE && c1 >= 0 && c1 < SIZE &&
                !shown[r1][c1]) { //Check if row and col values are in range
                    break; //Break loop
                }
            }
            if (quit == false ) { //If invalid input, print statement and reiterate through while loop
                printf("Invalid input. Try again.\n");
            }
            while (getchar() != '\n'); 
        }

        //Check if game quitted after first input
        if (quit == true) {
            printf("You chose to quit. Your score is 0.00\n"); //Score automatically 0
            fprintf(memoryMatch_score, "0.00\n"); //Print to file
            fclose(memoryMatch_score);
            return 0;
        }

        //Reiterate till valid input for second object
        while (1) {
            printf("Enter the coordinates of the second object(row col): "); 
            if (scanf("%d %d", &r2, &c2) == 2) { //Check if number of parameters is 2
                if (r2 == -1 && c2 == -1) { //Break if -1 -1
                    quit = true;
                    break; //Break loop
                }
                if (r2 >= 0 && r2 < SIZE && c2 >= 0 && c2 < SIZE &&
                !shown[r2][c2] && !(r1 == r2 && c1 == c2)) { //Check if row and col values are in range
                    break; //break loop
                }
            }
            if (quit == false ) { //If invalid input, print statement and reiterate through while loop
                printf("Invalid input. Try again.\n");
            }            
            while (getchar() != '\n'); 
        }

        //Check if game quitted after second input
        if (quit == true) {
            printf("You chose to quit. Your score is 0.00\n"); //Score automatically 0
            fprintf(memoryMatch_score, "0.00\n"); //Print to file
            fclose(memoryMatch_score);
            return 0;
        }

        //Shown indexes in array are set to 1 
        shown[r1][c1] = 1;
        shown[r2][c2] = 1;
        showBoard(board, shown); //Display board

        //Check if traits are a match by calling isMatch() 
        if (isMatch(traitsBoard[r1][c1], traitsBoard[r2][c2])) { 
            printf("Matched objects: %s and %s\n", board[r1][c1], board[r2][c2]); //Print matched objects
            printf("Trait: %s\n", traitsBoard[r1][c1]); //Print trait
            points += 1.0; //Increase points by 1
            matches++; //Increase matched items by 1
        } else { //If no match
            printf("No match. Try again.\n"); 

            //Shown indexes in array are set to 0
            shown[r1][c1] = 0; 
            shown[r2][c2] = 0;
            points -= 0.25; //Decrease points by 0.25
            if (points < 0.0) { //If points are negative, set them back to 0
                points = 0.0; 
            }  
        }

        tries++; //Increase number of tries by 1   

        //Print current status of player's game 
        printf("Current points: %.2f\n", points);
        printf("Efficiency: %.2f points/turn\n", points / tries);
        printf("Remaining tries: %d\n", MAX_TRIES - tries);

    }

    //After loop of game has ended, check if all items were matched within given number of tries
    if (matches == (SIZE * SIZE / 2) && tries <= MAX_TRIES) {
        //Give player final results of game
        printf("\nCongratulations! You matched all objects in %d tries.\n", tries); 
        printf("Your final points is %.2f.\n", points); 
    }
    
    //Print score efficiency, and then print it to file
    printf(" %.2f \n", points / tries);
    fprintf(memoryMatch_score, "%.2f\n", points / tries);
    fclose(memoryMatch_score); //Close file

    return 0; //Return 0 to know program executed gracefully
}
