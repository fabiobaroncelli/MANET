/*
 * manet
 * Copyright (C)  2010 <>
 * 
 */

#include "node.h"
#include <math.h>
#include <QMap>
#include <iostream>

using namespace std;

Node::Node(int d, int v, int dist, const char * p)
{
	setPosition(0, 0);
	degree = d;
	velocity  = v;
	radius = dist;
  angle = 0;
  pixName = p;
  rotation = 0;
  timer = new QTimer(this);
  message = false;

  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(sendMessagesToNeighbour()));
  timer->start(1000);
}

void Node::sendMessage(Message* msg, Node* node)
{
  if(isNeighbour(node))
    node->messageArrived(msg);
}

void Node::messageArrived(Message* msg)
{
  msgQueue.push_back(msg);
}

Message* Node::createMessage(int msgLength, int priority)
{
  Message* msg = new Message(x,y,msgLength,priority);

  return msg;
}

void Node::sendMessagesToNeighbour()
{

}

void Node::addNeighbours(QList<Node*> list, bool bid, int attachment)
{
  bool swapped = true;
  int j = 0;

  switch(attachment)
  {
    case RANDOM_ATTACHMENT:
    {
    }
    break;

    case NEAREST_ATTACHMENT:
    {
      while (swapped)
      {
        swapped = false;
        j++;

        for (int i = 0; i < list.size() - j; i++)
        {
          if (getDistance(list.at(i)) > getDistance(list.at(i + 1)))
          {
            list.swap(i,i+1);
            swapped = true;
          }
        }
      }
    }
    break;

    case FARTHER_ATTACHMENT:
    {
      while (swapped)
      {
        swapped = false;
        j++;

        for (int i = 0; i < list.size() - j; i++)
        {
          if (getDistance(list.at(i)) < getDistance(list.at(i + 1)))
          {
            list.swap(i,i+1);
            swapped = true;
          }
        }
      }
    }
    break;

    case BEST_CONNECTED_ATTACHMENT:
    {
      while (swapped)
      {
        swapped = false;
        j++;

        for (int i = 0; i < list.size() - j; i++)
        {
          if (list.at(i)->getActiveConnections() < list.at(i + 1)->getActiveConnections())
          {
            list.swap(i,i+1);
            swapped = true;
          }
        }
      }
    }
    break;

    case HIGHER_DEGREE_ATTACHMENT:
    {
      while (swapped)
      {
        swapped = false;
        j++;

        for (int i = 0; i < list.size() - j; i++)
        {
          if (list.at(i)->getDegree() < list.at(i + 1)->getDegree())
          {
            list.swap(i,i+1);
            swapped = true;
          }
        }
      }
    }
    break;
  }

  foreach(Node* node, list)
  {
    if(neighbours.size()>=degree)
      break;

    if(!isNeighbour(node))
    {
      if(bid)
      {
        if(node->addNeighbour(this))
          addNeighbour(node);
      }
      else
        addNeighbour(node);
    }
  }
}

bool Node::addNeighbour(Node* node)
{
  if(neighbours.size()<degree && !neighbours.contains(node))
  {
    neighbours.append(node);
    return true;
  }

  return false;
}


void Node::validateNeighbours()
{
  foreach(Node* node, neighbours)
    if(!isInRange(node))
      neighbours.removeAll(node);
}

bool Node::isInRange(Node* n)
{
  int range = getRadius();
  if(range > n->getRadius())
      range = n->getRadius();

  return getDistance(n) <= range;
}

double Node::getDistance(Node* n)
{
  return sqrt(pow(n->getX()-getX(),2)+pow(n->getY()-getY(),2));
}

