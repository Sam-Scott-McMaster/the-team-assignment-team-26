#!/bin/bash

help() {
    echo "Baddie or Not (v1.0.0)"
    echo "Usage: ./baddie-or-not [OPTIONS]"
    echo ""
    echo "This app uses a series of questions to determine the user’s personality type in terms of what Disney villain character they are. It also invites the user to play games such as Hangman, Wordle, Maze, and Memory Match to improve the accuracy of the response they receive."
    echo ""
    echo "Mini-Games Included:"
    echo "1. Hangman: A classic game that tests your problem-solving skills and vocabulary."
    echo "2. Wordle: A terminal-based game that tracks the number of attempts you take to find the correct answer."
    echo "3. Maze: Navigate through a glitchy maze that challenges your patience by introducing unexpected obstacles. Will you persevere or give up?"
    echo "4. Memory Match: A fashion-themed memory game where you match fashion items to the character you associate with them most."
    echo ""
    echo "Options:"
    echo "  --help        Display this help message with instructions"
    echo "  --test        Start the personality test, which will play all the mini-games in sequence."
    echo ""
    echo "How to Play:"
    echo "1. In Hangman and Wordle, you'll be prompted to guess letters or words."
    echo "2. In the Maze game, use arrow keys or input directions to navigate."
    echo "3. In Memory Match, flip cards and match pairs to score points."
    echo "4. Your quiz answers, combined with your scores from the mini-games, help refine the personality analysis by assessing traits like problem-solving skills, patience, and memory."
    echo "5. You'll be matched with a fictional villain that aligns with your personality!"
    echo ""
    echo "Objective: Complete all the mini-games and find out what Disney villain you are based on your performance!"
}

test() {
    #run games
    make -s
    
    echo "Welcome to Baddie or Not. The games will begin now: Good luck!"
    echo ""

    sleep 5
    clear

    echo "Welcome to Wordle!"
    echo ""
    echo "How to Play Wordle:"
    echo "1. Objective: Guess the secret 5-letter word within six tries."
    echo "2. Guess a Word: Type a 5-letter word and press 'Enter' to submit your guess."
    echo "3. Feedback on Guesses:"
    echo "   - Green: The letter is in the correct position."
    echo "   - Yellow: The letter is in the word but not in the correct position."
    echo "   - Red: The letter is not in the word at all."
    echo "4. Continue Guessing: Use the feedback from each guess to narrow down the possibilities. Keep guessing until you find the word or run out of tries."
    echo "5. Win or Lose: If you guess the word correctly, you win! If you run out of attempts, the correct word is revealed."
    echo ""
    ./wordle

    sleep 2
    clear

    echo "Welcome to Hangman!"
    echo ""
    echo "How to Play Hangman:"
    echo "1. This is a classic hangman game where you guess letters to uncover the hidden word."
    echo "2. You have up to 6 incorrect attempts to guess the word."
    echo "3. You can type in more than one letter at a time to guess, but it is recommended to guess letters one at a time."
    echo "4. This game is meant to test the player on their problem-solving skills."
    echo "5. Your score is calculated based on the number of guesses made, proportional to the optimal number of guesses to win."
    echo ""
    ./hangman

    sleep 2
    clear

    echo "    Welcome to Maze!"
    echo ""
    echo "1. How to Play Maze:"
    echo "2. Test your problem-solving and strategic thinking skills in this exciting game."
    echo "3. Take as much time as you need to reach your destination."
    echo ""
    echo "4.  Use the keys W (up), A (left), S (down), and D (right) to navigate the maze."
    echo "5. Type 'quit' anytime to exit."
    echo ""
    echo "6.  Your score is based on the number of moves you make to reach the destination—the fewer, the better!"
    echo ""
    ./maze

    sleep 2
    clear

    echo "Welcome to Fashion Memory Game!"
    echo ""
    echo "How to Play Fashion Memory Game:"
    echo "1. Match pairs of items that are identical or similar in aesthetic to reveal the villain's trait."
    echo "2. Enter the row and column numbers of two cards to flip and check if they form a matching pair."
    echo "3. Feedback on Matches:"
    echo "   - Match: The pair is identical or aesthetically similar; it stays revealed, and you gain 1 point."
    echo "   - No Match: The cards are flipped back over, and you lose 0.25 points."
    echo "5. Match all pairs within 10 turns to uncover the villain's hidden trait!"
    echo "6. Your final score is calculated based on efficiency (points/turns). Aim to maximize your matches with the fewest tries."
    echo ""
    clear
    ./match

    hangman_score=$(awk '{printf "%.0f", $1 * 100}' hangman_score.txt)
    wordle_score=$(awk '{printf "%.0f", $1 * 100}' wordle_score.txt)
    maze_score=$(awk '{printf "%.0f", $1 * 100}' maze_score.txt)
    match_score=$(awk '{printf "%.0f", $1 * 100}' memoryMatch_score.txt)

    # Scale scores to a range of 0-100 and calculate the average
    score=$((($hangman_score + $wordle_score + $maze_score + $match_score)/4))

    # Determine the category based on the average score
    if ((score >= 0 && score < 20)); then
        clear
        cat scar.txt
    elif ((score >= 20 && score < 40)); then
        clear
        cat jafar.txt
    elif ((score >= 40 && score < 60)); then
        clear
        cat gaston.txt
    elif ((score >= 60 && score < 80)); then
        clear
        cat ursula.txt
    else
        clear
        cat cruella.txt
    fi

    make -s clean
}

#main logic
if [[ "$#" -eq 0 ]]; then
    echo "Usage: ./baddie-or-not --[help/test]"
    exit 1
fi

for arg in "$@"; do
    if [[ "$arg" == "--test" ]]; then
        test
        exit 0
    elif [[ "$arg" == "--help" ]]; then
        help
        exit 0
    else
        echo "Usage: ./baddie-or-not --[help/test]"
        exit 1
    fi
done
