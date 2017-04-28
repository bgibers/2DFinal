#ifndef TWOWAYSPRITE__H
#define TWOWAYSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "sprite.h"

class TwoWaySprite : public Drawable {
public:
  TwoWaySprite(const std::string&);
  TwoWaySprite(const std::string&, const std::string&);
  TwoWaySprite(const TwoWaySprite&);
  TwoWaySprite(const std::string&, const int);//added for random start

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  void setFrames(const std::vector<Frame *> f);
  //virtual Drawable* blowUp();
  virtual const std::vector<Frame *> allFrames() const {return frames;}
  int randomStart() const;
  void setFlip(bool f){timeToFlip = f;}
  bool getFlip(){return timeToFlip;}
protected:

   std::vector<Frame *> frames;
   const std::vector<Frame *> initial;
   const std::vector<Frame *> change;



  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
  bool timeToFlip;

  void advanceFrame(Uint32 ticks);
};
#endif
