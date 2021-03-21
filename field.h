#ifndef FIELD_H
#define FIELD_H
#include "cell.h"
#include "sudokupuzzle.h"
#include <QObject>

class Field : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    //Cell ***cells;
    std::vector<std::vector<Cell*>> cells;

    Field(QGraphicsItem *parent, int row_number, int col_number, unsigned char level);
    ~Field();
    QRectF boundingRectk() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //void showHintActivate();
//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //void setSize(qreal size);
    void setWidth(qreal width);
    void setHeight(qreal height);
    //void updatePuzzleCell(unsigned char row, unsigned char col, unsigned char newUserValue);
    //void updatePuzzleCell(unsigned char i);
    void setLastActivated(Cell* cell);
    void showHint();
    void showSolution();
    void showHintForCell(unsigned char row, unsigned char col);
private:
    //qreal size;
    Cell* lastActivated;
    qreal width;
    qreal height;
    const int row_number;
    const int col_number;
    SudokuPuzzle *puzzle;

public:// slots:
    bool updatePuzzleCell(unsigned int row, unsigned int col, unsigned char i);
    unsigned char getCellSolution(unsigned int row, unsigned int col);
signals:
    //void signalTextChanged(unsigned char i);
    void triggerGameEnd();
};

#endif // FIELD_H
