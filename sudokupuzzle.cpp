#include "sudokupuzzle.h"
#include <QDebug>

SudokuPuzzle::SudokuPuzzle(unsigned char level): isSolved(false)
{
    this->cells = generatePuzzle(level);
}

SudokuPuzzle::~SudokuPuzzle()
{

}

bool SudokuPuzzle::setUserValue(unsigned char row, unsigned char col, unsigned char value)
{
    if(this->cells[row][col]->setUserValue(value)){
        bool puzzleIsSolved = true;
        for(unsigned char i = 0; i < 9; i++)
            for(unsigned char j = 0; j < 9; j++){
                puzzleIsSolved = puzzleIsSolved && this->cells[i][j]->getSolved();
            }
        this->isSolved = puzzleIsSolved;
        return true;
    }
}

bool SudokuPuzzle::getIsSolved()
{
    return this->isSolved;
}

unsigned char SudokuPuzzle::getSolution(unsigned char row, unsigned char col)
{
    return this->cells[row][col]->getSolution();
}

 std::vector<std::vector<SudokuPuzzle::Cell*>> SudokuPuzzle::generatePuzzle(unsigned char level)
{
     std::vector<char> puzzle;
     std::vector<char> solution;
     unsigned char lv = level % 4;
     //qDebug() << "level "<< lv;
    switch(lv){
        case 0 :
            generateTestPuzzle(puzzle, solution);
            break;
        case 2 :
            generateMediumPuzzle(puzzle, solution);
            break;
        case 3 :
            generateHardPuzzle(puzzle, solution);
            break;
        case 1 :
        default:
            generateEasyPuzzle(puzzle, solution);
            //break;
    }


     std::vector<std::vector<Cell*>> cells;
     for (unsigned int i = 0; i < 9; ++i) {
             std::vector<Cell*> v;
             for (unsigned int j = 0 ; j  < 9; ++j) {
                 v.push_back(new Cell(puzzle[i*9+j],solution[i*9+j]));
             }
             cells.push_back(v);
         }
     return cells;

 }

 void SudokuPuzzle::generateTestPuzzle(std::vector<char> &puzzle, std::vector<char> &solution)
 {
     puzzle.erase(puzzle.begin(), puzzle.end());
     puzzle = {
         9,1,5, 6,8,7, 2,3,4,
         4,2,7, 9,1,3, 8,5,6,
         6,8,3, 2,5,4, 7,1,9,

         5,9,8, 1,6,2, 4,7,3,
         1,3,2, 4,7,9, 5,6,8,
         7,6,4, 5,3,8, 9,2,1,

         3,4,9, 7,2,6, 1,8,5,
         2,5,6, 8,9,1, 3,4,7,
         8,7,1, 3,4,5, 6,9,0
     };

     solution.erase(solution.begin(), solution.end());
     solution = {
         9,1,5, 6,8,7, 2,3,4,
         4,2,7, 9,1,3, 8,5,6,
         6,8,3, 2,5,4, 7,1,9,

         5,9,8, 1,6,2, 4,7,3,
         1,3,2, 4,7,9, 5,6,8,
         7,6,4, 5,3,8, 9,2,1,

         3,4,9, 7,2,6, 1,8,5,
         2,5,6, 8,9,1, 3,4,7,
         8,7,1, 3,4,5, 6,9,2
     };
 }

void SudokuPuzzle::generateEasyPuzzle(std::vector<char> &puzzle, std::vector<char> &solution)
 {
    puzzle.erase(puzzle.begin(), puzzle.end());
    puzzle = {
              0,1,5, 6,0,7, 0,3,4,
              0,2,7, 0,0,0, 0,5,0,
              6,8,0, 0,0,4, 7,1,0,

              5,0,0, 1,0,0, 4,0,0,
              0,3,0, 0,7,0, 0,0,5,
              0,0,4, 0,0,8, 9,2,0,

              3,0,9, 7,0,6, 1,0,5,
              0,0,6, 8,9,1, 3,0,0,
              0,7,0, 3,0,5, 0,0,0
          };
    solution.erase(solution.begin(), solution.end());
          solution = {
              9,1,5, 6,8,7, 2,3,4,
              4,2,7, 9,1,3, 8,5,6,
              6,8,3, 2,5,4, 7,1,9,

              5,9,8, 1,6,2, 4,7,3,
              1,3,2, 4,7,9, 5,6,8,
              7,6,4, 5,3,8, 9,2,1,

              3,4,9, 7,2,6, 1,8,5,
              2,5,6, 8,9,1, 3,4,7,
              8,7,1, 3,4,5, 6,9,2
        };
 }

 void SudokuPuzzle::generateMediumPuzzle(std::vector<char> &puzzle, std::vector<char> &solution)
 {

     generateEasyPuzzle(puzzle, solution);
 }

 void SudokuPuzzle::generateHardPuzzle(std::vector<char> &puzzle, std::vector<char> &solution)
 {
     return generateEasyPuzzle(puzzle,solution);
 }


SudokuPuzzle::Cell::Cell(unsigned char userValue,unsigned char solutionValue)
{
    //set solution value
    if(solutionValue < 1) {
        this->solutionValue = 1;
    }
    else if (solutionValue > 9)
    {
        this->solutionValue = 9;
    }
    else
    {
        this->solutionValue = solutionValue;
    }

    //set userValue ad solved
    this->solved = false; // tmp
    if(!this->setUserValue(userValue))
    {
        this->userValue = 0;
        this->solved = false;
    }

}

bool SudokuPuzzle::Cell::getSolved()
{
    return this->solved;
}

unsigned char SudokuPuzzle::Cell::getSolution()
{
    return this->solutionValue;
}

unsigned char SudokuPuzzle::Cell::getUserValue()
{
    return this->userValue;
}

bool SudokuPuzzle::Cell::setUserValue(unsigned char value)
{
    // chack range
    if(value > 9 || value < 0)
    {
        return false;
    }

    // set userValue and update solved
    this->userValue = value;
    if(this->userValue == this->solutionValue)
    {
       this->solved = true;
    }
    else
    {
        this->solved = false;
    }
    return true;
}
