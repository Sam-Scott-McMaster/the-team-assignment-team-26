memoryMatch: memoryMatch.c 
	gcc -o memoryMatch memoryMatch.c 

memoryTest: memoryMatch
	gcc -o memoryTest --coverage memoryMatch.c 

clean:
	rm -f *.o *.gcda *.gcno *.gcov memoryTest

