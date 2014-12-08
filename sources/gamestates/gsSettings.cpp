// File: gsSettings.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "gamestates/gsSettings.hpp"
#include "main/global.hpp"

gsSettings::gsSettings() {
	g_rm->switchTarget(0, 1);

	bg = g_tm->getTexture("default", "instructions.png");
	btn = g_fm->getText("GentiumPlus-R.ttf", 35);
	btn.setColor(193, 193, 193);
	btn.setPosition(415, 28);
	btn.setText("BACK");

	backZone = {412, 426, 86, 29};
	backUnderline = {415, 70, 80, 5};
}

gsSettings::~gsSettings() {

}

void gsSettings::event(SDL_Event& e) {
	SDL_Point p;
	
	switch (e.type) {
		case SDL_QUIT:
			g_gm->exit();
			break;
		case SDL_MOUSEBUTTONUP:
			NNB_LOG << "Mouse button was pressed at (" << e.button.x << "; " << e.button.y << ")";
			break;
		case SDL_MOUSEBUTTONDOWN:
			p = {e.button.x, e.button.y};

			if (nnb::pointInRect(p, backZone)) {
				g_gm->changeState(nnb::StateAction::SET, "main");
			}
		case SDL_MOUSEMOTION:
			p = {e.motion.x, e.motion.y};

			if (nnb::pointInRect(p, backZone)) {
				backHover = true;
			} else {
				backHover = false;
			}
			break;
		default:
			break;
	}
}

void gsSettings::logic(float delta) {

}

void gsSettings::render() const {
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	bg.render();
	btn.render();

	SDL_SetRenderDrawColor(g_renderer, 193, 193, 193, 255);
	if (backHover) {
		SDL_RenderFillRect(g_renderer, &backUnderline);
	}

	g_rm->publish();
}
