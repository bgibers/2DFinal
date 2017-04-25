#include "twoWaysprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void TwoWaySprite::setFrames(const std::vector<Frame *> f)
{
   frames = f;
}

TwoWaySprite::TwoWaySprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
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
  timeToFlip(false)
{ }

TwoWaySprite::TwoWaySprite( const std::string& name, const std::string& change) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( RenderContext::getInstance()->getFrames(name) ),
  initial(RenderContext::getInstance()->getFrames(name) ),
  change(RenderContext::getInstance()->getFrames(change)),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  timeToFlip(false)
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
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
  timeToFlip(s.timeToFlip)
  { }

void TwoWaySprite::draw() const { 
  frames[currentFrame]->draw(getX(), getY(),timeToFlip);
}

/*Drawable* TwoWaySprite::blowUp()
{
    Sprite s("wildabeast");
    s.setFrame(getFrame());
    s.setPosition(getPosition());
    Drawable* boom = 
            new ExplodingSprite(*static_cast<Sprite*>(&s));
            return boom;
}*/

void TwoWaySprite::update(Uint32 ticks) { 
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
   // std::cout << "should flip back" << std::endl;
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
    timeToFlip=true;
     // std::cout << "should flip" << std::endl;

  }  

}
