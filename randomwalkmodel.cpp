#include "randomwalkmodel.h"
#include <QGraphicsWidget>
#include <math.h>
#include <QGraphicsPixmapItem>

RandomWalkModel::RandomWalkModel(QList<Node*> n, int d, bool b): WalkModel(n, d)
{
  Pi = 3.141;
  border = b;

  foreach(Node* node, nodes)
    node->setPosition(rand()%dim,rand()%dim);
}

void RandomWalkModel::advance()
{
  foreach(Node* node, nodes)
  {
    double angle = node->getAngle();

    if((int)rand()%20 == 5)
    {
      angle = angle + (rand()%90)*Pi/180;
      node->setAngle(angle);
    }

    int dv = (int)(rand()%(node->getVelocity()));
    int x = node->getX();
    int dx = (int)(::cos(angle)*dv);
    int y = node->getY();
    int dy = (int)(::sin(angle)*dv);

    x += dx;
    y += dy;

    if(border)
    {
      if(x<0 || x>dim || y<0 || y>dim)
      {
        angle = angle + (rand()%90)*Pi/180;
        node->setAngle(angle);
      }
    }
    else
    {
      if(x<0)
        x = dim + x;
      else if(x>dim)
        x = x - dim;

      if(y<0)
        y = dim + y;
      else if(y>dim)
        y = y - dim;
    }

    node->setPosition(x,y);
  }
}
