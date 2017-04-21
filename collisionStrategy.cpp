#include <vector>
#include <algorithm>
#include "ioMod.h"
#include "collisionStrategy.h"
#include "viewport.h"

void RectangularCollisionStrategy::draw() const {
  IOmod::
  getInstance().writeText("Strategy: Rectangular Collision", 320, 30);
}

bool RectangularCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {
  float left1 = obj1.getX();
  float left2 = obj2.getX();
  float right1 = left1+obj1.getFrame()->getWidth();
  float right2 = left2+obj2.getFrame()->getWidth();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  float top1 = obj1.getY();
  float top2 = obj2.getY();
  float bottom1 = top1+obj1.getFrame()->getHeight();
  float bottom2 = top2+obj2.getFrame()->getHeight();
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}


float MidPointCollisionStrategy::
distance(float x1, float y1, float x2, float y2) const {
  float x = x1-x2, y = y1-y2;
  return hypot(x, y);
}

void MidPointCollisionStrategy::draw() const {
  IOmod::
  getInstance().writeText("Strategy: Distance from Middle", 320, 30);
}

bool MidPointCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {
  int COLLISION_DISTANCE = 
    obj1.getFrame()->getWidth()/2 + obj2.getFrame()->getWidth()/2;
  float xobj1 = obj1.getX()+obj1.getFrame()->getWidth()/2;
  float yobj1 = obj1.getY()+obj1.getFrame()->getHeight()/2;
  float xobj2 = obj2.getX() + obj2.getFrame()->getWidth()/2;
  float yobj2 = obj2.getY() + obj2.getFrame()->getHeight()/2;
  return distance(xobj1, yobj1, xobj2, yobj2) < COLLISION_DISTANCE;
}

