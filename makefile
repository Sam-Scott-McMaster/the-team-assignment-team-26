<<<<<<< HEAD
memoryMatch: memoryMatch.c 
	gcc -o memoryMatch memoryMatch.c 

memoryTest: memoryMatch
	gcc -o memoryTest --coverage memoryMatch.c 

clean:
	rm -f *.o *.gcda *.gcno *.gcov memoryTest

=======
all: hangman wordle maze match

hangman: hangman-beta.c
	gcc -o hangman hangman-beta.c

wordle: wordle.c
	gcc -o wordle wordle.c

maze: maze.c
	gcc -o maze maze.c

match: memoryMatch.c
	gcc -o match memoryMatch.c
>>>>>>> 8c186b04f4669e7151117f0bf16ddf429e6d870f
