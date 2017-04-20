#include <cmath>
#include <random>
#include "scaledsprite.h"
#include "gamedata.h"
#include "renderContext.h"


const float PI = 4.0f*std::atan(1.0f);

using RADRAND_t = decltype(std::bind(std::declval<std::uniform_real_distribution<float> >(),std::declval<std::mt19937>()));
using NORRAND_t = decltype(std::bind(std::declval<std::normal_distribution<float> >(),std::declval<std::mt19937>()));

std::mt19937 getRand(){
  static std::random_device rd;
  return std::mt19937(rd());
}

RADRAND_t getRadianDist(){
  return std::bind(std::uniform_real_distribution<float>(0.0f,2.0f*PI),getRand());
}

NORRAND_t getNormalDist(float u, float dev){
  return std::bind(std::normal_distribution<float>(u,dev),getRand());
}

// Vector2f ScaledSprite::makeVelocity(int vx, int vy) const {
//   static auto rad = getRadianDist();
//   auto nor = getNormalDist(vx,vy);

//   float v_rad = rad();
//   float v_mag = nor();

//   return v_mag*Vector2f(std::cos(v_rad)/3,std::sin(v_rad)/3);
// }

Vector2f ScaledSprite::makeVelocity(int vx, int vy) const {
  float a = Gamedata::getInstance().getRandInRange(vx-50, vx+50);
  float b = Gamedata::getInstance().getRandInRange(vy-50, vy+50);

  a = a * (rand()%2 ?1:1);
  b = b * (rand()%2 ?-1:1);

  vx += a;
  vy += b;

  return Vector2f(a,b);
}

void ScaledSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

ScaledSprite::ScaledSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(randomStart(), 
                    randomStart()), 
           makeVelocity(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  scale(1),
  timeToFlip(false)
{ }

ScaledSprite::ScaledSprite(const ScaledSprite& s) :
  Drawable(s), 
  frames(s.frames),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  scale(s.scale),
  timeToFlip(s.timeToFlip)

  { }

inline namespace{
  constexpr float SCALE_EPSILON = 2e-7;
}

void ScaledSprite::draw() const { 
  if(getScale() < SCALE_EPSILON) return;
  int lol = 0;
  frames[currentFrame]->draw(getX(), getY(),scale,timeToFlip,lol);
}

int ScaledSprite::randomStart() const
{
  int rn = rand()%(1000 - 20 + 1) + 20;
  return rn;
}
void ScaledSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
        timeToFlip=false;

    //std::cout << "should flip back" << std::endl;
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
        timeToFlip=true;

     // std::cout << "should flip" << std::endl;

  }  

}
