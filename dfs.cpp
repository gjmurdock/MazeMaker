// STORE OUTPUT as vector<char> (i*width + j)
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<time.h>
#include<vector>

#define MAZESIZE 10

using namespace std;


void recurse(int**,int**,int,int);
void printmaze(int**);
void printadjarr(int**);
void printreal(int**,bool);
vector<char> makevec(int**); 


int main(int argc, char *argv[])
{
	bool outline;
	if (argv[1][0] == '1') outline = true;
	else if (argv[1][0] == '0') outline = false;
	else cout << "Need to be 0 or 1\n";

	bool print = true;
	if(print) cout << "Start\n";
 
    int* mptr[MAZESIZE];

	if(print) cout << "declare mptr\n";
	int i,j;
	for (i = 0; i < MAZESIZE; i++){
        mptr[i] = new int [MAZESIZE]; 
		for (j = 0; j < MAZESIZE; j++){
			mptr[i][j] = 0;
		}
	}

	cout << "Initialiazed mptr\n";
    int* aptr[MAZESIZE*MAZESIZE];
	cout << "declare aptr\n";
	for (i = 0; i < MAZESIZE*MAZESIZE; i++){
        aptr[i] = new int [MAZESIZE*MAZESIZE]; 
		for (j = 0; j < MAZESIZE*MAZESIZE; j++){
			//cout << "i: " << i << " j: " << j << " t:"<< ((MAZESIZE*MAZESIZE)*i)+j << "\n";
			aptr[i][j] = 0;
		}
	}
	if (print) cout << "got this far\n";
	// init random
	srand(time(NULL));

	//print before
	cout << "Maze: should be all zeros\n";
	printmaze(mptr);
	cout << "Adjacency Array: Should be all zeros\n";
	printadjarr(aptr);
	cout << "Real Maze: should be all x's\n";
	printreal(aptr,outline);

	// while, pick random
	recurse(mptr,aptr,0,0);

//*
	// print after
	cout << "Maze: should be all ones\n";
	printmaze(mptr);
	cout << "Adjacency Array: Should be a mix of zeros and ones\n";
	printadjarr(aptr);
	cout << "Real Maze: should be a mix of \" \" and x's\n";
	printreal(aptr,outline);
// */
	
	// return vector<char> (i*MAZESIZE + j)
	vector<char> returnvec = makevec(aptr);
	for (i = 0; i < returnvec.size(); i++)
	{
		printf("%c", returnvec[i]);
	}

	// delete everything
	for (i = 0; i < MAZESIZE; i++){
		delete mptr[i];
	}
	//delete mptr;

	for (i = 0; i < MAZESIZE*MAZESIZE; i++){
		delete aptr[i];
	}
	//delete aptr;

	return 0;
}

// dfs chooses only one route to follow until it cannot anymore
void recurse(int** mpos, int** apos, int i, int j)
{
	mpos[i][j] = 1;
	apos[(MAZESIZE*i)+j][(MAZESIZE*i)+j] = 1;

	//printreal(apos,true);
	//getchar();

	int choice;
	// choose random sizde, mark it as a part of the maze, recurse into it
	// if there are no more sides return 
	bool up, down, left, right;
	up = down = left = right = false;
	//up = (i-1 >= 0) true : false;
	if(i-1 >= 0){
		if(mpos[i-1][j] != 1){
			up = true;
		}
	}
	
	
	//down = (i+1 < MAZESIZE-1) true : false;
	if(i+1 < MAZESIZE){
		if(mpos[i+1][j] != 1){
			down = true;
		}
	}

	//left = (j-1 >= 0) true : false;
	if(j-1 >= 0){
		if(mpos[i][j-1] != 1){
			left = true;
		}
	}

	//right = (j+1 < MAZESIZE-1) true : false;
	if(j+1 < MAZESIZE){
		if(mpos[i][j+1] != 1){
			right = true;
		}
	}

/*
	while((i-1 >= 0 || *mpos[i-1][j] != 1) &&
	(i+1 < MAZESIZE-1 || *mpos[i+1][j] != 1) &&
	(j-1 >= 0 || *mpos[i][j-1] != 1) &&
	(j+1 < MAZESIZE-1 || *mpos[i][j+1] != 1)) {
*/
	while(up || down || left || right) {
		choice = rand() % 4;
		switch (choice) {
			case 0:
				//if(i-1 >= 0 && *mpos[i-1][j] != 1){ 
				if(i-1 >= 0){
					if(mpos[i-1][j] != 1){
						mpos[i-1][j] = 1;
						apos[(MAZESIZE*i)+j][(MAZESIZE*(i-1))+j] = 1;
						apos[(MAZESIZE*(i-1))+j][(MAZESIZE*i)+j] = 1;
						recurse(mpos, apos, i-1, j);
					} else {
						up = false;
					}
				} else {
					up = false;
				}
				break;
			case 1:
				//if(i+1 < MAZESIZE-1 && *mpos[i+1][j] != 1){ 
				if(i+1 < MAZESIZE){
					if(mpos[i+1][j] != 1){
						mpos[i+1][j] = 1;
						apos[(MAZESIZE*i)+j][(MAZESIZE*(i+1))+j] = 1;
						apos[(MAZESIZE*(i+1))+j][(MAZESIZE*i)+j] = 1;
						recurse(mpos, apos, i+1, j);
					} else {
						down = false;
					}
				} else {
					down = false;
				}
				break;
			case 2:
				//if(j-1 >= 0 && *mpos[i][j-1] != 1){ 
				if(j-1 >= 0){
					if(mpos[i][j-1] != 1){
						mpos[i][j-1] = 1;
						apos[(MAZESIZE*i)+j][(MAZESIZE*i)+(j-1)] = 1;
						apos[(MAZESIZE*i)+(j-1)][(MAZESIZE*i)+j] = 1;
						recurse(mpos, apos, i, j-1);
					} else {
						left = false;
					}
				} else {
					left = false;
				}
				break;
			case 3:
				//if(j+1 < MAZESIZE-1 && *mpos[i][j+1] != 1){ 
				if(j+1 < MAZESIZE){
					if(mpos[i][j+1] != 1){
						mpos[i][j+1] = 1;
						apos[(MAZESIZE*i)+j][(MAZESIZE*i)+(j+1)] = 1;
						apos[(MAZESIZE*i)+(j+1)][(MAZESIZE*i)+j] = 1;
						recurse(mpos, apos, i, j+1);
					} else {
						right = false;
					}
				} else {
					right = false;
				}
				break;
			default:
				cout << "You broke something\n";
		}
	}
}

