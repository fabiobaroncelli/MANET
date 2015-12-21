#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include <QList>
#include "nodeitem.h"

#define RANDOM_ALGORITHM 0
#define ANTILAPLACIAN_NORMALIZED_ALGORITHM 1

class Algorithm : public QObject
{
  Q_OBJECT

  public:
    Algorithm(int type);
    void addNodeItem(NodeItem* n) {nodeItems.append(n);}
    void removeNodeItems() {nodeItems.clear();}
    int getCicle(){return cicle;}
    double getPercentage(){return percentage;}

  private slots:
    void advance();

  private:
    int type;
    QList<NodeItem*> nodeItems;
    void randomAlgorithm();
    void antiLaplacianNormalizedAlgorithm();
    bool start;
    void setNodeMsg(NodeItem*);
    void setNodeMsg(Node*);
    double percentage;
    int cicle;
};

#endif // ALGORITHM_H
