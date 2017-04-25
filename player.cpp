#include <cmath>
#include "gamedata.h"
#include "player.h"



Player::Player(const std::string& name) : TwoWaySprite(name), 
intitialVelocity(getVelocity()), 
slowDown(Gamedata::getInstance().getXmlFloat(name+"/slowDown")){}//, clock(Clock::getInstance()){}

Player::Player(const std::string& name, const std::string& name2) : TwoWaySprite(name, name2), 
intitialVelocity(getVelocity()), 
slowDown(Gamedata::getInstance().getXmlFloat(name+"/slowDown")),sitStatus(true){}

Player::Player(const Player& p) :
TwoWaySprite(p), 
intitialVelocity(p.intitialVelocity), slowDown(p.slowDown)
// clock(Clock::getInstance()) {} 

{}

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
  //stop();
}