void printmaze(int** mptr)
{
	int i,j;
	for (i = 0; i < MAZESIZE; i++){
		for (j = 0; j < MAZESIZE; j++){
			cout << mptr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void printadjarr(int** aptr)
{
	int i,j;
	for (i = 0; i < MAZESIZE*MAZESIZE; i++){
		for (j = 0; j < MAZESIZE*MAZESIZE; j++){
			cout << aptr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void printreal(int** aptr, bool outline)
{
	int i,j;
	for (i = 0; i < MAZESIZE; i++){
		if (outline){
			for (j = 0; j < MAZESIZE; j++){
				cout << "-----";
			}
			cout << endl;
		}

		for (j = 0; j < MAZESIZE; j++){
			if (outline) cout << "|";
			// top row
			if (i - 1 >= 0){
				if ( aptr[(MAZESIZE*i)+j][(MAZESIZE*(i-1))+j] == 1){
					cout << "x x";
				} else {
					cout << "xxx";
				}
			} else {
				cout << "xxx";
			}
			if(outline) cout << "|";
		}
		cout << endl;

		for (j = 0; j < MAZESIZE; j++) {
			if (outline) cout << "|";
			// left
			if (j - 1 >= 0){
				if ( aptr[(MAZESIZE*i)+j][(MAZESIZE*i)+(j-1)] == 1){
					cout << " ";
				} else {
					cout << "x";
				}
			} else {
				cout << "x";
			}
			// middle ?
			if ( aptr[(MAZESIZE*i)+j][(MAZESIZE*i)+j] == 1){
				cout << " ";
			} else {
				cout << "x";
			} 
			// right
			if (j + 1 < MAZESIZE){
				if ( aptr[(MAZESIZE*i)+j][(MAZESIZE*i)+(j+1)] == 1){
					cout << " ";
				} else {
					cout << "x";
				}
			} else {
				cout << "x";
			}
			if(outline) cout << "|";
		}
		cout << endl;

		for (j = 0; j < MAZESIZE; j++) {
			if(outline) cout << "|";
			// bottom row
			if (i + 1 < MAZESIZE){
				if ( aptr[(MAZESIZE*i)+j][(MAZESIZE*(i+1))+j] == 1){
					cout << "x x";
				} else {
					cout << "xxx";
				}
			} else {
				cout << "xxx";
			}	
			if(outline) cout << "|";
		}
		cout << endl;

		if (outline) {
			for (j = 0; j < MAZESIZE; j++){
				cout << "-----";
			}
			cout << endl;
		}
	}
	cout << endl;
}

vector<char> makevec(int** apos)
{
	vector<char> returnvec;
	int i, j;

	// x's along the top of the maze
	for (j = 0; j < (MAZESIZE*2)+1; j++)
	{
		returnvec.push_back('x');
	}

	// push_back a newline
	returnvec.push_back('\n');

	// only consult apos for x's on the right and bottom
	// sides will be filled with if statements
	for(i = 0; i < MAZESIZE; i++)
	{
		// this checks right
		for(j = 0; j < MAZESIZE; j++)
		{
			// we're at the left side of the maze
			if (j == 0)
			{
				returnvec.push_back('x');
			}

			// checks if tile has been initialized, which it should
			if (apos[(MAZESIZE*i)+j][(MAZESIZE*i)+j] == 1)
			{
				returnvec.push_back(' ');
			}
			// this shouldn't happend, but just in case it does
			else
			{
				// note: might consider changing this to make arrays
				// that haven't been fully initialized more obvious
				returnvec.push_back('x');
			}

			// we're at the right side of the maze
			if(j+1 == MAZESIZE)
			{
				returnvec.push_back('x');
			}
			else if (apos[(MAZESIZE*i)+j][(MAZESIZE*i)+(j+1)] == 1)
			{
				returnvec.push_back(' ');
			}
			else
			{
				returnvec.push_back('x');
			}
		}

		returnvec.push_back('\n');
		// bottom left corner will always be x
		returnvec.push_back('x');

		// this checks bottom
		for(j = 0; j < MAZESIZE; j++)
		{
			if(i+1 == MAZESIZE)
			{
				returnvec.push_back('x');
			}
			else if (apos[(MAZESIZE*i)+j][(MAZESIZE*(i+1))+j] == 1)
			{
				returnvec.push_back(' ');
			}
			else
			{
				returnvec.push_back('x');
			}

			// bottom right corner will always be x
			returnvec.push_back('x');
		}

		returnvec.push_back('\n');
		
	}

	return returnvec;
}
