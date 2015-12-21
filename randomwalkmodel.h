#ifndef RANDOMWALKMODEL_H
#define RANDOMWALKMODEL_H

#include"walkmodel.h"

class RandomWalkModel : public WalkModel
{
  public:
    RandomWalkModel(QList<Node*>, int, bool);
    void advance();

  private:
    double Pi;
    bool border;
};

#endif // RANDOMWALKMODEL_H
