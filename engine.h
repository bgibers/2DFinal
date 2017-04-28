#include <vector>
#include <SDL.h>
//#include "ioMod.h"
#include "renderContext.h"
//#include "clock.h"
#include "hud.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "multisprite.h"
#include "smartSprite.h"
#include "sound.h"

class CollisionStrategy;

class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
  void switchSprite();
  void checkForCollisions();
  int getDeathcnt() const {return deathCount;}

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;
  Hud& hud;
  SDLSound& sound;

  SDL_Renderer * const renderer;
  World mtns;
  World mid;
  World sand;
  Player player;
  Player sit;
  MultiSprite dad;
  SmartSprite follower;
  Viewport& viewport;
  

  std::vector<Drawable*> sprites;
  std::vector<Drawable*> wildabeasts;
  std::vector<Drawable*> playerSprites;
  std::vector<Drawable*> smartSprites;

  int currentSprite;
  bool makeVideo;
  CollisionStrategy* strategy;
  int deathCount;
  bool godMode;
  bool gameOver;

  void draw() const;
  void update(Uint32);
  void reset();

  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;
};
