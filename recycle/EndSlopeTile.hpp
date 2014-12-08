// Author: Bob Rubbens - Knights of the Compiler
// Creation date: za 26-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef ENDSLOPETILE_HPP
#define ENDSLOPETILE_HPP

// Public

// Private
#include "world/tile.hpp"

class EndSlopeTile : public SlopedTile {
public:
	EndSlopeTile();
	EndSlopeTile(int slopeOrder);

	void debugRender(SDL_Renderer *tgt, int x, int y, Camera const &cam) const;
	void setIndex(int slopeIndex) {}

private:

} ;

#endif