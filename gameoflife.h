#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QMainWindow>
#include <QObject>
#include <QTimer>

#include "cell.h"

namespace Ui {
class GameOfLife;

}

class GameOfLife : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOfLife(QWidget *parent = 0);
    void makeGrid();
    void createCells();
    void setInitialState();
    ~GameOfLife();

public slots:
    void updateState();
    void pauseResume();
    void setSpeed(int time);
    void clear();

protected:
    void resizeEvent( QResizeEvent* );

private:
    Ui::GameOfLife *ui;
    QGraphicsScene *scene;
    Cell** cells;
    int dimx,dimy;
    QTimer *timer;
    bool isRunning;


    void setup();
};

#endif // GAMEOFLIFE_H
