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
    make
    
    echo "Welcome to Baddie or Not. The games will begin now: Good luck!"
    echo ""
    echo ""
    
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
    
    echo "Welcome to Maze!"
    ./maze
    ./match

    hangman_score=$(cat hangman_score.txt)
    wordle_score=$(cat wordle_score.txt)
    maze_score=$(cat maze_score.txt)
    match_score=$(cat memoryMatch_score.txt)

    score=$(echo "scale=2; ($hangman_score + $wordle_score + $maze_score + $match_score) / 4 * 100" | bc)

    if (( $(echo "$score < 20" | bc -l) )); then
        echo ""
        cat scar.txt
    elif (( $(echo "$score >= 20 && $score < 40" | bc -l) )); then
        echo ""
        cat jafar.txt
    elif (( $(echo "$score >= 40 && $score < 60" | bc -l) )); then
        echo ""
        cat gaston.txt
    elif (( $(echo "$score >= 60 && $score < 80" | bc -l) )); then
        echo ""
        cat ursula.txt
    else
        echo ""
        cat cruella.txt
    fi
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
