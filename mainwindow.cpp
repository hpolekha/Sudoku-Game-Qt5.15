#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "field.h"
#include <QDebug>
#define DEFAULT_CELL_SIZE 50
#include <QMetaObject>
#include "faq.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setStyleSheet("background: transparent");

    //set timer
    Timer=new QTimer(this);
    Timer->setInterval(1000);
    Timerecord=new QTime(0,0,0,0);
    ui->timer->setDigitCount(8);
    ui->timer->setSegmentStyle(QLCDNumber::Flat);
    ui->timer->display(Timerecord->toString("hh:mm:ss"));

    connect(Timer,&QTimer::timeout,this,&MainWindow::timeupdate);
    stopWatch = new QElapsedTimer();

    scene = new QGraphicsScene(this);
    //field = new Field(nullptr, 9, 9);
    //scene->addRect(-300,-300,600,600);
    QPixmap pixmap("/home/helena/Pictures/homer-rok.png");
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(0, 0);

    drawPixmapOnScene("/home/helena/Downloads/PAINy/MINE_proj/SudokuGame/img/sudoku.png");

    //exit button clicked
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::closeWindow);

    // new game click
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::newGame);

    //levels
    connect(ui->actionTest, &QAction::triggered, this, &MainWindow::setLevelToTest);
    connect(ui->actionEasy, &QAction::triggered, this, &MainWindow::setLevelToEasy);
    connect(ui->actionMedium, &QAction::triggered, this, &MainWindow::setLevelToMedium);
    connect(ui->actionHard, &QAction::triggered, this, &MainWindow::setLevelToHard);


    //help
    connect(ui->actionShow_help, &QAction::triggered, this, &MainWindow::showHelp);


    //newGame();
    this->level = 0;

}


void MainWindow::timerstart()
{
    Timerecord->setHMS(0,0,0,0);
    ui->timer->display(Timerecord->toString("hh:mm:ss"));

    stopWatch->start();
    Timer->start(500);

}

void MainWindow::drawPixmapOnScene(QString filename)
{
    scene = new QGraphicsScene(this);
    QPixmap pixmap(filename);
    scene->addPixmap(pixmap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(0, 0);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateSize()
{

    QRectF bounds = scene->itemsBoundingRect();
    ui->graphicsView->fitInView(bounds, Qt::KeepAspectRatio);

    ui->graphicsView->centerOn(0, 0);
}


void MainWindow::resizeEvent(QResizeEvent *event) {
//    if(resize)
        updateSize();
//    resize = true;

}

void MainWindow::showEvent(QShowEvent *event)
{
    updateSize();
}


void MainWindow::updateGame()
{
    ui->label->setText("Solved!");
    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->foregroundRole(), Qt::red);
    ui->label->setPalette(palette);
    QFont f = ui->label->font();
    f.setBold(true);
    ui->label->setFont(f);
    Timer->stop();

    //drawPixmapOnScene("/home/helena/Downloads/PAINy/MINE_proj/SudokuGame/img/congrats.png");
   // QPixmap pixmap("/home/helena/Downloads/PAINy/MINE_proj/SudokuGame/img/congrats.png");
   // scene->addPixmap(pixmap);
   // ui->graphicsView->centerOn(-300, -300);
    //ui->graphicsView->show();

}

void MainWindow::newGame()
{
    //set label
    ui->label->setText("Cood Luck!");
    QPalette palette = ui->label->palette();
    palette.setColor(ui->label->foregroundRole(), Qt::blue);
    ui->label->setPalette(palette);
    QFont f = ui->label->font();
    f.setBold(false);
    ui->label->setFont(f);

    //set board
    scene = new QGraphicsScene(this);
    field = new Field(nullptr, 9, 9, this->level);
    scene->addItem(field);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(0, 0);
    connect(field, &Field::triggerGameEnd, this, &MainWindow::updateGame);

    //hint
    connect(ui->pushButton_2, &QPushButton::clicked, field, &Field::showHint );

    //solution
    connect(ui->pushButton_3, &QPushButton::clicked, field, &Field::showSolution );

    timerstart();

}

void MainWindow::setLevel(unsigned char level)
{
   this->level = level % 4;
    newGame();
}

void MainWindow::setLevelToTest()
{
    this->setLevel(0);
}

void MainWindow::setLevelToEasy()
{
    this->setLevel(1);
}

void MainWindow::setLevelToMedium()
{
    this->setLevel(2);
}

void MainWindow::setLevelToHard()
{
    this->setLevel(3);
}

void MainWindow::showHelp()
{
    FAQ faq;
    faq.exec();
}

void MainWindow::timeupdate()
{
    Timerecord->setHMS(0,0,0,0);
    *Timerecord=Timerecord->addSecs(stopWatch->elapsed() / 1000);
    ui->timer->display(Timerecord->toString("hh:mm:ss"));
}

void MainWindow::closeWindow()
{
    this->close();
}


