#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "twoWaysprite.h"
#include "sprite.h"
//#include "clock.h"

class Player : public TwoWaySprite
{
public:
	Player();
	Player(const std::string&);
	Player(const std::string&, const std::string&);

	Player(const Player& p);



	virtual void update(Uint32 ticks);
	void stop();
	void left();
	void right();
	void up();
	void down();
	bool getStatus() {return sitStatus;}
	void setStatus(bool s) {sitStatus = s;}
	protected:
		Vector2f intitialVelocity;
		const float slowDown;

	private:
	//	Clock& clock;
		bool sitStatus;
};

#endif