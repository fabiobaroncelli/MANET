#include "streetwalkmodel.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

StreetWalkModel::StreetWalkModel(int g, QGraphicsScene* scene, QList<Node*> n, int d): WalkModel(n, d)
{
  //Create Streets
  int grid=g;
  double vel = 2;
  int dd = dim/grid;

  int id = 0;

  for(int x=0; x<=grid; x++)
    for(int y=0; y<=grid; y++)
    {
      int xx = x*dd;
      int yy = y*dd;

      if(x!=grid)
      {
        scene->addLine(xx, yy, xx+dd, yy);
        streets.append(new Street(id, xx, yy, xx+dd, yy, vel));
        id++;
      }

      if(x!=0)
      {
        scene->addLine(xx, yy, xx-dd, yy);
        streets.append(new Street(id, xx, yy, xx-dd, yy, vel));
        id++;
      }

      if(y!=0)
      {
        scene->addLine(xx, yy, xx, yy-dd);
        streets.append(new Street(id, xx, yy, xx, yy-dd, vel));
        id++;
      }

      if(y!=grid)
      {
        scene->addLine(xx, yy, xx, yy+dd);
        streets.append(new Street(id, xx, yy, xx, yy+dd, vel));
        id++;
      }
    }

    //Set streets neighbours

    foreach(Street* str, streets)
    {
      QList<Street*> strs = searchNeighbours(str);
      foreach(Street* str1, strs)
        str->setNeighbour(str1);
    }

   //Put Nodes on Streets

   if(streets.size())
     foreach(Node* node, n)
     {
       int i = (int)rand()%(streets.size());
       Street* str = streets.at(i);
       str->setNode(node, (int)rand()%100);
     }
}

void StreetWalkModel::advance()
{
  foreach(Street* str, streets)
    str->advance();
}

QList<Street*> StreetWalkModel::searchNeighbours(Street* street)
{
  QList<Street*> st;

  foreach(Street* str, streets)
  {
    if(str->getStartPoint() == street->getEndPoint() && str->getEndPoint() != street->getStartPoint())
      st.append(str);
  }

  return st;
}
