// File: RendererManager.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "game/RendererManager.hpp"
#include "nnb/log/log.hpp"
#include "main/global.hpp"

RendererManager::RendererManager() {
	for (int x = 0; x < 2; ++x) {
		for (int y = 0; y < 2; ++y) {
			int i = x + y * 2;
			views[i].reset(SDL_CreateTexture(g_renderer, 
						SDL_GetWindowPixelFormat(g_window),
						SDL_TEXTUREACCESS_TARGET, 
						VIEW_W, VIEW_H));
			viewContainers[i].setTexture(g_renderer, views[i].get());
			viewContainers[i].setPosition(x * VIEW_W, y * VIEW_H);
		}
	}
}

RendererManager::~RendererManager() {
	// std::unique_ptr!
}

void RendererManager::switchTarget(int x, int y) {
	nextView = {x, y};
	SDL_SetRenderTarget(g_renderer, views[x + y * 2].get());
}

void RendererManager::setDefault() {
	SDL_SetRenderTarget(g_renderer, nullptr);
}

void RendererManager::logic() {
	setDefault();
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);

	if (nextView.x != -1) {
		shutters[currentView].close();

		currentView = nextView.x + nextView.y * 2;
		nextView = {-1, -1};

		shutters[currentView].open();
	}

	SDL_SetRenderTarget(g_renderer, views[currentView].get());

	for (auto& s : shutters) {
		s.logic();
	}
}

void RendererManager::publish() {
	for (int i = 0; i < 4; ++i) {
		SDL_SetRenderTarget(g_renderer, views[i].get());
		shutters[i].render();
	}

	setDefault();

	for (int i = 0; i < 4; ++i) {
		viewContainers[i].render();
	}

	SDL_Rect horSmall, horBig, verSmall, verBig;

	horSmall = {0, 382, 1024, 4};
	horBig = {0, 380, 1024, 8};
	verSmall = {510, 0, 4, 768};
	verBig = {508, 0, 8, 768};

	SDL_SetRenderDrawColor(g_renderer, 166, 166, 166, 255);
	SDL_RenderFillRect(g_renderer, &horBig);
	SDL_RenderFillRect(g_renderer, &verBig);
	SDL_SetRenderDrawColor(g_renderer, 205, 205, 205, 255);
	SDL_RenderFillRect(g_renderer, &horSmall);
	SDL_RenderFillRect(g_renderer, &verSmall);

	SDL_RenderPresent(g_renderer);
}
