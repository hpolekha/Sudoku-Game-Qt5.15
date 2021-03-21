#ifndef SUDOKUPUZZLE_H
#define SUDOKUPUZZLE_H
#include <vector>
#include <memory>
class SudokuPuzzle
{
public:
    SudokuPuzzle(unsigned char level);
    ~SudokuPuzzle();
    class Cell
    {
    public:

        Cell():solved(false),solutionValue(1), userValue(1){}
        Cell(unsigned char solutionValue, unsigned char userValue);
        bool getSolved();
        unsigned char getSolution();
        unsigned char getUserValue();
        bool setUserValue(unsigned char value);
    private:
        unsigned char userValue;
        unsigned char solutionValue;
        bool solved;
    };
    bool setUserValue(unsigned char row, unsigned char col, unsigned char value);
    bool getIsSolved();
    unsigned char getSolution(unsigned char row, unsigned char col);
    //Cell ***cells;
    //Cell*** generatePuzzle();
    std::vector<std::vector<Cell*>> cells;
    std::vector<std::vector<Cell*>> generatePuzzle(unsigned char level);
    void generateHardPuzzle(std::vector<char> &puzzle, std::vector<char> &solution);
    void generateEasyPuzzle(std::vector<char> &puzzle, std::vector<char> &solution);
    void generateMediumPuzzle(std::vector<char> &puzzle, std::vector<char> &solution);
    void generateTestPuzzle(std::vector<char> &puzzle, std::vector<char> &solution);

    //std::vector<std::vector<Cell>> cells;
    //std::vector<std::vector<std::unique_ptr<Cell>>> generatePuzzle();
private:
    bool isSolved;

};

#endif // SUDOKUPUZZLE_H
