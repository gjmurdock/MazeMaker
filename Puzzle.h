/******************************************************************************
 * Author: Luis Valencia
 * Puzzle.h Header Class File
 * Date Last Modified: 02/14/2012
 ******************************************************************************/
#include<string>
#include<vector>
using namespace std;
const string defaultPuzzle = "./Puzzles/Puzzle.Properties";
class Puzzle
{
   private:
      vector<vector<char> > container;
      vector<int> heights; 
      vector<int> widths;
   public:
      Puzzle (string filename = defaultPuzzle);
      int sizeOfContainer();
      //Metric System (count base 0)
      char charAt(int floor, int x, int y);
      void printMaze(int floor);
};
