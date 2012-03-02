#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<time.h>
#include<iostream>

#define MAZESIZE 10

using namespace std;


// tile struct for use in vector
struct tile {
	bool inMaze;
	// open sides
	bool top, left, right, bottom;
	// initialized sides
	bool init_t, init_l, init_r, init_b;
	int pos;
} maze[MAZESIZE][MAZESIZE];

// functions
int checksides(tile*);
int choosetile(tile*);
bool inthemaze(vector<tile>,int);
void setemupnice(tile*,tile*);
void setemuphalf(tile*,tile*);
void printthatprim();
void printrevprim();

int main()
{
	int i,j; // iterators

	// initialize maze
	for(i = 0; i < MAZESIZE; i++){
		for (j = 0; j < MAZESIZE; j++) {
			maze[i][j].inMaze = false;
			maze[i][j].top = false;
			maze[i][j].left = false;
			maze[i][j].right = false;
			maze[i][j].bottom = false;
			maze[i][j].init_t = false;
			maze[i][j].init_l = false;
			maze[i][j].init_r = false;
			maze[i][j].init_b = false;
			maze[i][j].pos = (MAZESIZE*i)+j;
		}
	}

	printthatprim();

	//* Uncomment this when you're ready 

	// initialize edges of the maze to prevent illegal expansion
	// initialize top row
	for (j = 0; j < MAZESIZE; j++){
		maze[0][j].init_t = true;
	}

	// initialize left column
	for (i = 0; i < MAZESIZE; i++){
		maze[i][0].init_l = true;
	}

	// initialize right column 
	for (i = 0; i < MAZESIZE; i++){
		maze[i][MAZESIZE-1].init_r = true;
	}

	// initialize bottom row
	for (j = 0; j < MAZESIZE; j++){
		maze[MAZESIZE-1][j].init_b = true;
	}

	// container for tiles
	vector<tile> inmaze; 

	// put initial tile in container
	inmaze.push_back(maze[0][0]);

	// let tile know it's in the maze
	maze[0][0].inMaze = true;

	
	// seed for random, problems when I tried to do it globally for choosetile()
	srand(time(NULL));
	
	tile current; // currently selected tile
	unsigned int curr_pos; // currently selected tile pos in inmaze
	int next; // next tile pos to possibly add
	while (inmaze.size() > 0){
		//cout << "Current size: " << inmaze.size() << endl;
		for (i = 0; i < inmaze.size(); i++){
			//cout << inmaze[i].pos << " ";
		}
		//cout << endl;

		// choose random tile
		curr_pos = rand() % inmaze.size();
		current = inmaze[curr_pos];
		inmaze.erase(inmaze.begin() + curr_pos);
		//cout << "Random tile pos: " << current.pos << endl;
		// if all walls true/false
		if (checksides(&current)){
			// remove tile
			//inmaze.erase(inmaze.begin() + curr_pos);
			//cout << "All sides init\n";
		}
		else {
			// choose random unintialized wall
			next = choosetile(&current);
			//cout << "Next: " << next << endl;
			// if tile behind wall is not in inmaze
			if (!inthemaze(inmaze,next))
			{
				//cout << "Next not in maze\n";
				// set corresponding wall / init_wall in tile to true
				//setemupnice(&current, &maze[next/MAZESIZE][next%MAZESIZE]);
				setemupnice(&maze[current.pos/MAZESIZE][current.pos%MAZESIZE], &maze[next/MAZESIZE][next%MAZESIZE]);
				// add tile to inmaze
				inmaze.push_back(maze[current.pos/MAZESIZE][current.pos%MAZESIZE]);
				inmaze.push_back(maze[next/MAZESIZE][next%MAZESIZE]);
				//cout << "Added maze[" << next/MAZESIZE << "][" << next%MAZESIZE << "]\n";
			}
			// else set wall = false / init_wall = true
			else
			{
				//cout << "Next already in maze\n";
				//setemuphalf(&current, &maze[next/MAZESIZE][next%MAZESIZE]);
				setemuphalf(&maze[current.pos/MAZESIZE][current.pos%MAZESIZE], &maze[next/MAZESIZE][next%MAZESIZE]);
				inmaze.push_back(maze[current.pos/MAZESIZE][current.pos%MAZESIZE]);
			}
		}
	}

	printthatprim();
	printrevprim();

	// End of long comment */ 
	return 0;
}

int checksides(tile* current)
{
	//cout << current->pos << " sides = u: " << current->init_t << " l: " << current->init_l <<
	//	" r: " << current->init_r << " d: " << current->init_b << endl;
	if( current->init_t == true && current->init_l == true &&
		current->init_r == true && current->init_b == true ) {
		return 1;
	}
	else {
		return 0;
	}
}

// you could probably use this function to get rid of checksides
// assuming you return 0 or something for 
// available_tiles.size() == 0
int choosetile(tile* current)
{
	vector<int> available_tiles;
	int choice;
	if (!current->init_t){
		available_tiles.push_back(1);
	}

	if (!current->init_l){
		available_tiles.push_back(2);
	}

	if (!current->init_r){
		available_tiles.push_back(3);
	}

	if (!current->init_b){
		available_tiles.push_back(4);
	}

	choice = rand() % available_tiles.size();

	// switch to tell which next tile to add
	// 1 is up one row = - MAZESIZE
	// 2 is left one col = - 1
	// 3 is right one col = + 1
	// 4 is down one row  = + MAZESIZE
	switch(available_tiles[choice])
	{
		case 1:
			//cout << "UP: " << available_tiles[choice] << "\n";
			return current->pos - MAZESIZE;
			break;
		case 2:
			//cout << "LEFT: " << available_tiles[choice] << "\n";
			return current->pos - 1;
			break;
		case 3:
			//cout << "RIGHT: " << available_tiles[choice] << "\n";
			return current->pos + 1;
			break;
		case 4:
			//cout << "DOWN: " << available_tiles[choice] << "\n";
			return current->pos + MAZESIZE;
			break;
		default:
			cout << "You dun fuck'd it up! CHOICE: " << available_tiles[choice] << endl;
			return 0;
			break;
	}
	return 0;
}

