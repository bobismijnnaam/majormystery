// Author: Bob Rubbens - Knights of the Compiler
// Creation date: za 26-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef BEGINSLOPETILE_HPP
#define BEGINSLOPETILE_HPP

// Public
#include <SDL2/SDL.h>

// Private
#include "world/Camera.hpp"
#include "world/tile.hpp"

class BeginSlopeTile : public SlopedTile {
public:
	BeginSlopeTile();
	BeginSlopeTile(int slopeOrder);

	void debugRender(SDL_Renderer *tgt, int x, int y, Camera const &cam) const;
	void setIndex(int slopeIndex) {}

private:

};

#endif