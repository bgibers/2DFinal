#include <cmath>
#include "gamedata.h"
#include "player.h"



Player::Player(const std::string& name) : TwoWaySprite(name), 
intitialVelocity(getVelocity()), 
slowDown(Gamedata::getInstance().getXmlFloat(name+"/slowDown")),
bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
bullets( bulletName ){}//, clock(Clock::getInstance()){}

Player::Player(const std::string& name, const std::string& name2) : TwoWaySprite(name, name2), 
intitialVelocity(getVelocity()), 
slowDown(Gamedata::getInstance().getXmlFloat(name+"/slowDown")),sitStatus(true),
bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
bullets( bulletName ){}

Player::Player(const Player& p) :
TwoWaySprite(p), 
intitialVelocity(p.intitialVelocity), slowDown(p.slowDown),bulletName(p.bulletName),
bullets(p.bullets) {}

void Player::shoot() { 
  float x = getX()+getFrame()->getWidth();
  float y = getY()+getFrame()->getHeight()/2;
  // I'm not adding minSpeed to y velocity:
  bullets.shoot( Vector2f(x, y), 
    Vector2f(100+getVelocityX(), 0)
  );
}

bool Player::b_collidedWith(const Drawable* obj) const {
  return bullets.collidedWith( obj );
}

void Player::bulletDraw() const { //add to engine where draw is
  bullets.draw();
}

void Player::stop()
{
	setVelocityX(slowDown * getVelocityX());
	setVelocityY(0);
  //make sprite sheet swap
   frames = TwoWaySprite::change;

}

void Player::right()
{
	if(getX() < worldWidth-frameWidth)
	{
		setVelocityX(-intitialVelocity[0]);
	}

   // sitStatus=false;
    frames = TwoWaySprite::initial;
	timeToFlip = false;
}


void Player::left()
{
  
	if(getX() > 0)
	{
		setVelocityX(intitialVelocity[0]);
	}
    // sitStatus=false;
    frames = TwoWaySprite::initial;

	timeToFlip = true;
}

void Player::up()
{  
	//make a jump perhaps
}

void Player::down()
{
	//tbt
}

void Player::update(Uint32 ticks)
{

	advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-frameHeight) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() <= 0) {
    setVelocityX( fabs( getVelocityX() ) );
    timeToFlip=false;
    //std::cout << "should flip back" << std::endl;
  }
  if ( getX() >= worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
    timeToFlip=true;
      //std::cout << "should flip" << std::endl;

  } 
  bullets.update(ticks);
  //stop();
}