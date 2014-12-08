// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <math.h>

// Private
#include "gamestates/gsMainMenu.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "nnb/utils/constants.hpp"
#include "nnb/utils/SDL_Helpers.hpp"
#include "nnb/utils/unique_ptr.hpp"
#include "game/RendererManager.hpp"

gsMainMenu::gsMainMenu() {
	stateStart = SDL_GetTicks();

	bg = g_tm->getTexture("default", "main.png");

	play = g_fm->getText("GentiumPlus-R.ttf", 50);
	play.setText("PLAY");
	play.setColor(193, 193, 193);
	play.setVAlign(nnb::VAlign::CENTER);
	play.setPosition(120, 340);

	help = g_fm->getText("GentiumPlus-R.ttf", 50);
	help.setText("HELP");
	help.setColor(193, 193, 193);
	help.setVAlign(nnb::VAlign::CENTER);
	help.setPosition(250, 340);

	spacer = g_tm->getTexture("default", "spacer.png");
	spacer.setPosition(232, 337);

	g_rm->switchTarget(0, 0);

	left = {121, 365, 105, 5};
	right = {250, 365, 105, 5};
	playZone = {117, 321, 116, 43};
	helpZone = {246, 322, 116, 43};

	/*
	for (int i = 0; i < 6; ++i) {
		shuts[i] = g_tm->getTexture("game", "60.png");
		shuts[i].setPosition(VIEW_W / 2, VIEW_H / 2);
	}
	*/
}

gsMainMenu::~gsMainMenu() {
	// RAII takes care of:
	// Label
}

void gsMainMenu::event(SDL_Event& e) {
	SDL_Point p;

	switch (e.type) {
		case SDL_QUIT:
			g_gm->exit();
			break;
		case SDL_MOUSEBUTTONUP:
			NNB_LOG << "Mouse button was pressed at (" << e.button.x << "; " << e.button.y << ")";
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_SPACE) {
				g_gm->changeState(nnb::StateAction::SET, "intro"); // intro
			}
			break;
		case SDL_MOUSEMOTION:
			p = {e.motion.x, e.motion.y};

			if (nnb::pointInRect(p, playZone)) {
				hoverPlay = true;
			} else {
				hoverPlay = false;
			}
			
			if (nnb::pointInRect(p, helpZone)) {
				hoverHelp = true;
			} else {
				hoverHelp = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			p = {e.button.x, e.button.y};

			if (nnb::pointInRect(p, playZone)) {
				g_gm->changeState(nnb::StateAction::SET, "intro");
			} else if (nnb::pointInRect(p, helpZone)) {
				g_gm->changeState(nnb::StateAction::SET, "settings");
			}
			break;
		default:
			break;
	}

}

void gsMainMenu::logic(float delta) {
	/*
	if (SDL_GetTicks() - stateStart > 2000) {
		stateStart = SDL_GetTicks();
	}

	float d = (SDL_GetTicks() - stateStart) / 2000.0;

	for (int i = 0; i < 6; ++i) {
		shuts[i].setRotation(i * 60 + 30);
		int alpha = i * 60 + 30;
		float sx = VIEW_W / 2 + cos((alpha - 60) * nnb::PI / 180) * d * 100;
		float sy = VIEW_H / 2 + sin((alpha - 60) * nnb::PI / 180) * d * 100;
		shuts[i].setPosition(sx, sy);
	}
	*/
}

void gsMainMenu::render() const {
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	bg.render();
	spacer.render();

	play.render();
	help.render();

	SDL_SetRenderDrawColor(g_renderer, 193, 193, 193, 255);
	if (hoverPlay) SDL_RenderFillRect(g_renderer, &left);
	if (hoverHelp) SDL_RenderFillRect(g_renderer, &right);

	// for (int i = 0; i < 6; ++i) shuts[i].render();

	g_rm->publish();
}
