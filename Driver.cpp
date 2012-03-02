#include"Puzzle.h"

using namespace std;

int main ()
{
   Puzzle *p = new Puzzle();
   for(int i = 0; i < 3; i++) p->printMaze(i);
   return 0;
}
