#include "field.h"
#include <QDebug>
//#include <QPainter>
//#include <QGraphicsItem>
#define DEFAULT_CELL_SIZE 51
//#include "sudokupuzzle.h"
#include <QObject>
#include <QMetaObject>



Field::Field(QGraphicsItem *parent, int row_number, int col_number, unsigned char level)
    : QGraphicsItem(parent), row_number(row_number), col_number(col_number)
{
    this->lastActivated = nullptr;
    width = col_number * DEFAULT_CELL_SIZE + 3 * 2;
    height = row_number * DEFAULT_CELL_SIZE + 3 * 2;
    this->puzzle = new SudokuPuzzle(level);
    bool editable = true;
    for (unsigned int i = 0; i < row_number; ++i) {
            std::vector<Cell*> v;
            for (unsigned int j = 0 ; j  < col_number; ++j) {
                char tmp = this->puzzle->cells[i][j]->getUserValue();
                QString text = "";
                editable  = true;
                if(tmp > 0) {
                    editable = false;
                    text = QString::number(tmp);
                }
                v.push_back(new Cell(this, i, j, DEFAULT_CELL_SIZE, editable, text));
            }
            cells.push_back(v);
        }

}
bool Field::updatePuzzleCell(unsigned int row, unsigned int col, unsigned char value)
{

    bool t = this->puzzle->setUserValue(row, col, value);
   // qDebug() << "here(" << this->puzzle.cells[row][col]->getSolved() << ") for " << value <<" with " << this->puzzle.cells[row][col]->getUserValue();
   if(this->puzzle->getIsSolved())
   {
       triggerGameEnd();
       for(unsigned char i = 0; i < 9; i++){

           for(unsigned char j = 0; j < 9; j++){

               this->cells[i][j]->setEditable(false);
           }
       }
   }

    if(this->puzzle->cells[row][col]->getSolved())
    {
        return true;
    }

    return false;
}

void Field::showHint()
{

    if(this->lastActivated != nullptr)
        this->showHintForCell(this->lastActivated->getRow(), this->lastActivated->getCol());
}
void Field::showHintForCell(unsigned char row, unsigned char col){
    unsigned char solution = this->getCellSolution(row, col);
    this->cells[row][col]->setText(solution);
    this->cells[row][col]->setTextColor(Qt::red);
}
void Field::showSolution()
{
     for (unsigned int i = 0; i < row_number; ++i)
     {
          for (unsigned int j = 0; j < col_number; ++j)
          {
              if(this->cells[i][j]->getEditable())
              {
                   this->showHintForCell(i,j);
              }
          }
     }
}

unsigned char Field::getCellSolution(unsigned int row, unsigned int col)
{
    return this->puzzle->getSolution(row,col);
}




Field::~Field()
{
    delete this->puzzle;
};
QRectF Field::boundingRectk() const
{
    return QRectF(-width / 2, -height / 2, width, height);
}

void Field::setWidth(qreal width) {
    if (width > 0) {
        this->width = width;
    }
}
void Field::setHeight(qreal height) {
    if (height > 0) {
        this->height = height;
    }
}

void Field::setLastActivated(Cell *cell)
{
    this->lastActivated = cell;
}



void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr)
{
    QRectF rec = boundingRectk();
    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRect(rec);


    painter->fillRect(boundingRectk(), Qt::black);

}
