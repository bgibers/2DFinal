#include <cmath>
#include "viewport.h"
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

SmartSprite::SmartSprite(const std::string& name, const std::string& name2, Player* p) :
 TwoWaySprite(name,name2),
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

void SmartSprite::changeFrame(bool switcher){if(switcher){frames = TwoWaySprite::change;}else frames = TwoWaySprite::initial;}

void SmartSprite::update(Uint32 ticks) {
  TwoWaySprite::update(ticks);

   Vector2f vel = player->getVelocity();
   setVelocityX(vel[0]);
   setVelocityY(vel[1]);


  if ( player->getFlip() == true) goLeft();
  if ( player->getFlip() == false ) goRight();

  if(player->getDead() == true) changeFrame(true);
  if(player->getDead() == false) changeFrame(false);


}

