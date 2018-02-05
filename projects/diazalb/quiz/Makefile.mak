CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	
all: 

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out 
