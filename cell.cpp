#include "gameoflife.h"

Cell::Cell(): QGraphicsRectItem()
{
    config();
}

Cell::Cell(QRectF rect): QGraphicsRectItem(rect)
{
    config();
}

void Cell::config()
{
    state = DEAD;
    setToolTip("Click to toggle the state.");
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setPen(QPen(Qt::gray,Qt::SolidLine));

    QGraphicsRectItem::paint(painter,option,widget);
    if(state == ALIVE)
        setBrush(QBrush(Qt::black,Qt::SolidPattern));
    else
        setBrush(QBrush(Qt::white,Qt::SolidPattern));

}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (state == ALIVE)
        setState(DEAD);
    else
        setState(ALIVE);
}

void Cell::setState(State state)
{
    this->state = state;
    update();
}

State Cell::getState()
{
    return state;
}

void Cell::setNextState(State nextState)
{
    this->nextState = nextState;
}

State Cell::getNextState()
{
    return nextState;
}

void Cell::die()
{
    setNextState(DEAD);
}

void Cell::live()
{
    setNextState(ALIVE);
}




