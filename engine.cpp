#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include "sprite.h"
#include "twoWaysprite.h"
#include "scaledSprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
//#include "collisionStrategy.h"

class SpriteCompare{
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const{
    return (lhs->getScale() < rhs->getScale());
  }
};

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
 for( auto&& items : sprites) {delete items;}
 for( auto&& items : wildabeasts) {delete items;}
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  hud( Hud::getInstance()),
  renderer( rc->getRenderer() ),
  mtns("mtns", Gamedata::getInstance().getXmlInt("mtns/factor") ),
  mid("mid", Gamedata::getInstance().getXmlInt("mid/factor") ),
  sand("sand", Gamedata::getInstance().getXmlInt("sand/factor") ),
  player("simba","simbaSit"),
  sit("simbaSit"),
  dad("dad"),
  viewport( Viewport::getInstance() ),
  sprites(),
  wildabeasts(),
  playerSprites(),
  currentSprite(-1),

  makeVideo( false ),
  strategy( new RectangularCollisionStrategy ), //here
  collisions(0)
{
  constexpr float u = 0.8f;//mean
  constexpr float d = 0.4f;//std

  std::random_device rd;
  std::mt19937 mt(rd());
  std::normal_distribution<float> dist(u,d);

  unsigned int n = Gamedata::getInstance().getXmlInt("numberOfStars");
  for(unsigned int i=0; i<n; ++i)
  {
    auto* s = new ScaledSprite("Bat");
    float scale = dist(mt);
    while(scale < 0.1f) scale=dist(mt);
    s->setScale(scale);
    sprites.push_back(s);
  }

  
  sort(sprites.begin(), sprites.end(), SpriteCompare());
  for(Drawable* sprite : sprites)
  {
    ScaledSprite* thisone = dynamic_cast<ScaledSprite*>(sprite);
    if(thisone)
    {
      std::cout << thisone->getScale() << std::endl;
    }
  }

  wildabeasts.push_back(new TwoWaySprite("wildabeast"));

  
  playerSprites.push_back(&player);
  viewport.setObjectToTrack(&player);
  //switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  mtns.draw();
  for(unsigned int i = 0; i < sprites.size()/1.5; ++i)
  {
    sprites[i]->draw();
  }
  mid.draw();
  for(unsigned int i = sprites.size()/1.5; i < sprites.size(); ++i)
  {
    sprites[i]->draw();
  }
  sand.draw();
  playerSprites[0]->draw();
  player.bulletDraw();
  for(auto w : wildabeasts)
  {
    w->draw();
  }
  dad.draw();

  SDL_Color red ={255,0,0,0};


  // std::stringstream strm;
  // strm << "fps: " << clock.getFps();
  // io.writeText(strm.str(), 30, 60);

  std::stringstream strm1;
  // strm1 << "avg fps: " << clock.getAvgFps();
  // io.writeText(strm1.str(), 30, 90);
  io.writeText(Gamedata::getInstance().getXmlStr("screenTitle"),30,440,red);

  //for(auto* s : sprites) s->draw();
  hud.draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);

  playerSprites[0]->update(ticks);

  mtns.update();
  mid.update();
  sand.update();
  dad.update(ticks);
  for(auto w : wildabeasts)
  {
    w->update(ticks);
  }
  // if(playerSprites[0]->getStatus() == true)
  // {
  //     playerSprites[0]->update(ticks);
  // }
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  //currentSprite = ++currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::checkForCollisions() {
  std::vector<Drawable*>::iterator it = wildabeasts.begin();

  Drawable* playerptr = playerSprites[0]; //should put player in sprite
  while ( it != wildabeasts.end() ) {
    //if ( strategy->execute(*player, **it) ) {
    if(player.collidedWith(*it)){
      // delete *it;
      //ExplodingSprite* p = dynamic_cast<ExplodingSprite*>(*it);
      const Sprite s(**it,(*it)->getFrame());
      Drawable* boom = new ExplodingSprite(s);
      it = wildabeasts.erase(it);
      it = wildabeasts.insert(it,boom);

      //this should be permenantly deleting
      if(static_cast<ExplodingSprite*>(boom)->chunkCount() == 0) it = wildabeasts.erase(it);
      ++collisions;
    }
    else ++it;
  }


}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }

        if( keystate[SDL_SCANCODE_R]){
            //reset here something w chunk
            wildabeasts[0] = new TwoWaySprite("wildabeast");
        }

       if (keystate[SDL_SCANCODE_F1] && hud.getDisplay() == true) {
          hud.setDisplay(false);
        }

        else if (keystate[SDL_SCANCODE_F1] && hud.getDisplay() == false) {
          hud.setDisplay(true);
        }

        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    if ( (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D]) ||
        (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D]))
    {
       player.stop();   
   		
    }

    else if (keystate[SDL_SCANCODE_A])
    {
      player.left();
      //playerSprites[0]->update(ticks);
    }

    else if (keystate[SDL_SCANCODE_D])
    {
      player.right();
      //playerSprites[0]->update(ticks);

    }
  

    if ( keystate[SDL_SCANCODE_W]  && keystate[SDL_SCANCODE_S])
    {
      player.stop();
      //player.update(ticks);
    }

      if ( keystate[SDL_SCANCODE_SPACE]){
        player.shoot();
      }

 // else if (keystate[SDL_SCANCODE_W])
 //    {
 //      //go up
 //    }

 //    else if (keystate[SDL_SCANCODE_S])
 //    {
 //      //go down
 //    }
    
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      checkForCollisions();
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
