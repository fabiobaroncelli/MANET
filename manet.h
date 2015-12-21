#ifndef _MANET_H_
#define _MANET_H_

#include <Eigen/Dense>
#include "node.h"
#include <QMap>
#include <QList>

#define NO_CALCULATION 0
#define STANDARD_LAPLACIAN 1
#define SIGNLESS_LAPLACIAN 2
#define NORMALIZED_LAPLACIAN 3
#define SIGNLESS_NORMALIZED_LAPLACIAN 4
#define ADJACENCY_MATRIX 5
#define NORMALIZED_ADJACENCY_MATRIX 6

using Eigen::MatrixXd;
using Eigen::VectorXd;

bool XlessThan(const Node*, const Node*);
void BubbleSort(long double num[], int);

class Manet
{
	public :

    Manet();
    ~Manet();
    void start();
    Node* addNode();
    Node* addHub();
    void setHubDegree(int d){hubDegree = d;}
    void setNodeDegree(int n){nodeDegree = n;}
    void setNodeNumber(int s){nodeNumber = s;}
    void setHubNumber(int s){hubNumber = s;}
    void setVelocityHub(int s){velocityHub = s;}
    void setVelocityNode(int s){velocityNode = s;}
    void setRadiusHub(int s){radiusHub = s;}
    void setRadiusNode(int s){radiusNode = s;}
    void setDimension(int d){dim = d;}
    void setBidirectional(bool b){bid = b;}
    void setKeep(bool k){keep = k;}
    void setLaplacianType(int l){laplacianType = l;}
    void setAttachmentType(int t){attachmentType = t;}
    void setMsgSendProbability(double p){msgSendProbability = p;}
    void setMsgBER(int b){msgBER = b;}
    void setBandwidth(double b){bandwidth = b;}
    void setMsgLength(int l){msgLength = l;}
    void setMaxHop(int h){msgMaxHop = h;}
    void setMaxTime(double h){msgMaxTime = h;}
    void setMaxDistance(int h){msgMaxDistance = h;}

    int getHubNumber(){return hubNumber;}
    int getNodeNumber(){return nodeNumber;}
    int getDimension(){return dim;}
    int getVelocityHub(){return velocityHub;}
    int getVelocityNode(){return velocityNode;}
    int getRadiusHub(){return radiusHub;}
    int getRadiusNode(){return radiusNode;}
    int getHubDegree(){return hubDegree;}
    int getNodeDegree(){return nodeDegree;}
    double getMsgSendProbability(){return msgSendProbability;}
    int getMsgBER(){return msgBER;}
    double getBandwidth(){return bandwidth;}
    int getMsgLength(){return msgLength;}
    int getMaxHop(){return msgMaxHop;}
    double getMaxTime(){return msgMaxTime;}
    int getMaxDistance(){return msgMaxDistance;}

    QList<Node*> getNodes(){return nodeVectorX;}
    void report();
    void reset();
    double calculate(QList<double>&);
    QMap<int, int> getDegreeDistribution(){return degreeDistribution;}

    QList<double> getEigenvalues();
    MatrixXd getLaplacian(bool);
    MatrixXd getNormalizedLaplacian(bool);
    MatrixXd getEigenVectors(){return eigenVectors;}
    MatrixXd getAdjacencyMatrix(bool);
    MatrixXd adjacencyMatrix;

	private :

    int dim;
    int hubDegree;
    int nodeDegree;
    int nodeNumber;
    int hubNumber;
    int velocityHub;
    int velocityNode;
    int radiusHub;
    int radiusNode;
    QList<Node*> nodeVectorX;
    int laplacianType;
    bool keep, bid;
    int attachmentType;
    MatrixXd eigenVectors;

    bool firstAdjacencyMatrix;

    double msgSendProbability ;
    int msgBER;
    int msgLength;
    double bandwidth;
    int msgMaxHop;
    double msgMaxTime;
    int msgMaxDistance;

    QList<Node*> getPotentialNeighbours(Node*);
    Node* addGenericNode(int,int,int,const char *);
    void writeMatrix(MatrixXd, QString);
    QList<QString*> eigenvalues;
    QMap<int,int> degreeDistribution;
    VectorXd powerMethod(MatrixXd a, int it_max);
    void norma(VectorXd & x);
    double energy(Node*);
};

#endif // _MANET_H_
