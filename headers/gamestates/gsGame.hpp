// File: gsGame.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSGAME_HPP
#define GSGAME_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>

// Private
#include "nnb/states/GameState.hpp"
#include "nnb/graphics/Text.hpp"
#include "nnb/utils/FloatRect.hpp"
#include "game/Shutter.hpp"
#include "game/Battery.hpp"
#include "game/OffChief.hpp"

class gsGame : public nnb::GameState {
public:
	gsGame();
	~gsGame();
	void event(SDL_Event& e);
	void logic(float delta);
	void render() const;

private:
	Uint32 stateStart = 0;

	nnb::FloatRect view;

	nnb::TextureContainer hud;
	nnb::TextureContainer fog;
	nnb::TextureContainer fg;
	nnb::TextureContainer bg;

	nnb::Text viewInfo;

	Shutter shutter;
	Battery battery;
	OffChief chief;

	int returnTimer = -1;
	bool caught = false;
} ;

#endif
