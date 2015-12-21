#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "manet.h"
#include <QSpinBox>
#include <QGraphicsWidget>
#include <QtGui>
#include <Eigen/Dense>
#include "walkmodel.h"
#include "algorithm.h"

namespace Ui {
    class MainWindow;
}

class PixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    PixmapItem(const QPixmap * pix) : QGraphicsPixmapItem(*pix)
    {
    }
};

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene* scene;

protected:
    void changeEvent(QEvent *e);

private slots:
  void startSimulation();
  void stopSimulation();
  void snapShot();
  void advance();

  void setHubDegree(int d){manet->setHubDegree(d);}
  void setHubNumber(int d){manet->setHubNumber(d);}
  void setVelocityHub(int s){manet->setVelocityHub(s);}
  void setVelocityNode(int s){manet->setVelocityNode(s);}
  void setNodeDegree(int d){manet->setNodeDegree(d);}
  void setNodeNumber(int d){manet->setNodeNumber(d);}

private:
    Ui::MainWindow *ui;
    Manet* manet;
    QTimer* timer;
    QTimer* algorithmTimer;
    QList<double> array;
    int index;
    int step, totalSteps;
    double cp;
    void writeReport();
    QString getEnergy(int);
    WalkModel* walkModel;
    int grid;
    Algorithm* algorithm;
};

#endif // MAINWINDOW_H
