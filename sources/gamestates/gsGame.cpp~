// File: gsGame.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <cmath>
#include <SDL2/SDL.h>
#include <string>

// Private
#include "gamestates/gsGame.hpp"
#include "main/global.hpp"
#include "nnb/log/log.hpp"
#include "nnb/states/GameState.hpp"
#include "nnb/utils/unique_ptr.hpp"
#include "nnb/utils/StringHelpers.hpp"

gsGame::gsGame() :
shutter{150} {
	g_tm->loadGroup("scenes");

	NNB_INFO << "loading hud";
	hud = g_tm->getTexture("game", "hud.png");
	hud.setAlpha(100);

	fog = g_tm->getTexture("game", "fog.png");

	g_rm->switchTarget(1, 1);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	
	view.w = VIEW_W;
	view.h = VIEW_H;
	/*
	view.x = (2048 - view.w) / 2;
	view.y = (1536 - view.h) / 2;
	*/
	view.x = 0;
	view.y = 0;

	shutter.open();

	if (chosenLvl == "woods") {
		chief.pushAction("warp -130 242");
		chief.pushAction("move 1496 242");
		chief.pushAction("pause 1000");
		chief.pushAction("wear gun.png -30 -50 0 0 0 0 0");
		chief.pushAction("pause 600");
		chief.pushAction("shoot");
		chief.pushAction("pause 700");
		chief.pushAction("shoot");
		chief.pushAction("pause 700");
		chief.pushAction("shoot");
		chief.pushAction("pause 700");
		chief.pushAction("shoot");
		chief.pushAction("pause 700");
		chief.pushAction("move 1798 242");
		chief.pushAction("wear wildleg.png 30 -80 23 88 23 88 210");
		chief.pushAction("look -1");
		chief.pushAction("move -130 242");
		chief.pushAction("finished");

		bg = g_tm->getTexture("scenes", "woodsbg.png");
		fg = g_tm->getTexture("scenes", "woods.png");
	} else if (chosenLvl == "city") {
		chief.pushAction("warp 2248 738");
		// chief.pushAction("warp 500 738");
		chief.pushAction("look -1");
		chief.pushAction("wear car.png 0 0 65 124 0 0 0");
		chief.pushAction("move 194 738");
		chief.pushAction("unwear");
		chief.pushAction("drop car.png 132 614 0 0 0");
		chief.pushAction("warp 100 738");
		chief.pushAction("move 100 838");
		chief.pushAction("look 1");
		chief.pushAction("move 450 838");
		chief.pushAction("move 450 730");
		chief.pushAction("look -1");
		chief.pushAction("wear wildleg.png 30 -80 23 88 23 88 210");
		chief.pushAction("pause 300");
		chief.pushAction("mirrorwear");
		chief.pushAction("unwear");
		chief.pushAction("look 1");
		chief.pushAction("wear wildleg.png -28 -80 14 88 14 88 150");
		chief.pushAction("move 584 730");
		chief.pushAction("move 584 682");
		chief.pushAction("move 740 682");
		chief.pushAction("unwear");
		chief.pushAction("pause 2000");
		chief.pushAction("look -1");
		chief.pushAction("move 584 676");
		chief.pushAction("move 584 838");
		chief.pushAction("move 100 838");
		chief.pushAction("look 1");
		chief.pushAction("move 100 738");
		chief.pushAction("warp 194 738");
		chief.pushAction("wear car.png 0 0 65 124 0 0 0");
		chief.pushAction("look -1");
		chief.pushAction("undrop");
		chief.pushAction("pause 500");
		chief.pushAction("move -400 738");
		chief.pushAction("finished");

		bg = g_tm->getTexture("scenes", "citybg.png");
		fg = g_tm->getTexture("scenes", "cityfg.png");
	} else if (chosenLvl == "golf") {
		chief.pushAction("warp 2104 1330");
		chief.pushAction("wear car.png 0 0 65 124 0 0 0");
		chief.pushAction("look -1");
		chief.pushAction("move 1658 1330");
		chief.pushAction("move 1658 914");
		chief.pushAction("move 934 914");
		chief.pushAction("drop car.png 869 790 0 0 0");
		chief.pushAction("unwear");
		chief.pushAction("warp 818 914");
		chief.pushAction("pause 300");
		chief.pushAction("look 1");
		chief.pushAction("pause 300");
		chief.pushAction("wear bambi.png 0 -30 28 37 0 0 0");
		chief.pushAction("pause 333");
		chief.pushAction("move 818 664");
		chief.pushAction("move 1518 664");
		chief.pushAction("drop bambi.png 1418 524 0 0 0");
		chief.pushAction("unwear");
		chief.pushAction("look -1");
		chief.pushAction("pause 500");
		chief.pushAction("wear cigar.png -64 -125 0 0 0 0 0");
		chief.pushAction("pause 3000");
		chief.pushAction("finished");

		bg = g_tm->getTexture("scenes", "golfbg.png");
		fg = g_tm->getTexture("scenes", "golffg.png");
	} else {
		NNB_ERROR << "Level not recognized: \"" << chosenLvl << "\"";
		chief.pushAction("warp 500 500");
	}

	viewInfo = g_fm->getText("GentiumPlus-R.ttf", 20);
	viewInfo.setText("(?; ?)");
	viewInfo.setPosition(VIEW_W / 2, VIEW_H / 2);
	viewInfo.setColor(nnb::Color::WHITE);
}

