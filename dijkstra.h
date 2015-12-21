#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QMap>
#include <QList>
#include "node.h"

class Dijkstra
{
  public:

    Dijkstra(QList<Node*>);
    double getConnectivityProbability(Node*);
    QList<Node*> getCluster(Node*);

  private:
    QList<Node*> nodes;
    QMap<Node*,bool> visited;
    QMap<Node*,Node*> back_pointer;
    QMap<Node*,int> cost;

    void resetNodes();
    void addNodes(Node*, QList<Node*>&);

};

#endif // DIJKSTRA_H
