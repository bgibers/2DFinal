#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include "twoWaysprite.h"
#include "sprite.h"
#include "bulletPool.h"
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
	void bulletDraw() const; //draw bullets
	void shoot(); //shoot bullets
	bool b_collidedWith(const Drawable*) const;//for collisions with bullets
	protected:
		Vector2f intitialVelocity;
		const float slowDown;

	private:
		bool sitStatus;
		std::string bulletName;
		BulletPool bullets;
		
};

#endif