gsGame::~gsGame() {
	g_tm->unloadGroup("scenes");

	SDL_SetRelativeMouseMode(SDL_FALSE);
}

void gsGame::event(SDL_Event& e) {
	switch (e.type) {
		case SDL_QUIT:
			g_gm->exit();
			break;
		case SDL_MOUSEMOTION:
			view.x += e.motion.xrel * 2.0;
			view.y += e.motion.yrel * 2.0;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				g_gm->changeState(nnb::StateAction::SET, "intro");
				caught = true;
				if (chosenLvl == "city") {
					cityCaught = 1;
					justDid = 2;
				} else if (chosenLvl == "woods") {
					woodsCaught = 1;
					justDid = 3;
				} else if (chosenLvl == "golf") {
					golfCaught = 1;
					justDid = 1;
				}
			} else if (e.key.keysym.sym == SDLK_RETURN) {
				if (battery.decrease()) {
					shutter.blinkClose();
					NNB_INFO << "Smile!";
					if (chief.isInFrame(view.toSDLRect()) && !caught) {
						if (chief.getWearable() == "wildleg.png" || chief.getWearable() == "bambi.png") {
							returnTimer = SDL_GetTicks();
							caught = true;
							if (chosenLvl == "city") {
								cityCaught = 2;
								justDid = 2;
							} else if (chosenLvl == "woods") {
								woodsCaught = 2;
								justDid = 3;
							} else if (chosenLvl == "golf") {
								golfCaught = 2;
								justDid = 1;
							}
						}
					}
				}
			} else if (e.key.keysym.sym == SDLK_SLASH) {
				returnTimer = SDL_GetTicks();
				caught = true;
				if (chosenLvl == "city") {
					cityCaught = 2;
					justDid = 2;
				} else if (chosenLvl == "woods") {
					woodsCaught = 2;
					justDid = 3;
				} else if (chosenLvl == "golf") {
					golfCaught = 2;
					justDid = 1;
				}
			}
			break;
		default:
			break;
	}

	if (view.x < 0) view.x = 0;
	if (view.y < 0) view.y = 0;
	if (view.x + view.w > 2048) view.x = 2048 - view.w;
	if (view.y + view.h > 1536) view.y = 1536 - view.h;

	fg.setPosition(-view.x, -view.y);
	bg.setPosition(-view.x, -view.y);

	viewInfo.setText("(" + nnb::tos(view.x + VIEW_W / 2) + "; " + nnb::tos(view.y + VIEW_H / 2) + ")");
}

void gsGame::logic(float delta) {
	// No logic here
	// ...
	// Just madness
	//
	// Haha jk
	
	chief.logic(view.toSDLRect());

	shutter.logic();
	battery.logic();

	if (chief.isFinished() && !caught && returnTimer == -1) {
		returnTimer = SDL_GetTicks();
		if (chosenLvl == "city") {
			if (cityCaught != 2) cityCaught = 1;
			justDid = 2;
		} else if (chosenLvl == "woods") {
			if (woodsCaught != 2) woodsCaught = 1;
			justDid = 3;
		} else if (chosenLvl == "golf") {
			if (golfCaught != 2) golfCaught = 1;
			justDid = 1;
		}
	}

	if (returnTimer != -1) {
		if (SDL_GetTicks() - returnTimer >= 1000) {
			g_gm->changeState(nnb::StateAction::SET, "intro");
		}
	}
}

void gsGame::render() const {
	SDL_SetRenderDrawColor(g_renderer, 38, 179, 0, 255);
	SDL_RenderClear(g_renderer);

	bg.render();

	chief.render();

	fg.render();

	fog.render();

	shutter.render();

	hud.render();

	battery.render();

	// viewInfo.render();

	g_rm->publish();
}
