/******************************************************************************
 * Author: Luis Valencia
 * Puzzle.cpp Class File
 * Date Last Modified: 02/14/2012
 ******************************************************************************/
#include<cstdio>
#include<cstdlib>
#include"Puzzle.h"
//-----------------------------------------------------------------------------
//Class Puzzle
//-----------------------------------------------------------------------------
// Method: Constructor
// Purpose: Given a Filename of a Puzzle Properties Structure it reads the 
//          number of Mazes and the subsequent Maze Names and then opens
//          those files and reads the height and width (in that order) of that 
//          maze and proceeds to read in the maze (char by char) into an array
Puzzle::Puzzle(string filename)
{
   //Open the Puzzle Property File
   FILE * f = fopen(filename.c_str(), "r");
   //Structure: # of Floors, followed by FloorNames
   int floors;
   vector<string> filenames;
   if (f == NULL) { printf("Couldn't Open Puzzle File\n"); exit(-1); }
   else
   {
      fscanf(f, "%d", &floors);
      container.resize(floors);
      char name[100];
      //Traverse the Filenames, Keep file names under 100 chars
      for(int i = 0; i < floors; i++)
      {
         fscanf(f, "%s\n", name);
         FILE * maze = fopen(name, "r");
         //Maze structure: the Height, the Width, the actual Maze chars
         int height;
         int width;
         if (maze == NULL) { printf("Couldn't Open Maze File %s\n", name); exit(-1); }
         else 
         {
            fscanf(maze, "%d", &height);
            fscanf(maze, "%d", &width);
            heights.push_back(height);
            widths.push_back(width);
            printf("Populating Maze %s\n", name);
            char c; 
            while (fscanf(maze, "%c", &c) && c != '`') 
               if(c != '\n') { container[i].push_back(c); }
         }
      }
	}
}
//-----------------------------------------------------------------------------
// Method: sizeOfContainer
// Purpose: returns the number of Mazes in the Container
int Puzzle::sizeOfContainer() { return container.size(); }
//-----------------------------------------------------------------------------
// Method: printMaze
// Purpose: given a floor "a maze" it prints that maze
void Puzzle::printMaze(int floor)
{
   printf("Maze %d has dimensions %d x %d\n", floor, heights[floor], widths[floor]);
   printf("%d Characters, Printing Maze...\n",  (int)container[floor].size());
   for(int i = 0; i < container[floor].size(); i++)
   {
      if(i != 0 && i % widths[floor] == 0){ printf("\n"); }
      printf("%c", container[floor][i]);
   }
   printf("\n");
}
//-----------------------------------------------------------------------------
// Method: charAt
// Purpose: given the floor and the coordinates (count base 0) it returns the 
//          character at that point for the Maze (pesudo 2D array in a 1D array)
char Puzzle::charAt(int floor, int x, int y){ return container[floor][x*widths[floor]+y]; }
//-----------------------------------------------------------------------------
