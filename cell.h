#ifndef CELL_H
#define CELL_H
#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include <QObject>

#define SPACE 3;

class Cell :public QGraphicsItem
{

public:
    Cell(QGraphicsItem *parent, const unsigned int row, unsigned int const col, int size, bool editable, QString text = "");

    QRectF boundingRectk() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //bool Pressed;

    static void setSize(qreal size);
//    void setNumber(char number, QColor color);
//    char getNumber();
    void setTextColor(QColor color);
    QColor getTextColor();
    void updateTextAndColor(QString text, QColor color);
    void setText(unsigned char i);
    void updateColorAndRefresh(QColor color);
    void setEditable(bool value);
    bool getEditable();
    unsigned int getRow();
    unsigned int getCol();

//public slots:
    //void showHint();
protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
   // void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void focusInEvent(QFocusEvent *event);


private:
    bool editable;
    const qreal size;
    const int row;
    const int col;
    QString text;
    bool active;

    //char number;

    QColor textColor;
    QColor defaultTextColor;
signals:
    void signalTextChanged(unsigned char i);

};

#endif // CELL_H
