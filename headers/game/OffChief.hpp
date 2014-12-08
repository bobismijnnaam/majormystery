// File: OffChief.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef OFFCHIEF_HPP
#define OFFCHIEF_HPP

// Public
#include <deque>
#include <SDL2/SDL.h>
#include <math.h>
#include <string>

// Private
#include "nnb/graphics/TextureContainer.hpp"
#include "main/global.hpp"

int const BULLET_W = 18;
int const BULLET_H = 8;
int const BULLET_SPD = 500;
int const MAJOR_WALKSPEED = 90; // Units per second
int const MAJOR_LEGTIME = 1800;

class OffChief {
public:
	OffChief();
	~OffChief();

	void pushAction(std::string action);
	void logic(SDL_Rect view);
	void render() const;
	bool isInFrame(SDL_Rect view);
	bool isWearableInFrame(SDL_Rect view);
	std::string getWearable();
	bool isFinished();

private:
	std::deque<std::string> actions;
	std::string currentAction = "";
	bool finished = false;

	std::string actionType = "";
	int actionStart = 0;
	int actionDuration = 0;
	int lookDir = 1;
	std::string wearing = "";

	SDL_Point currPos;
	SDL_Point targetPos;

	nnb::TextureContainer torso;
	nnb::TextureContainer leg[2];
	
	nnb::TextureContainer dropped;
	SDL_Point droppedPos;

	nnb::TextureContainer wearable;
	SDL_Point wearingOffset;

	SDL_Rect currentView;

	std::vector<std::tuple<int, SDL_Point, int>> bullets;
} ;

#endif
