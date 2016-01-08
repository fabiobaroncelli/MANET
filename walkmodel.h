#ifndef WALKMODEL_H
#define WALKMODEL_H

#include <QList>
#include "node.h"

class WalkModel
{
  public:
    WalkModel(QList<Node*>, int);
    virtual void advance();
    virtual ~WalkModel(){}

  protected:
    int dim;
    QList<Node*> nodes;
};

#endif // WALKMODEL_H
