#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsPixmapItem>
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const double Pi = 3.14159265358979323846264338327950288419717;

class NodeItem : public QObject, public QGraphicsPixmapItem
{
  Q_OBJECT
  Q_PROPERTY(QPointF pos READ pos WRITE setPos)

  public :

  NodeItem(Node* n, const QPixmap* pix) : QGraphicsPixmapItem(*pix)
  {
    node = n;
    height = pix->height();
    width = pix->width();
  }

  void advance(int)
  {
    setPos(node->getX()-width/2,node->getY()-height/2);
  }

  Node* getNode() {return node;}

private :
    Node* node;
    int height, width;
};

#endif // NODEITEM_H
