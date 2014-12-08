// File: Shutter.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "game/Shutter.hpp"
#include "main/global.hpp"
#include "nnb/utils/constants.hpp"

Shutter::Shutter(int slideTime_) :
state{ShutterState::CLOSED},
stateTimer{0},
pos{0, 0},
slideTime{slideTime_} {
	for (int i = 0; i < 6; i++) {
		shuts[i] = g_tm->getTexture("default", "60.png");
		shuts[i].setRotation(i * 60);
	}
}

Shutter::~Shutter() {
}

void Shutter::open() {
	state = ShutterState::OPENING;
	stateTimer = SDL_GetTicks();
}

void Shutter::close() {
	state = ShutterState::CLOSING;
	stateTimer = SDL_GetTicks();
}

void Shutter::blinkOpen() {
	state = ShutterState::CLOSEAFTER;
	stateTimer = SDL_GetTicks();
}

void Shutter::blinkClose() {
	state = ShutterState::OPENAFTER;
	stateTimer = SDL_GetTicks();
}

void Shutter::logic() {
	float d = (SDL_GetTicks() - stateTimer) / (float) slideTime;

	switch (state) {
	case ShutterState::OPEN:
		d = 1;
		break;
	case ShutterState::OPENING:
		if (SDL_GetTicks() - stateTimer > slideTime) {
			state = ShutterState::OPEN;
			stateTimer = 0;
			d = 1;
		} 
		break;
	case ShutterState::CLOSED:
		d = 0;
		break;
	case ShutterState::CLOSING:
		if (SDL_GetTicks() - stateTimer > slideTime) {
			state = ShutterState::CLOSED;
			stateTimer = 0;
			d = 0;
		} else {
			d = 1 - d;
		}
		break;
	case ShutterState::CLOSEAFTER:
		if (SDL_GetTicks() - stateTimer > slideTime) {
			state = ShutterState::CLOSING;
			stateTimer = SDL_GetTicks();
			d = 1;
		} 
		break;
	case ShutterState::OPENAFTER:
		if (SDL_GetTicks() - stateTimer > slideTime) {
			state = ShutterState::OPENING;
			stateTimer = SDL_GetTicks();
			d = 0;
		} else {
			d = 1 - d;
		}
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 6; ++i) {
		int alpha = i * 60; 
		float r = VIEW_W / 2 / cos(nnb::PI * 1/3);
		float sx = pos.x * VIEW_W + VIEW_W / 2.0 + cos((alpha - 60.0) * nnb::PI / 180.0) * d * r;
		float sy = pos.y * VIEW_H + VIEW_H / 2.0 + sin((alpha - 60.0) * nnb::PI / 180.0) * d * r;
		shuts[i].setPosition(sx, sy);
	}
}

void Shutter::render() const {
	for (auto& s : shuts) {
		s.render();
	}
}

	/*
	SDL_SetRenderDrawColor(g_renderer, 128, 128, 128, 255);
	SDL_Rect left, right, full = {pos.x * VIEW_W, pos.y * VIEW_H, VIEW_W, VIEW_H};
	float d = (SDL_GetTicks() - stateTimer) / (float) slideTime;

	switch (state) {
	case ShutterState::OPEN:
		return;
		break;
	case ShutterState::OPENING:
		d = 1 - d;
		break;
	case ShutterState::CLOSING:
		break;
	case ShutterState::CLOSED:
		SDL_RenderFillRect(g_renderer, &full);
		return;
		break;
	default:
		break;
	}
	
	left.x = pos.x * VIEW_W; 
	left.y = pos.y * VIEW_H;
	left.w = (int) (VIEW_W / 2.0 * d);
	left.h = VIEW_H;

	right.x = pos.x * VIEW_W + VIEW_W - (int) (VIEW_W / 2.0 * d);
	right.y = pos.y * VIEW_H;
	right.w = (int) (VIEW_W / 2.0 * d);
	right.h = VIEW_H;

	SDL_RenderFillRect(g_renderer, &left);
	SDL_RenderFillRect(g_renderer, &right);
	*/

