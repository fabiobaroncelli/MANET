#ifndef STREETWALKMODEL_H
#define STREETWALKMODEL_H

#include"walkmodel.h"
#include <QList>
#include <QPoint>
#include "street.h"
#include <QGraphicsScene>

class StreetWalkModel : public WalkModel
{
  public:
    StreetWalkModel(int, QGraphicsScene*, QList<Node*>, int);
    void advance();

  private:
    QList<Street*> streets;
    QList<Street*> searchNeighbours(Street*);
};

#endif // STREETWALKMODEL_H