bool inthemaze(vector<tile> inmaze, int next)
{
	unsigned int i;
	for (i = 0; i < inmaze.size(); i++){
		if (inmaze[i].pos == next){
			return true;
		}
	}
	return false;
}

// These will probably fail knowing my track record with pointers
// occurs when next isn't in inmaze
// should set current and next up with initializations 
void setemupnice(tile *current, tile *next)
{
	if (next->pos == (current->pos - MAZESIZE))
	{
		current->top = true;
		current->init_t = true;
		next->bottom = true;
		next->init_b = true;
	}

	else if (next->pos == (current->pos - 1))
	{
		current->left = true;
		current->init_l = true;
		next->right = true;
		next->init_r = true;
	}

	else if (next->pos == (current->pos + 1))
	{
		current->right = true;
		current->init_r = true;
		next->left = true;
		next->init_l = true;
	}

	else if (next->pos == (current->pos + MAZESIZE))
	{
		current->bottom = true;
		current->init_b = true;
		next->top = true;
		next->init_t = true;
	}

	else{
		cout << "It was a FIRE FIGHT!!!!\n";
	}
}
/*
void setemupnice(tile *current, tile *next)
{
	if (*next.pos == *current.pos - MAZESIZE)
	{
		*current.top = true;
		*current.init_t = true;
		*next.bottom = true;
		*next.init_b = true;
	}

	else if (*next.pos == *current.pos - 1)
	{
		*current.left = true;
		*current.init_l = true;
		*next.right = true;
		*next.init_r = true;
	}

	else if (*next.pos == *current.pos + 1)
	{
		*current.right = true;
		*current.init_r = true;
		*next.left = true;
		*next.init_l = true;
	}

	else if (*next.pos == *current.pos + MAZESIZE)
	{
		*current.bottom = true;
		*current.init_b = true;
		*next.top = true;
		*next.init_t = true;
	}

	else{
		cout << "It was a FIRE FIGHT!!!!\n";
	}
}
*/

// occurs when next is already in inmaze
// should set current up with initializations 
void setemuphalf(tile *current, tile *next)
{
	if (next->pos == current->pos - MAZESIZE)
	{
		//current->top = false;
		current->init_t = true;
	}

	else if (next->pos == current->pos - 1)
	{
		//current->left = false;
		current->init_l = true;
	}

	else if (next->pos == current->pos + 1)
	{
		//current->right = false;
		current->init_r = true;
	}

	else if (next->pos == current->pos + MAZESIZE)
	{
		//current->bottom = false;
		current->init_b = true;
	}

	else{
		cout << "It was a SHIT STORM!!!!\n";
	}
}
/*
void setemuphalf(tile *current, tile *next)
{
	if (*next.pos == *current.pos - MAZESIZE)
	{
		*current.top = false;
		*current.init_t = true;
	}

	else if (*next.pos == *current.pos - 1)
	{
		*current.left = false;
		*current.init_l = true;
	}

	else if (*next.pos == *current.pos + 1)
	{
		*current.right = false;
		*current.init_r = true;
	}

	else if (*next.pos == *current.pos + MAZESIZE)
	{
		*current.bottom = false;
		*current.init_b = true;
	}

	else{
		cout << "It was a SHIT STORM!!!!\n";
	}
}
*/


// print out prim maze
void printthatprim()
{
	int i,j;

	for (i = 0 ; i < MAZESIZE; i++){
		for (j = 0; j < MAZESIZE; j++) {
			// top row
			if (!maze[i][j].left){
				cout << "|";
			} else {
				cout << " ";
			}
			if (!maze[i][j].top){
				cout << "--";
			}else{
				cout << "  ";
			}
			if (!maze[i][j].right){
				cout << "|";
			}else{
				cout << " ";
			}
		}
		cout << endl;
		for (j = 0; j < MAZESIZE; j++) {
			// bottom row
			if (!maze[i][j].left){
				cout << "|";
			}else{
				cout << " ";
			}
			if (!maze[i][j].bottom){
				cout << "__";
			}else{
				cout << "  ";
			}
			if (!maze[i][j].right){
				cout << "|";
			}else{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

// print out prim maze
void printrevprim()
{
	int i,j;

	for (i = 0 ; i < MAZESIZE; i++){
		for (j = 0; j < MAZESIZE; j++) {
			// top row
			if (!maze[i][j].top){
				cout << "  |  ";
			}else{
				cout << "     ";
			}
		}
		cout << endl;
		for (j = 0; j < MAZESIZE; j++) {
			// middle row
			if (!maze[i][j].left){
				cout << "-- ";
			}else{
				cout << "   ";
			}
			if (!maze[i][j].right){
				cout << "--";
			}else{
				cout << "  ";
			}
		}
		cout << endl;
		for (j = 0; j < MAZESIZE; j++) {
			// bottom row
			if (!maze[i][j].bottom){
				cout << "  |  ";
			}else{
				cout << "     ";
			}
		}
		cout << endl;
	}
	cout << endl;
}
