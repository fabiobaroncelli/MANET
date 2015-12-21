#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <nodeitem.h>
#include <QList>
#include <stdio.h>
#include <math.h>

#include"streetwalkmodel.h"
#include"randomwalkmodel.h"

using namespace std;


class QGraphicsRectWidget : public QGraphicsWidget
{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *)
    {
        painter->fillRect(rect(), Qt::blue);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  manet = new Manet();
  timer = new QTimer;
  scene = NULL;
  grid = 5;
  walkModel = NULL;

  ui->StopButton->setEnabled(false);
  ui->HubDegreeBox->setValue(manet->getHubDegree());
  ui->HubStartBox->setValue(manet->getHubNumber());
  ui->HubVelocityBox->setValue(manet->getVelocityHub());
  ui->NodeDegreeBox->setValue(manet->getNodeDegree());
  ui->NodeStartBox->setValue(manet->getNodeNumber());
  ui->NodeRadiusBox->setValue(manet->getRadiusNode());
  ui->HubRadiusBox->setValue(manet->getRadiusHub());
  ui->NodeVelocityBox->setValue(manet->getVelocityNode());
  ui->DimensionBox->setValue(manet->getDimension());
  ui->BandwidthBox->setValue(manet->getBandwidth());
  ui->MaxDistanceBox->setValue(manet->getMaxDistance());
  ui->MaxHopBox->setValue(manet->getMaxHop());
  ui->MaxTimeBox->setValue(manet->getMaxTime());
  ui->MsgBERBox->setValue(manet->getMsgBER());
  ui->MsgLengthBox->setValue(manet->getMsgLength());
  ui->MsgSendProbabilityBox->setValue(manet->getMsgSendProbability());
  ui->GridBox->setValue(grid);

  ui->WalkModelBox->addItem("Random Walk");
  ui->WalkModelBox->addItem("Streets Walk");

  ui->LaplacianTypeBox->addItem("No Calculation");
  ui->LaplacianTypeBox->addItem("Standard Laplacian");
  ui->LaplacianTypeBox->addItem("Unsigned Laplacian");
  ui->LaplacianTypeBox->addItem("Normalized Laplacian");
  ui->LaplacianTypeBox->addItem("Unsigned Normalized Laplacian");
  ui->LaplacianTypeBox->addItem("Adjacency Matrix");
  ui->LaplacianTypeBox->addItem("Normalized Adjacency Matrix");

  ui->AttachmentBox->addItem("Random attachment");
  ui->AttachmentBox->addItem("Nearest attachment");
  ui->AttachmentBox->addItem("Furthest attachment");
  ui->AttachmentBox->addItem("Best connected attachment");
  ui->AttachmentBox->addItem("Higher degree attachment");

  array.clear();
  index=0;
  cp = 0;
  algorithm = NULL;
}

MainWindow::~MainWindow()
{
  delete ui;
  delete algorithm;
}

QString MainWindow::getEnergy(int p)
{
  QString energyString;
  double energy = 0;

  for(int i=0; i<array.size(); i++)
  {
    double x = (double)(array[i]/index);
    energy += pow(x,p);
  }

  energyString.setNum(energy);
  return energyString;
}

void MainWindow::writeReport()
{
  QString name("N" + QString::number(manet->getNodeNumber()) + "-" + QString::number(manet->getNodeDegree()) + "-" + QString::number(manet->getRadiusNode()));
  name.append("H" + QString::number(manet->getHubNumber()) + "-" + QString::number(manet->getHubNumber()) + "-" + QString::number(manet->getRadiusHub()) + "-");
  name.append("R" + QString::number(manet->getDimension()));
  if(ui->KeepBox->isChecked())
    name.append("-keep");
  else
    name.append("-noKeep");

  bool laplacianCalculation = true;

  if(ui->LaplacianTypeBox->currentIndex()==NO_CALCULATION)
    laplacianCalculation = false;

  if(laplacianCalculation)
  {
    QFile file1("Result/" + name + ".dat");
    file1.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file1);
    qSort(array.begin(), array.end());

    for(int i=0; i<array.size(); i++)
      out << (double)(array[i]/index) << endl;

    file1.close();
  }

  QMap<int, int> degreeDistribution = manet->getDegreeDistribution();

  QFile file2("Result/Report-" + name + ".dat");
  file2.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out2(&file2);

  out2 << "Connectivity probability" << endl;
  out2 << "------------------------ " << endl;
  out2 << cp/index << endl;

  out2 << "Degree distribution " << endl;
  out2 << "------------------- " << endl;
  foreach (int key, degreeDistribution.keys())
    out2 << key << " - " << ((double)degreeDistribution[key])/index << endl;

  if(laplacianCalculation)
  {
    out2 << "Energy " << endl;
    out2 << "------ " << endl;
    out2 << "E1 = " << getEnergy(1) << endl;
    out2 << "E2 = " << getEnergy(2) << endl;
    out2 << "E3 = " << getEnergy(3) << endl;
  }

  file2.close();

  if(ui->LaplacianTypeBox->currentIndex() == NORMALIZED_ADJACENCY_MATRIX)
  {
    MatrixXd adj = manet->adjacencyMatrix;
    QFile file3("Result/Adjacency-" + name + ".dat");
    file3.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out3(&file3);

    for(int x=0; x<adj.rows(); x++)
    {
      for(int y=0; y<adj.cols(); y++)
        out3 << adj(x,y) << "\t";

      out3 << endl;
    }
    file3.close();
  }
}

