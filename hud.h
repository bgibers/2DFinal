#ifndef HUD_H
#define HUD_H
#include <SDL.h>
#include "clock.h"
#include "ioMod.h"
#include "viewport.h"



class Hud
{
public:
	static Hud& getInstance();
	void draw() const;
	bool getDisplay() const{return display;}
	void setDisplay(bool set) {display = set;}
	void setGodmode(bool set) {godmode = set;}
	void setGameover(bool set) {gameOver = set;}

private:
	Hud();
	Hud(const Hud&);
	Hud& operator=(const Hud&);

	bool display;
	bool godmode;
	bool gameOver;
	unsigned int width;
	unsigned int height;

	Vector2f position;
	IOmod& ioMod;
	Viewport& viewport;
	Clock& clock;

};
#endif