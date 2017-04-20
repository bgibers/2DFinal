#include "hud.h"
#include <sstream>

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}

Hud::Hud() : display(true), width(Gamedata::getInstance().getXmlInt("hud/width")),
height(Gamedata::getInstance().getXmlInt("hud/height")),
position(Gamedata::getInstance().getXmlInt("hud/xCoord"),Gamedata::getInstance().getXmlInt("hud/yCoord")),
ioMod(IOmod::getInstance()), viewport(Viewport::getInstance()), 
clock(Clock::getInstance()) {}

void Hud::draw() const
{
	if(display == true)
	{	
	SDL_Rect rect;
	rect.x = position[0];
	rect.y = position[1];
	rect.w = width;
	rect.h = height;

	SDL_Renderer* renderer = ioMod.getRenderer();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255/2 );
	SDL_RenderFillRect( renderer, &rect );
 	SDL_SetRenderDrawColor( renderer, 208, 209, 210, 255 );
 	SDL_RenderDrawRect( renderer, &rect);

  SDL_Color yellow = {153,153,0,0}; 

  std::stringstream strm1, strm2, strm3;


  strm1 << "fps: " << clock.getFps();
  strm2 << "AVG FPS: " << clock.getAvgFps();
  strm3 << "A and D to walk F1 to hide HUD";
  
  ioMod.writeText(strm1.str(),position[0]+20, position[1]+20,yellow);
  ioMod.writeText(strm2.str(),position[0]+20, position[1]+50,yellow);
  ioMod.writeText(strm3.str(),position[0]+20, position[1]+80,yellow);
}
 	return;
 }
