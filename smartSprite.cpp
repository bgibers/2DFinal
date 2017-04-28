#include <cmath>
#include "viewport.h"
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

SmartSprite::SmartSprite(const std::string& name, Player* p) :
 TwoWaySprite(name),
 player(p) {
   Vector2f vel = p->getVelocity();
   setVelocityX(vel[0]);
   setVelocityY(vel[1]);
   setX(player->getX()-50);
 }

void SmartSprite::goLeft()  {
  //if (getX() > 0) setVelocityX( -fabs(getVelocityX()) );
  if(player->getFlip() == true) timeToFlip = true;
  setX(player->getX()+50);
}
void SmartSprite::goRight() { timeToFlip = false; setX(player->getX()-50);}



void SmartSprite::update(Uint32 ticks) {
  TwoWaySprite::update(ticks);

   Vector2f vel = player->getVelocity();
   setVelocityX(vel[0]);
   setVelocityY(vel[1]);

  if ( player->getFlip() == true) goLeft();
  if ( player->getFlip() == false ) goRight();



}

