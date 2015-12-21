#include "message.h"

Message::Message(int xx, int yy, int l, int p = 0)
{
  x = xx;
  y = yy;
  length = l;
  time = QTime::currentTime();
  hop = 1;
  priority = p;
}
