#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include <list>
#include <vector>

class CSnake : public CFramedWindow
{
private:
  enum Direction 
  { 
	  UP,
	  DOWN,
	  LEFT,
	  RIGHT
  };
  
  std::list<CPoint> body;
  CPoint food;
  Direction dir;
  bool paused;
  bool help;
  bool game_over;
  int level;
  int speed_counter;
  int points;

  void generateFood();
  void resetGame();
  void moveSnake();
  bool checkColision(CPoint p);

public:
  CSnake(CRect r, char _c = ' ');
  virtual void paint() override;
  virtual bool handleEvent(int key) override;
};

#endif
