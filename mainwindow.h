#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
//#include <QGraphicsScene>
#include <QResizeEvent>
#include <QElapsedTimer>
#include "cell.h"
#include "field.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void updateGame();
    void newGame();
    void setLevel(unsigned char level);
    void getLevel();
    void setLevelToTest();
    void setLevelToEasy();
    void setLevelToMedium();
    void setLevelToHard();
    void showHelp();
protected:
    void timerstart();
private:
    unsigned char level;
    QTimer*Timer;
    QTime*Timerecord;
    QElapsedTimer *stopWatch;

    void drawPixmapOnScene(QString filename);
    void updateSize();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Field *field;
    Cell *cells[9][9];
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    int CellSize;
    bool resize = false;
    QTimer *timer;
    void timeupdate();
    void closeWindow();

};
#endif // MAINWINDOW_H
