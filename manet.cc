/*
 * MANET
 * Copyright (C)  2010 <Fabio Baroncelli>
 */

#include <math.h>
#include "manet.h"
#include <QtAlgorithms>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <Eigen/Eigen>
#include "dijkstra.h"

using namespace Eigen;
using namespace std;

Manet::Manet()
{
  reset();
  firstAdjacencyMatrix = true;
}

Manet::~Manet()
{
  foreach(Node* node, nodeVectorX)
  {
    nodeVectorX.removeOne(node);
    delete node;
  }
}

void Manet::reset()
{
  dim = 500;
  hubDegree = 10;
  nodeDegree = 3;
//  startNodeNumber = 100;
  hubNumber = 0;
//  stepNode = 5;
//  endNodeNumber = 100;
  nodeNumber = 100;
  velocityHub = 5;
  velocityNode = 10;
  radiusNode = 50;
  radiusHub = 100;

  msgSendProbability = 1;
  msgBER = 7;
  msgLength = 10;
  bandwidth = 100;
  msgMaxHop = 100;
  msgMaxTime = 5000;
  msgMaxDistance = 200;

  degreeDistribution.clear();

  foreach(Node* node, nodeVectorX)
  {
    nodeVectorX.removeOne(node);
    delete node;
  }

  nodeVectorX.clear();
}

void Manet::start()
{
  srand(time(0));

  //Creazione HUB
  for(int t=0; t<hubNumber; t++)
    addHub();

  //Creazione nodi semplici
  for(int t=0; t<nodeNumber; t++)
    addNode();

  degreeDistribution.clear();
}

double Manet::calculate(QList<double> & array)
{    
  Dijkstra d(nodeVectorX);
  double cp = 0;

  for(int i=0; i<100; i++)
  {
    int i1 = (int)rand()%nodeVectorX.size();
    int i2 = (int)rand()%nodeVectorX.size();

    QList<Node*> list = d.getCluster(nodeVectorX.at(i1));
    if(list.contains(nodeVectorX.at(i2)))
      cp++;
  }

  foreach(Node* n, nodeVectorX)
  {
    if(keep)
      n->validateNeighbours();
    else
      n->resetNeighbours();
  }

  foreach(Node* node, nodeVectorX)
  {
    node->addNeighbours(getPotentialNeighbours(node), bid, attachmentType);
    int deg = node->getNeighbours().size();
    if(degreeDistribution.contains(deg))
      degreeDistribution[deg] += 1;
    else
      degreeDistribution.insert(deg, 1);
  }

  if(laplacianType!=NO_CALCULATION)
  {
    QList<double> eigen = getEigenvalues();

    for(int i=0; i<eigen.size(); i++)
    {
      if(array.size()<=i)
        array.append(0);
      array[i] += eigen[i];
    }

  }

  return cp/100;
}

MatrixXd Manet::getNormalizedLaplacian(bool type)
{
  int size = nodeVectorX.size();
  MatrixXd laplacian(size,size);
  laplacian << MatrixXd::Zero(size,size);

  for(int x=0; x<size; x++)
  {
    int dx = nodeVectorX[x]->getNeighbours().size();

    for(int y=0; y<size; y++)
    {
      int dy = nodeVectorX[y]->getNeighbours().size();

      if(dx != 0 && dy != 0)
      {
        if(x==y)
          laplacian(x,x) = 1;
        else if(nodeVectorX[x]->isNeighbour(nodeVectorX[y]))
        {
          if(type)
            laplacian(x,y) = -1/(sqrt(dx*dy));
          else
            laplacian(x,y) = 1/(sqrt(dx*dy));
        }
      }
    }
  }
  return laplacian;
}

MatrixXd Manet::getAdjacencyMatrix(bool normalized)
{
  int size = nodeVectorX.size();
  MatrixXd adjacency(size,size);
  adjacency << MatrixXd::Zero(size,size);

  for(int x=0; x<nodeVectorX.size(); x++)
  {
    int deg =nodeVectorX.at(x)->getNeighbours().size();
    if(deg == 0)
    {
      if(normalized)
        adjacency(x,x)=1;
    }
    else
    {
      foreach(Node* n, nodeVectorX.at(x)->getNeighbours())
      {
        int y = nodeVectorX.indexOf(n);
        if(normalized)
          adjacency(y,x) = 1/(double)deg;
        else
          adjacency(y,x) = 1;
      }
    }
  }

  if(firstAdjacencyMatrix)
  {
    adjacencyMatrix = adjacency;
    firstAdjacencyMatrix = false;
    cout << adjacencyMatrix << endl;
  }
  else
    adjacencyMatrix = adjacencyMatrix * adjacency;

//  cout << "----------------------------------------" << endl;
//  cout << adjacencyMatrix << endl;
//  cout << adjacencyMatrix(0,0) << endl;
  return adjacency;
}

