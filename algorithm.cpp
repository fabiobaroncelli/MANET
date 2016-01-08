#include "algorithm.h"
#include <iostream>

using namespace std;

Algorithm::Algorithm(int t)
{
  type = t;
  start = true;
  percentage = 0;
  cicle = 0;
}

void Algorithm::advance()
{
  cicle++;

  switch(type)
  {
  case RANDOM_ALGORITHM:
    randomAlgorithm();
    break;

  case ANTILAPLACIAN_NORMALIZED_ALGORITHM:
    antiLaplacianNormalizedAlgorithm();
    break;
  }

  int i=0;
  foreach(NodeItem* n, nodeItems)
  {
    if(n->getNode()->getMsg())
      i++;
  }

  percentage = i/nodeItems.size();
}

void Algorithm::randomAlgorithm()
{
  if(start && nodeItems.size()>0)
  {
    setNodeMsg(nodeItems.at(0));
    start=false;
  }

  foreach(NodeItem* n, nodeItems)
  {
    Node* node = n->getNode();
    if(node->getMsg())
    {
      foreach(Node* nn, node->getNeighbours())
      {
        if(!nn->getMsg())
          setNodeMsg(nn);
      }
    }
  }
}

void Algorithm::antiLaplacianNormalizedAlgorithm()
{
  if(start && nodeItems.size()>0)
  {
    setNodeMsg(nodeItems.at(0));
    start=false;
    foreach(NodeItem* n, nodeItems)
    {
      n->getNode()->setScore(1);
      n->getNode()->setMedia(1);
    }
  }

  QMap<Node*, double> map;

  //Ogni nodo riceve lo score e la media dai vicini
  foreach(NodeItem* n, nodeItems)
  {
    double score = 0;
    double media = n->getNode()->getMedia();

    QList<Node*> neighbours = n->getNode()->getNeighbours();

    if(neighbours.size() == 0)
    {
      score = 1;
      media = 1;
    }
    else
    {
      foreach(Node* node, neighbours)
      {
        score += node->getScore();
        media += node->getMedia();
        if(!node->getMsg())
          setNodeMsg(node);
      }

      media = media/neighbours.size();
    }

    map.insert(n->getNode(), score/media);
  }

  //Ogni nodo setta il nuovo score
  foreach(Node* nnn, map.keys())
    nnn->setScore(map.value(nnn));

//  cout << cicle << "   " <<  nodeItems.at(0)->getNode()->getScore() << endl;
}

void Algorithm::setNodeMsg(NodeItem* n)
{
  n->getNode()->setMsg(true);
  n->setPixmap(QPixmap("./images/blue.png"));
}

void Algorithm::setNodeMsg(Node* node)
{
  NodeItem* nn;

  foreach(NodeItem* n, nodeItems)
  {
    if(n->getNode()==node)
    {
      nn = n;
    }
  }

  node->setMsg(true);
  nn->setPixmap(QPixmap("./images/blue.png"));
}
