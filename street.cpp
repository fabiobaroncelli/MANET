#include "street.h"
#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Street::Street(int i, int a, int b, int c, int d, double v)
{
  id = i;
  start.setX(a);
  start.setY(b);
  end.setX(c);
  end.setY(d);
  length = sqrt(pow(a-c,2)+pow(b-d,2));
  velocity = v;
  angle = atan2((d-b), (c-a))* 180 / 3.14;
}

void Street::setNeighbour(Street* s)
{
  if(!neighbours.contains(s))
    neighbours.append(s);
}

void Street::setNode(Node* n, int perc)
{
  nodes.insert(n, length*perc/100);
  n->setRotation(angle);
}

void Street::insertNode(Node* n)
{
  if(!nodes.contains(n))
  {
    nodes.insert(n,0);
    n->setPosition(start.x(),start.y());
    n->setRotation(angle);
  }
}

void Street::advance()
{
  double dist;
  double xd = end.x()-start.x();
  double yd = end.y()-start.y();
  QMap<Node*, double>::iterator i;

  for(i = nodes.begin(); i != nodes.end(); ++i)
  {
    dist = i.value() + velocity;

    if(dist>=length)
    {
      if(neighbours.size()>0)
      {
        Street* str = neighbours.at((int)rand()%(neighbours.size()));
        str->insertNode(i.key());
        nodes.remove(i.key());
      }
      else
        i.key()->setPosition(end.x(), end.y());
    }
    else
    {
      i.value() = dist;
      i.key()->setPosition(start.x() + xd*dist/length, start.y() + yd*dist/length);
    }
  }
}
