// File: RendererManager.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef RENDERERMANAGER_HPP
#define RENDERERMANAGER_HPP

// Public
#include "SDL2/SDL.h"
#include <memory>

// Private
#include "nnb/resources/CustomDeleters.hpp"
#include "nnb/graphics/TextureContainer.hpp"
#include "nnb/graphics/Text.hpp"
#include "game/Shutter.hpp"

class RendererManager {
public:
	RendererManager();
	~RendererManager();

	void switchTarget(int x, int y);
	void setDefault();
	void propose();
	void logic();
	void publish();

private:
	std::unique_ptr<SDL_Texture, nnb::SDLDeleter> views[4];
	nnb::TextureContainer viewContainers[4];
	
	Shutter shutters[4];

	int currentView = 0;
	SDL_Point nextView = {-1, -1};
} ;

#endif
