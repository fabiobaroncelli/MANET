/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * manet
 * Copyright (C)  2010 <>
 * 
 * manet is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * manet is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MOBILENODE_H_
#define _MOBILENODE_H_

#include<QList>
#include"message.h"
#include<QTimer>
#include<QQueue>

#define RANDOM_ATTACHMENT 0
#define NEAREST_ATTACHMENT 1
#define FARTHER_ATTACHMENT 2
#define BEST_CONNECTED_ATTACHMENT 3
#define HIGHER_DEGREE_ATTACHMENT 4

class Node : public QObject
{
  Q_OBJECT

	public:
    Node(int, int, int, const char *);
    int getX() const {return x;}
    int getY() const {return y;}
    double getAngle() const {return angle;}
    int getVelocity() const {return velocity;}
    void setPosition(int x1, int y1) {x = x1; y = y1;}
    int getDegree() const {return degree;}
    int getRadius() const {return radius;}
    void resetNeighbours(){neighbours.clear();}
    void addNeighbours(QList<Node*>, bool, int);
    bool isNeighbour(Node* n){return neighbours.contains(n);}
    QList<Node*> getNeighbours(){return neighbours;}
    const char* getPixName() const {return pixName;}
    void setAngle(double a){angle = a;}
    bool isInRange(Node*);
    void validateNeighbours();
    bool addNeighbour(Node*);
    bool operator <(Node*);
    double getDistance(Node*);
    int getActiveConnections(){return neighbours.size();}

    void setMsgSendProbability(double p){msgSendProbability = p;}
    void setMsgLength(int l){msgLength = l;}
    void setMsgBER(int b){msgBER = b;}
    void setBandwidht(double b){bandwidht=b;}
    int getRotation(){return rotation;}
    void setRotation(int r){rotation = r;}

    void setScore(double s) {score=s;}
    double getScore(){return score;}
    void setMsg(bool m) {message=m;}
    bool getMsg(){return message;}
    void setMedia(double m) {media=m;}
    double getMedia(){return media;}

	protected:
		int degree;
		int x;
		int y;
		int velocity;
		int radius;
    int rotation;
    double angle;
    QList<Node*> neighbours;
    const char * pixName;
    QTimer *timer;
    QQueue<Message*> msgQueue;
    void sendMessage(Message*, Node*);
    Message* createMessage(int,int);
    void messageArrived(Message*);

    double msgSendProbability;
    int msgLength;
    int msgBER;
    double bandwidht;
    double score;
    bool message;
    double media;

  private slots:
    void sendMessagesToNeighbour();
};

#endif // _MOBILENODE_H_
