all: hangman wordle maze match

hangman: hangman-beta.c
	gcc -o hangman hangman-beta.c
wordle: wordle.c
	gcc -o wordle wordle.c
maze: maze.c
	gcc -o maze maze.c
match: memoryMatch.c
	gcc -o match memoryMatch.c
