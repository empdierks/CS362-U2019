
all: testme
	./testme

testme: testme.c
	gcc -std=c99 -lm -fpic -coverage testme.c -o testme

clean:
	rm -rf testme
