// File: gsSettings.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GSSETTINGS_HPP
#define GSSETTINGS_HPP

// Public

// Private
#include "nnb/states/GameState.hpp"
#include "nnb/graphics/Text.hpp"
#include "nnb/graphics/TextureContainer.hpp"
#include "nnb/utils/SDL_Helpers.hpp"

class gsSettings : public nnb::GameState {
public:
	gsSettings();
	~gsSettings();

	void event(SDL_Event& e);
	void logic(float delta);
	void render() const;

private:

	nnb::TextureContainer bg;
	nnb::Text btn;

	SDL_Rect backZone, backUnderline;
	bool backHover = false;

} ;

#endif
