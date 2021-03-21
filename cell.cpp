#include "cell.h"
#include "field.h"


Cell::Cell(QGraphicsItem *parent, const unsigned int row, const unsigned int col, const int size, bool editable, QString text)
           : QGraphicsItem(parent), row(row), col(col),size(size),text(text), editable(editable), active(false)
{

    if(this->editable)
    {
        this->defaultTextColor = Qt::blue;
    }
    else
    {
        this->defaultTextColor = Qt::black;
    }
    this->textColor = this->defaultTextColor;
    setFlag(ItemIsFocusable);

}
QRectF Cell::boundingRectk() const
{

    QRectF rec = QRectF(this->parentItem()->boundingRectk().x() + (col > 2 ? 3 : 0 ) + (col > 5 ? 3 : 0) + size * col,
                        this->parentItem()->boundingRectk().y() + (row > 2 ? 3 : 0 ) + (row > 5 ? 3 : 0) + size * row, size, size);
    return rec;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRectk();
    QBrush brush(Qt::cyan);

    if(active)
    {
       brush.setColor(QColor(76, 255, 243));
    }
    else
    {
        brush.setColor(QColor(187, 222, 251));
    }

    painter->fillRect(rec,brush);

    painter->drawRect(rec);

    painter->setPen(this->textColor);


    QFont font;
    font.setPixelSize(30);
    painter->setFont(font);
    painter->drawText(this->boundingRectk(),Qt::AlignCenter, text);

}

void Cell::setTextColor(QColor color)
{
    this->textColor = color;
}

QColor Cell::getTextColor()
{
    return this->textColor;
}

void Cell::updateTextAndColor(QString text, QColor color)
{
    this->text = text;
    this->textColor = color;
}

void Cell::setText(unsigned char i)
{
    this->text = QString::number(i);
    update();
}

void Cell::setEditable(bool value)
{
    this->editable = value;
}

bool Cell::getEditable()
{
    return this->editable;
}

unsigned int Cell::getRow()
{
    return this->row;
}


unsigned int Cell::getCol()
{
    return this->col;
}


void Cell::keyPressEvent(QKeyEvent *event)
{
    if (event->key() >= '1' && event->key() <= '9' && this->editable && this->active)
    {
       unsigned char value = event->key();
       this->text = value;
       QColor color = (static_cast<Field*>(this->parentItem())->updatePuzzleCell(this->row, this->col, value-'0') ? Qt::red : this->defaultTextColor);//this->signalTextChanged(i-'0');

       this->textColor = color;

       update();

    }
    else if(event->key() == Qt::Key_Backspace)//&& this->active)
    {
        this->text = "";
        static_cast<Field*>(this->parentItem())->updatePuzzleCell(this->row, this->col, 0);
        this->textColor = this->defaultTextColor;
        update();
    }

}



void Cell::focusOutEvent(QFocusEvent *event)
{
    this->active = false;
    if(this->editable)
        static_cast<Field*>(this->parentItem())->setLastActivated(this);
    this->update();
}
void Cell::focusInEvent(QFocusEvent *event)
{
    this->active = true;

    this->update();
}

