// File: Shutter.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef SHUTTER_HPP
#define SHUTTER_HPP

// Public
#include <SDL2/SDL.h>

// Private
#include "nnb/graphics/TextureContainer.hpp"

enum class ShutterState {
	OPEN,
	OPENING,
	CLOSING,
	CLOSED,
	CLOSEAFTER,
	OPENAFTER
} ;

class Shutter {
public:
	Shutter(int slideTime_ = 340);
	~Shutter();

	void open();
	void close();
	void blinkOpen();
	void blinkClose();
	void logic();
	void render() const;

private:
	int stateTimer;
	ShutterState state;
	SDL_Point pos;
	int slideTime;
	nnb::TextureContainer shuts[6];
} ;

#endif
