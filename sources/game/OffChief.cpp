// File: OffChief.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <tuple>

// Private
#include "game/OffChief.hpp"
#include "nnb/utils/StringHelpers.hpp"
#include "nnb/utils/constants.hpp"

float dist(SDL_Point a, SDL_Point b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void printRect(SDL_Rect a) {
	NNB_INFO << "SDL_Rect {x: " << a.x << "; y: " << a.y << "; w: " << a.w << "; h: " << a.h << "}";
}

OffChief::OffChief() {
	g_tm->loadGroup("wearables");

	torso = g_tm->getTexture("game", "major.png");
	torso.setOrigin(27, 111);

	leg[0] = g_tm->getTexture("game", "leg.png");
	leg[1] = g_tm->getTexture("game", "leg.png");
	
	leg[0].setOrigin(5, 0);
	leg[0].setRotationCenter(5, 0);

	leg[1].setOrigin(5, 0);
	leg[1].setRotationCenter(5, 0);
}

OffChief::~OffChief() {
	g_tm->unloadGroup("wearables");
}

void OffChief::pushAction(std::string action) {
	actions.push_back(action);
}

void OffChief::logic(SDL_Rect view) {
	currentView = view;

	while (int(SDL_GetTicks()) - actionStart >= actionDuration && !finished) {
		// Finish current action
		if (actionType == "move") {
			currPos = targetPos;
		}
		currentAction = "";
		actionType = "";

		if (actions.size() > 0) {
			// Next action
			currentAction = actions.front();
			actions.pop_front();
			std::vector<std::string> tokens = nnb::split(currentAction, " ");
			actionType = tokens[0];

			actionStart = SDL_GetTicks();
			actionDuration = -1;

			if (actionType == "warp") {
				int nx = nnb::stoi(tokens[1]);
				int ny = nnb::stoi(tokens[2]);
				currPos = {nx, ny};
			} else if (actionType == "move") {
				int nx = nnb::stoi(tokens[1]);
				int ny = nnb::stoi(tokens[2]);
				targetPos = {nx, ny};
				actionDuration = int(dist(currPos, targetPos) / float(MAJOR_WALKSPEED) * 1000);
			} else if (actionType == "look") {
				if (lookDir != nnb::stoi(tokens[1])) {
					lookDir *= -1;
				}
			} else if (actionType == "pause") {
				actionDuration = nnb::stoi(tokens[1]);
			} else if (actionType == "wear") {
				wearable = g_tm->getTexture("wearables", tokens[1]);
				int dx = nnb::stoi(tokens[2]);
				int dy = nnb::stoi(tokens[3]);
				int ox = nnb::stoi(tokens[4]);
				int oy = nnb::stoi(tokens[5]);
				int cx = nnb::stoi(tokens[6]);
				int cy = nnb::stoi(tokens[7]);
				int rot = nnb::stoi(tokens[8]);

				wearingOffset = {dx, dy};
				wearable.setOrigin(ox, oy);
				wearable.setRotationCenter(cx, cy);
				wearable.setRotation(rot);
				wearing = tokens[1];
			} else if (actionType == "drop") {
				dropped = g_tm->getTexture("wearables", tokens[1]);
				droppedPos.x = nnb::stoi(tokens[2]);
				droppedPos.y = nnb::stoi(tokens[3]);
				int ox = nnb::stoi(tokens[4]);
				int oy = nnb::stoi(tokens[5]);
				int rot = nnb::stoi(tokens[6]);
				dropped.setOrigin(ox, oy);
				dropped.setRotation(rot);
			} else if (actionType == "unwear") {
				wearable = nnb::TextureContainer();
				wearing = "";
			} else if (actionType == "undrop") {
				dropped = nnb::TextureContainer();
			} else if (actionType == "mirrorwear") {
				wearable.setFlip(SDL_FLIP_HORIZONTAL);
			} else if (actionType == "shoot") {
				SDL_Point bulletPos = currPos;
				bulletPos.y -= 40;
				auto newBullet = std::make_tuple(SDL_GetTicks(), bulletPos, lookDir);
				bullets.push_back(newBullet);
			} else if (actionType == "finished") {
				finished = true;
			} else {
				NNB_ERROR << "Unknown action: \"" << currentAction << "\"";
			}
		}
	}

	// Move character and animate if moving
	SDL_Point nowPos = currPos;

	if (actionType == "move") {
		float travelDist = dist(currPos, targetPos);
		float travelTime = travelDist / MAJOR_WALKSPEED;
		int elapsedTime = SDL_GetTicks() - actionStart;
		float d = elapsedTime / float(travelTime * 1000) ;

		nowPos.x = currPos.x * (1 - d) + targetPos.x * d;
		nowPos.y = currPos.y * (1 - d) + targetPos.y * d;

		leg[0].setRotation(sin(elapsedTime / float(MAJOR_LEGTIME) * 2 * nnb::PI ) * 25);
		leg[1].setRotation(sin(elapsedTime / float(MAJOR_LEGTIME) * 2 * nnb::PI ) * 25 * -1);
	} else {
		// Else put legs at normal place and position at currPos
		leg[0].setRotation(0);
		leg[1].setRotation(0);
	}

	// Position stuff
	torso.setPosition(nowPos.x - currentView.x, nowPos.y - currentView.y);
	leg[0].setPosition(nowPos.x - currentView.x - 6, nowPos.y - currentView.y);
	leg[1].setPosition(nowPos.x - currentView.x + 5, nowPos.y - currentView.y);

	// Look the right way
	if (lookDir == -1) {
		torso.setFlip(SDL_FLIP_HORIZONTAL);
	} else {
		torso.setFlip(SDL_FLIP_NONE);
	}

	// TODO: Position dropped
	dropped.setPosition(droppedPos.x - currentView.x, droppedPos.y - currentView.y);

	SDL_Point wearablePos = nowPos;
	wearablePos.x += wearingOffset.x;
	wearablePos.y += wearingOffset.y;
	wearable.setPosition(wearablePos.x - currentView.x, wearablePos.y - currentView.y);
	
	for (auto it = bullets.begin(); it != bullets.end();) {
		SDL_Rect bulletShape = {0, 0, BULLET_W, BULLET_H};
		auto base = std::get<1>(*it);
		auto bulletDir = std::get<2>(*it);
		bulletShape.x = (SDL_GetTicks() - std::get<0>(*it)) / 1000.0 * float(BULLET_SPD) * bulletDir + base.x;
		bulletShape.y = base.y;
		SDL_Rect world = {0, 0, WORLD_W, WORLD_H};

		SDL_Rect interRect;
		if (!SDL_IntersectRect(&world, &bulletShape, &interRect) && SDL_RectEmpty(&interRect)) {
			it = bullets.erase(it);
		} else {
			it++;
		}
	}
}

void OffChief::render() const {
	dropped.render();

	leg[0].render();
	leg[1].render();
	torso.render();
	
	wearable.render();
	
	SDL_Rect bulletShape = {0, 0, BULLET_W, BULLET_H};
	SDL_SetRenderDrawColor(g_renderer, 40, 40, 40, 255);
	for (auto bullet : bullets) {
		auto base = std::get<1>(bullet);
		int dir = std::get<2>(bullet);
		bulletShape.x = (SDL_GetTicks() - std::get<0>(bullet)) / 1000.0 * float(BULLET_SPD) * dir + base.x - currentView.x;
		bulletShape.y = base.y - currentView.y;
		SDL_RenderFillRect(g_renderer, &bulletShape);
	}
}

bool OffChief::isInFrame(SDL_Rect view) {
	SDL_Rect interRect;
	SDL_Rect chiefBounds = torso.getBounds();
	chiefBounds.x += view.x;
	chiefBounds.y += view.y;
	SDL_IntersectRect(&view, &chiefBounds, &interRect);

	bool intersectsOrContains = !SDL_RectEmpty(&interRect);
	return intersectsOrContains;
}

bool OffChief::isWearableInFrame(SDL_Rect view) {
	return false;
}

std::string OffChief::getWearable() {
	return wearing;
}

bool OffChief::isFinished() {
	return finished;
}

/*
Possible actions:

warp x y
move x y
look l/r
pause t
wear name rx ry ox oy cx cy rotation
unwear
undrop
mirrorwear
drop name x y ox oy rotation 
shoot

   */

