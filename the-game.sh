#!/bin/bash

help() {
    echo "Help: This script runs different games."
    echo "Usage: ./baddie-or-not --[help/test]"

}

test() {
    #run games
    ./hangman
    ./wordle
    ./maze
    ./match

    #game scores
    hangman_score=$(cat hangman_score.txt)
    wordle_score=$(cat wordle_score.txt)
    maze_score=$(cat maze_score.txt)
    match_score=$(cat match_score.txt)

    #average score
    score=$(((hangman_score + wordle_score + maze_score + match_score)/4)*100)

    if [[ $score -ge 0 && $score -lt 20 ]]; then
        echo "Cruella"
    elif [[ $score -ge 20 && $score -lt 40 ]]; then
        echo "Scar"
    elif [[ $score -ge 40 && $score -lt 60 ]]; then
        echo "Jafar"
    elif [[ $score -ge 60 && $score -lt 80 ]]; then
        echo "Ursula"
    else
        echo "Gaston"
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