MatrixXd Manet::getLaplacian(bool type)
{
  int size = nodeVectorX.size();
  MatrixXd laplacian(size,size);
  laplacian << MatrixXd::Zero(size,size);

  foreach(Node* node, nodeVectorX)
  {
    int x = nodeVectorX.indexOf(node);
    laplacian(x,x)=node->getNeighbours().size();

    foreach(Node* n, node->getNeighbours())
    {
      if(type)
        laplacian(x,nodeVectorX.indexOf(n)) = -1;
      else
        laplacian(x,nodeVectorX.indexOf(n)) = 1;
    }
  }

  return laplacian;
}

QList<double> Manet::getEigenvalues()
{
  MatrixXd laplacian;

  switch(laplacianType)
  {
    case STANDARD_LAPLACIAN:
      laplacian = getLaplacian(true);
      break;

    case SIGNLESS_LAPLACIAN:
      laplacian = getLaplacian(false);
      break;

    case NORMALIZED_LAPLACIAN:
      laplacian = getNormalizedLaplacian(true);
      break;

    case SIGNLESS_NORMALIZED_LAPLACIAN:
      laplacian = getNormalizedLaplacian(false);
      break;

    case ADJACENCY_MATRIX:
      laplacian = getAdjacencyMatrix(false);
      break;

    case NORMALIZED_ADJACENCY_MATRIX:
      laplacian = getAdjacencyMatrix(true);
      break;
  }

  powerMethod(laplacian, 50);

  SelfAdjointEigenSolver<MatrixXd> es(laplacian, true);

  QList<double> eigen;

  for(int i=0; i<laplacian.rows(); i++)
    eigen.append(es.eigenvalues()[i]);

  qSort(eigen.begin(), eigen.end());
  eigenVectors = es.eigenvectors();

  return eigen;
}

Node* Manet::addGenericNode(int deg, int vel, int dist, const char * pixName)
{
  Node* n = new Node(deg,vel,dist,pixName);
  nodeVectorX.append(n);
  degreeDistribution.clear();
  return n;
}

Node* Manet::addNode()
{
  return addGenericNode(nodeDegree, velocityNode, radiusNode, "./images/red.png");
}

Node* Manet::addHub()
{
  return addGenericNode(hubDegree, velocityHub, radiusHub, "./images/orange.png");
}

QList<Node*> Manet::getPotentialNeighbours(Node* node)
{
  QList<Node*> neighbours;

  foreach(Node* nn, nodeVectorX)
  {
    if(nn == node || abs(nn->getX()-node->getX())>node->getRadius())
      continue;

    if(node->isInRange(nn))
      neighbours.append(nn);
  }

  return neighbours;
}

void BubbleSort(long double arr[], int n)
{
  bool swapped = true;
  int j = 0;
  double tmp;

  while (swapped)
  {
    swapped = false;
    j++;

    for (int i = 0; i < n - j; i++)
    {
      if (arr[i] > arr[i + 1])
      {
        tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        swapped = true;
      }
    }
  }
}

bool XlessThan(const Node* n1, const Node* n2)
{
    return n1->getX() < n2->getX();
}

void Manet::norma(VectorXd & x)
{
  double sum = 0;

  for(int i=0; i<x.rows(); i++)
    sum = x.dot(x);

  x = x/sqrt(sum);
}

double Manet::energy(Node* node)
{
  double power = 0;

  foreach(Node* n, nodeVectorX)
  {
    if(n != node)
    {
      double dist = node->getDistance(n);
      power += 1/(dist*dist);
    }
  }
  return power;
}

VectorXd Manet::powerMethod(MatrixXd a, int it_max)
{
  VectorXd x = VectorXd::Ones(a.rows());

  for(int n=0; n<it_max; n++)
  {
    x = a*x;
    norma(x);
  }

  cout << energy(nodeVectorX.at(0)) << "\t" << x(0) << endl;

  return x;
}

