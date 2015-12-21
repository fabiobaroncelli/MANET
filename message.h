#ifndef MESSAGE_H
#define MESSAGE_H

#include <QTime>

class Message
{
  public:
    Message(int, int, int, int);
    int getX(){return x;}
    int getY(){return y;}
    int getLength(){return length;}
    int getPriority(){return priority;}

  private:
    int priority;
    int length;
    int x;
    int y;
    int hop;
    QTime time;


};

#endif // MESSAGE_H
