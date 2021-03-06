#include "hud.h"
#include <sstream>

Hud& Hud::getInstance() {
  static Hud instance;
  return instance;
}

Hud::Hud() : display(true), godmode(false), width(Gamedata::getInstance().getXmlInt("hud/width")),
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
  SDL_Color red ={255,0,0,0};

  std::stringstream strm,strm1, strm2, strm3, strm4;

  strm  << "LION KING";
  strm1 << "Run to Simbas dad!";
  strm2 << "You have 3 lives";
  strm3 << "A&D-walk SPACE-shoot G-godmode";
  strm4 << "R to restart P to pause F1 to hide HUD";
  
  ioMod.writeText(strm.str(),position[0]+20, position[1],red);
  ioMod.writeText(strm1.str(),position[0]+20, position[1]+22,yellow);
  ioMod.writeText(strm2.str(),position[0]+20, position[1]+52,yellow);
  ioMod.writeText(strm3.str(),position[0]+20, position[1]+82,yellow);
  ioMod.writeText(strm4.str(),position[0]+20, position[1]+112,yellow);
}
	if(godmode == true)
	{
		 SDL_Color red ={255,0,0,0};
         std::stringstream strm;
         strm << "GODMODE ON";
         ioMod.writeText(strm.str(),650,100,red);
	}

  if(gameOver == true)
  {
     SDL_Color red ={255,0,0,0};
         std::stringstream strm;
         strm << "You win! Press R to restart";
         ioMod.writeText(strm.str(),300,250,red);
  }
 	
 	return;
 }
