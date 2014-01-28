#include <QPainter>
#include <QPushButton>
#include <QLineEdit>

#include "gameoflife.h"
#include "ui_gameoflife.h"
#include "cell.h"

GameOfLife::GameOfLife(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::GameOfLife)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;

    dimx = 40;
    dimy = 40;

    isRunning = false;
    timer = new QTimer();
    timer->setInterval(100);

    setup();

    createCells();
    makeGrid();

    //setInitialState();
}

void GameOfLife::setup()
{
    ui->clockSlider->setMinimum(50);
    ui->clockSlider->setMaximum(2000);
    ui->clockSlider->setValue(500);
    ui->clockSlider->setTickInterval(50);

    ui->view->setScene(scene);
    setCentralWidget(ui->widget);

    connect(ui->startStopButton, SIGNAL(clicked()), this, SLOT(pauseResume()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(timer, SIGNAL(timeout()), this, SLOT(updateState()));
    connect(ui->clockSlider,SIGNAL(valueChanged(int)),this,SLOT(setSpeed(int)));

}

void GameOfLife::setSpeed(int time)
{
    timer->setInterval(time);
}

void GameOfLife::clear()
{
    for(int i = 0 ; i < dimx ; i++)
        for(int j = 0; j < dimy ; j++)
            cells[i][j].setState(DEAD);
}

void GameOfLife::pauseResume()
{
    if(isRunning)
    {
        timer->stop();
        ui->startStopButton->setText("Resume");
    }
    else
    {
        timer->start();
        ui->startStopButton->setText("Pause");
    }
    isRunning = !isRunning;
}

void GameOfLife::updateState()
{
    int numLiveNeighbors = 0;

    for(int i = 0 ; i < dimx ; i++)
    {
        for(int j = 0; j < dimy ; j++)
        {
            numLiveNeighbors = 0;
            if((i-1 >= 0 && j-1 >= 0) && cells[i-1][j-1].getState() == ALIVE)
                numLiveNeighbors++;
            if((i-1 >= 0) && cells[i-1][j].getState() == ALIVE)
                numLiveNeighbors++;
            if((i-1 >= 0 && j+1 < dimy) && cells[i-1][j+1].getState() == ALIVE)
                numLiveNeighbors++;
            if((j-1 >= 0) && cells[i][j-1].getState() == ALIVE)
                numLiveNeighbors++;
            if((j+1 < dimy) && cells[i][j+1].getState() == ALIVE)
                numLiveNeighbors++;
            if((i+1 < dimx && j-1 >= 0) && cells[i+1][j-1].getState() == ALIVE)
                numLiveNeighbors++;
            if((i+1 < dimx) && cells[i+1][j].getState() == ALIVE)
                numLiveNeighbors++;
            if((i+1 < dimx && j+1 < dimy) && cells[i+1][j+1].getState() == ALIVE)
                numLiveNeighbors++;

            if (numLiveNeighbors < 2 || numLiveNeighbors > 3)
                cells[i][j].setNextState(DEAD);
            if (numLiveNeighbors == 2)
                cells[i][j].setNextState(cells[i][j].getState());
            if (numLiveNeighbors == 3)
                cells[i][j].setNextState(ALIVE);
        }
    }

    for(int i = 0 ; i < dimx ; i++)
        for(int j = 0; j < dimy ; j++)
            cells[i][j].setState(cells[i][j].getNextState());
}

void GameOfLife::setInitialState()
{
    for(int i = 0; i < dimx; i++)
    {
        for(int j = 0; j < dimy; j++)
        {

            if (rand() % 2 == 0)
                cells[i][j].setState(DEAD);
            else cells[i][j].setState(ALIVE);
        }
    }
}

//TODO: Improve this function
void GameOfLife::resizeEvent( QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    for(int i = 0; i < dimx; i++)
        for(int j = 0; j < dimy; j++)
            scene->removeItem(&cells[i][j]);

    makeGrid();
}

void GameOfLife::createCells()
{
    cells = new Cell*[dimx];
    for(int i = 0; i < dimx ; i++)
    {
        cells[i] = new Cell[dimy];
    }
}

void GameOfLife::makeGrid()
{
    int w = width()/dimx;
    int h = height()/dimy;

    for(int i = 0; i < dimx; i++)
    {
        for(int j = 0; j < dimy; j++)
        {
            cells[i][j].setRect(i*w,j*h,w,h);
            scene->addItem(&cells[i][j]);
        }
    }
}

GameOfLife::~GameOfLife()
{
    delete ui;

    for(int i = 0; i < dimx ; i++)
        delete[] cells[i];

    delete cells;

    delete scene;
}
