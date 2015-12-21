#include "dijkstra.h"
#include <iostream>
#include <QQueue>

using namespace std;

Dijkstra::Dijkstra(QList<Node*> n)
{
  nodes = n;
}

QList<Node*> Dijkstra::getCluster(Node* source)
{
  QList<Node*> list;
  list.append(source);
  addNodes(source, list);
  return list;
}


void Dijkstra::addNodes(Node* node, QList<Node*>& list)
{
  foreach(Node* n, node->getNeighbours())
  {
    if(!list.contains(n))
    {
      list.append(n);
      addNodes(n,list);
    }
  }
}

void Dijkstra::resetNodes()
{
  foreach(Node* node, nodes)
  {
    visited.insert(node, false);
    back_pointer.insert(node, NULL);
    cost.insert(node, 0);
  }
}

double Dijkstra::getConnectivityProbability(Node* source)
{
  resetNodes();

  // put the source into pq and loop until empty
  QQueue<Node*> pq;
  pq.enqueue(source);

  while(!pq.isEmpty())
  {
    // process least cost node.
    Node* curr = pq.dequeue();
    visited[curr] = true;

    // process neighbors
    QList<Node*> neighbours = curr->getNeighbours();

    foreach(Node* ne, neighbours)
    {
      if(!visited[ne])
      {
        cost[ne] += 1;
        visited[ne] = true;
        back_pointer[ne] = curr;
        pq.enqueue(ne);
      }
    }
  }

  int i = 0;

  foreach(Node* n, cost.keys())
  {
    if(cost[n]>0)
      i++;
  }

  return 1-((double)i)/cost.size();
}
