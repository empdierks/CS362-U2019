/***************************
 * CS362 - Summer 2019
 * Random Testing Quiz
 * Emily Dierks
 * *************************/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include<time.h>

char inputChar(){

	//random character between 32 ' ' to 125 '}'
	// random()%(125-32+1)+32
	char randomChar = (rand()%94)+32;

	return randomChar;
}

void inputString(char* randomString){

	//need 101 'e' to 116 't'
	for (int i=0; i <5; i++){
		//(rand()%116-101+1)+101
		randomString[i]=(rand()%16)+101;
	}

	//add \0 at end of every string
	randomString[5]= '\0';

}

void testme(){

	int tcCount = 0;
	char s[6];
	char c;
	int state = 0;
	
	while(1){

		tcCount++;
		c=inputChar();
		inputString(s);
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if(c == '[' && state == 0) state = 1; //ASCII 91
		if(c == '(' && state == 1) state = 2; // ASCII 40
		if(c == '{' && state == 2) state = 3; //ASCII 123
		if(c == ' ' && state == 3) state = 4; //ASCII 32
		if(c == 'a' && state == 4) state = 5; //ASCII 97
		if(c == 'x' && state == 5) state = 6; //ASCII 120
		if(c == '}' && state == 6) state = 7; //ASCII 125
		if(c == ')' && state == 7) state = 8; //ASCII 41
		if(c == ']' && state == 8) state = 9; //ASCII 93

		if(s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9){
			printf("error ");
			exit(200);
		}
	}
}

int main(int argc, char *argv[]){
	srand(time(NULL));
	testme();
	return 0;
} 
	
	
