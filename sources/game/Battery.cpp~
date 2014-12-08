// File: Battery.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <algorithm>

// Private
#include "game/Battery.hpp"
#include "main/global.hpp"

Battery::Battery() {
	powerbar = g_tm->getTexture("default", "powerbar.png");
	powerbar.setPosition(18, 102);
	powerbar.setAlpha(100);

	power = 0;
	lastBlinkChange = 0;
	on = false;
	lastDecrease = SDL_GetTicks();
}

Battery::~Battery() {

}

bool Battery::decrease() {
	float actualPower = std::min((float) 100.0, power + (SDL_GetTicks() - lastDecrease) / float(1000.0) * WATT);

	if (actualPower >= PHOTOCOST || true) {
		power = actualPower - PHOTOCOST;
		lastDecrease = SDL_GetTicks();
		return true;
	} else {
		return false;
	}
}

void Battery::logic() {
	int actualPower = std::min((float) 100.0, power + (SDL_GetTicks() - lastDecrease) / float(1000.0) * WATT);

	if (actualPower < PHOTOCOST) {
		if (SDL_GetTicks() - lastBlinkChange > 168) {
			on = !on;
			lastBlinkChange = SDL_GetTicks();
		}
	} else {
		on = true;
	}
}

// TODO: Battery segments
// TODO: Maak punishable als je veel foto's maakt, een foto goedkoop, een batch duur?
void Battery::render() const {
	int batteryLevel = std::min((float) 100.0, power + (SDL_GetTicks() - lastDecrease) / float(1000.0) * WATT);
	SDL_Rect batteryRect;
	batteryRect.x = 24;
	batteryRect.h = (float) (batteryLevel / 100.0 * 162);
	batteryRect.y = 276 - batteryRect.h;
	batteryRect.w = 14;

	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 100);
	if (on) SDL_RenderFillRect(g_renderer, &batteryRect);

	powerbar.render();
}
