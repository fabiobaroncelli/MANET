#ifndef STREET_H
#define STREET_H

#include <QList>
#include <QMap>
#include "node.h"
#include <QPoint>

class Street
{
  public:
    Street(int, int, int, int, int, double);
    void setNeighbour(Street* s);
    QList<Street*> getNeighbour(){return neighbours;}
    void setNode(Node*, int);
    void insertNode(Node*);
    void advance();
    int getID(){return id;}
    QPoint getStartPoint(){return start;}
    QPoint getEndPoint(){return end;}

  private:
    int id;
    double velocity;
    double length;
    double angle;
    QList<Street*> neighbours;
    QMap<Node*, double> nodes;
    QPoint start;
    QPoint end;
};

#endif // STREET_H
