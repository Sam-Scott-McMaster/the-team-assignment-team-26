memoryMatch: memoryMatch.c 
	gcc -o memoryMatch memoryMatch.c 

testMemoryMatch: test_memoryMatch.c 
	gcc -o testMemoryMatch test_memoryMatch.c 

memoryTest: test_memoryMatch.c
	gcc -o memoryTest --coverage test_memoryMatch.c 

clean:
	rm -f *.o *.gcda *.gcno *.gcov memoryTest

