#include<stdio.h>
#include<stdlib.h>
#define MAZESIZE 10

using namespace std;

int main()
{
	int maze[MAZESIZE][MAZESIZE];
	int i,j;
	for (i = 0; i < MAZESIZE; i++){
		for (j = 0; j < MAZESIZE; j++){
			maze[i][j] = 0;
		}
	}

	// while, pick random
	int * pos = maze[0][0];
	recurse(pos);
	return 0;
}

void recurse(int * pos)
{
	
}