void MainWindow::startSimulation()
{
  cout << "START" << endl;

  ui->StartButton->setEnabled(false);
  ui->StopButton->setEnabled(true);
  ui->ProgressBar->setValue(0);
  ui->ReportBox->clear();

  manet = new Manet();
  manet->setHubDegree(ui->HubDegreeBox->value());
  manet->setHubNumber(ui->HubStartBox->value());
  manet->setNodeNumber(ui->NodeStartBox->value());
  manet->setVelocityHub(ui->HubVelocityBox->value());
  manet->setRadiusHub(ui->HubRadiusBox->value());
  manet->setDimension(ui->DimensionBox->value());
  manet->setNodeDegree(ui->NodeDegreeBox->value());
  manet->setVelocityNode(ui->NodeVelocityBox->value());
  manet->setLaplacianType(ui->LaplacianTypeBox->currentIndex());
  manet->setAttachmentType(ui->AttachmentBox->currentIndex());
  manet->setBidirectional(ui->BidirectionalBox->isChecked());
  manet->setKeep(ui->KeepBox->isChecked());
  manet->setBandwidth(ui->BandwidthBox->value());
  manet->setMaxDistance(ui->MaxDistanceBox->value());
  manet->setMaxHop(ui->MaxHopBox->value());
  manet->setMaxTime(ui->MaxTimeBox->value());
  manet->setMsgBER(ui->MsgBERBox->value());
  manet->setMsgLength(ui->MsgLengthBox->value());
  manet->setMsgSendProbability(ui->MsgSendProbabilityBox->value());

  timer = new QTimer;
  scene = ui->graphicsView->scene();

  if(scene == NULL)
  {
    scene = new QGraphicsScene(0, 0, manet->getDimension(), manet->getDimension());
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
  }

  scene->setSceneRect(0, 0, manet->getDimension(), manet->getDimension());

  array.clear();
  index=0;
  cp = 0;
  step = 50;
  totalSteps = step*ui->TimeBox->value();
  manet->start();
  int wm = ui->WalkModelBox->currentIndex();

  if(walkModel != NULL)
  {
    delete walkModel;
  }

  if(wm == 0)
    walkModel = new RandomWalkModel(manet->getNodes(), manet->getDimension(), true);
  else if(wm == 1)
    walkModel = new StreetWalkModel(ui->GridBox->value(), scene, manet->getNodes(), manet->getDimension());

  if(algorithm != NULL)
  {
    delete algorithm;
  }

  //algorithm = new Algorithm(ANTILAPLACIAN_NORMALIZED_ALGORITHM);
  algorithm = new Algorithm(RANDOM_ALGORITHM);

  foreach(Node* node, manet->getNodes())
  {
    NodeItem* nodeItem = new NodeItem(node, new QPixmap(node->getPixName()));
    nodeItem->setPos(node->getX(),node->getY());
    scene->addItem(nodeItem);
    algorithm->addNodeItem(nodeItem);
  }

  QObject::connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
  timer->start(1000 / step);

  algorithmTimer = new QTimer;
  QObject::connect(algorithmTimer, SIGNAL(timeout()), algorithm, SLOT(advance()));
  algorithmTimer->start(50);
}

void MainWindow::advance()
{
  walkModel->advance();

  if(ui->AnimationBox->isChecked())
    scene->advance();

  cp += manet->calculate(array);
  MatrixXd ev = manet->getEigenVectors();
  ui->ProgressBar->setValue(1+(int)(index*100/totalSteps));
  index++;

  if(index>=totalSteps)
  {
    writeReport();
    stopSimulation();
  }
}

void MainWindow::snapShot()
{
  if(ui->LaplacianTypeBox->currentIndex()==NO_CALCULATION)
    return;

  QString title(QTime::currentTime().toString().replace(QString(":"), QString("-")));
  QFile file("Result/" + title + ".dat");
  file.open(QIODevice::WriteOnly | QIODevice::Text);
  QTextStream out(&file);

  QList<double> eigen = manet->getEigenvalues();
  foreach(double val, eigen)
    out << val << endl;

  file.close();

  if(ui->LaplacianTypeBox->currentIndex()!=NO_CALCULATION)
  {
    QFile file2("Result/E-" + title + ".dat");
    file2.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out2(&file2);

    MatrixXd ev = manet->getEigenVectors();

    for(int x=0; x<ev.rows(); x++)
    {
      for(int y=0; y<ev.cols(); y++)
       out2 << ev.coeff(x,y) << "\t\t\t";

      out2 << endl;
    }

    file2.close();
  }
}

void MainWindow::stopSimulation()
{
  ui->StartButton->setEnabled(true);
  ui->StopButton->setEnabled(false);

  if(timer != NULL)
  {
    timer->stop();
    delete timer;
  }
  timer = NULL;

  if(algorithmTimer != NULL)
  {
    algorithmTimer->stop();
    delete algorithmTimer;
  }
  algorithmTimer = NULL;


  if(scene != NULL)
    delete scene;

  scene = NULL;
  manet->reset();
  index=0;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
