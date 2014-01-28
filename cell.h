#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainter>
#include <QGraphicsSceneEvent>
#include <QObject>

enum State { DEAD, ALIVE };

class Cell: public QObject,public QGraphicsRectItem
{
    Q_OBJECT

public:
    Cell();
    Cell(QRectF);
    void die();
    void live();
    State getState();
    void setNextState(State);
    State getNextState();
    void setState(State);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);

private:

    State state;
    State nextState;

    void config();
};



#endif // CELL_H
