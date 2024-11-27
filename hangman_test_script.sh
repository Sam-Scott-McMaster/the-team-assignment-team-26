#!/bin/bash

#clean previous build and coverage files
rm -f *.gcda *.gcno *.gcov hangman hangman_gcov_output.txt hangman_score.txt

#compile with coverage
gcc -o hangman hangman-test.c -fprofile-arcs -ftest-coverage -Wall

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

#case 1: EOF
echo -e "EOF Test Case:\n" >> hangman_gcov_output.txt
(echo -n "" | ./hangman) >> hangman_gcov_output.txt

#case 2: correct guesses
echo -e "\nCorrect Guesses Test Case:\n" >> hangman_gcov_output.txt
(echo -e "c\na\nn\nd\nEOF" | ./hangman) >> hangman_gcov_output.txt

#case 3: incorrect guesses
echo -e "\nIncorrect Guesses Test Case:\n" >> hangman_gcov_output.txt
(echo -e "z\ny\nx\nEOF" | ./hangman) >> hangman_gcov_output.txt

#case 4: correct and incorrect guesses
echo -e "\nMixed Guesses Test Case:\n" >> hangman_gcov_output.txt
(echo -e "c\nz\na\nx\nEOF" | ./hangman) >> hangman_gcov_output.txt

#generate the gcov report
if [ -f "hangman-hangman-test.gcno" ]; then
    mv hangman-hangman-test.gcno hangman-test.gcno
fi

if [ -f "hangman-hangman-test.gcda" ]; then
    mv hangman-hangman-test.gcda hangman-test.gcda
fi

gcov -b hangman-test.c >> hangman_gcov_output.txt
cat hangman_gcov_output.txt