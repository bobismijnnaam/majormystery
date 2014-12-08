// File: gsIntro.cpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-12-06
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public

// Private
#include "gamestates/gsIntro.hpp"
#include "main/global.hpp"
#include "nnb/utils/SDL_Helpers.hpp"

gsIntro::gsIntro() {
	g_rm->switchTarget(1, 0);
	stateStart = SDL_GetTicks();

	locText = g_fm->getText("GentiumPlus-R.ttf", 40);
	locText.setText("");
	locText.setVAlign(nnb::VAlign::CENTER);
	locText.setHAlign(nnb::HAlign::CENTER);
	locText.setPosition(VIEW_W / 2, 300);
	locText.setColor(255, 255, 255);

	bg = g_tm->getTexture("game", "selection.png");

	if (woodsCaught == 2) {
		locationMark[2] = g_tm->getTexture("game", "checkmark.png");
	} else if (woodsCaught == 1) {
		locationMark[2] = g_tm->getTexture("game", "cross.png");
	}
	if (cityCaught == 2) {
		locationMark[1] = g_tm->getTexture("game", "checkmark.png");
	} else if (cityCaught == 1) {
		locationMark[1] = g_tm->getTexture("game", "cross.png");
	}
	if (golfCaught == 2) {
		locationMark[0] = g_tm->getTexture("game", "checkmark.png");
	} else if (golfCaught == 1) {
		locationMark[0] = g_tm->getTexture("game", "cross.png");
	}

	locationMark[0].setPosition(113, 211);
	locationMark[1].setPosition(290, 88);
	locationMark[2].setPosition(376, 199);

	for (auto& mark : locationMark) {
		mark.setOrigin(75, 75);
	}

	if (justDid != 0) {
		NNB_INFO << "Congratz, you just did " << justDid;
		int i = justDid - 1;
		locationMark[i].setSize(250, 250);
		locationMark[i].setOrigin(locationMark[i].getRenderWidth() / 2,
				locationMark[i].getRenderHeight() / 2);
		locationMark[i].setRotation(540);
		locationMark[i].setRotationCenter(locationMark[i].getRenderWidth() / 2,
				locationMark[i].getRenderHeight() / 2);
	}

	doWeird = woodsCaught && cityCaught && golfCaught;

	if (doWeird) {
		youWin = g_fm->getText("GentiumPlus-R.ttf", 120);
		youWin.setText("You win!");
		youWin.setVAlign(nnb::VAlign::CENTER);
		youWin.setHAlign(nnb::HAlign::CENTER);
		youWin.setPosition(VIEW_W / 2, VIEW_H / 2);
		youWin.setColor(193, 193, 193);
	}

	/*
	g_tm->loadGroup("wearables");
	if (doWeird) {
		weirdTimer = SDL_GetTicks();
		bodyparts[0] = g_tm->getTexture("wearables", "wildleg.png");
		bodyparts[1] = g_tm->getTexture("wearables", "wildleg.png");
		bodyparts[2] = g_tm->getTexture("wearables", "torso.png");
		bodyparts[3] = g_tm->getTexture("wearables", "bambi.png");
	}
	*/
}

gsIntro::~gsIntro() {
	justDid = 0;
	// g_tm->unloadGroup("wearables");
}

void gsIntro::event(SDL_Event& e) {
	SDL_Rect golf = {16, 109, 232, 164};
	SDL_Rect woods = {295, 114, 162, 192};
	SDL_Rect city = {184, 3, 217, 94};
	SDL_Point p;
	bool mouseDown = false, mouseMove = false;
	
	switch (e.type) {
	case SDL_QUIT:
		g_gm->exit();
		break;
	case SDL_MOUSEMOTION:
		p.x = e.motion.x - VIEW_W;
		p.y = e.motion.y;
		mouseMove = true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		p.x = e.button.x - VIEW_W;
		p.y = e.button.y;
		mouseDown = true;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			g_gm->changeState(nnb::StateAction::SET, "main");
		}
		break;
	default:
		break;
	}

	if (mouseDown || mouseMove) {
		if (nnb::pointInRect(p, golf)) {
			locText.setText("The Golfcourse");
			if (mouseDown) {
				g_gm->changeState(nnb::StateAction::SET, "game");
				chosenLvl = "golf";
			}
		} else if (nnb::pointInRect(p, woods)) {
			locText.setText("The Woods");
			if (mouseDown) {
				g_gm->changeState(nnb::StateAction::SET, "game");
				chosenLvl = "woods";
			}
		} else if (nnb::pointInRect(p, city)) {
			locText.setText("The City");
			if (mouseDown) {
				g_gm->changeState(nnb::StateAction::SET, "game");
				chosenLvl = "city";
			}
		} else {
			locText.setText("");
		}
	}
}

void gsIntro::logic(float delta) {
	if (justDid != 0) {
		int i = justDid - 1;
		int eltim = SDL_GetTicks() - stateStart;
		if (eltim > 1000) {
			locationMark[i].setRotation(0);
			locationMark[i].resetSize();
			locationMark[i].setOrigin(75, 75);
			locationMark[i].setRotationCenter(locationMark[i].getRenderWidth() / 2, locationMark[i].getRenderHeight() / 2);
			justDid = 0;
		} else {
			float d = eltim / 1000.0;
			d *= d;
			locationMark[i].setRotation((1 - d) * 540.0);
			locationMark[i].setSize(150.0 * d + (1 - d) * 250.0, 150.0 * d + (1 - d) * 250.0);
			locationMark[i].setOrigin(locationMark[i].getRenderWidth() / 2, locationMark[i].getRenderHeight() / 2);
			locationMark[i].setRotationCenter(locationMark[i].getRenderWidth() / 2, locationMark[i].getRenderHeight() / 2);
		}
	}

	/*
	switch (ctr) {
	case 0:
		if (SDL_GetTicks() - stateStart > 500) {
			ctrText.setText("3...");
			ctr++;
			stateStart = SDL_GetTicks();
		}
		break;
	case 1:
		if (SDL_GetTicks() - stateStart > 1000) {
			ctrText.setText("3... 2...");
			ctr++;
			stateStart = SDL_GetTicks();
		}
		break;
	case 2:
		if (SDL_GetTicks() - stateStart > 1000) {
			ctrText.setText("3... 2... 1...");
			ctr++;
			stateStart = SDL_GetTicks();
		}
		break;
	case 3:
		if (SDL_GetTicks() - stateStart > 1000) {
			startText.setText("Happy spotting!");
			ctr++;
			stateStart = SDL_GetTicks();
		}
		break;
	case 4:
		if (SDL_GetTicks() - stateStart > 500) {
			g_gm->changeState(nnb::StateAction::SET, "game");
		}
	default:
		// nope;
		break;
	}
	*/
}

void gsIntro::render() const {
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_renderer);
	
	/*
	ctrText.render();
	startText.render();
	*/

	bg.render();

	locText.render();

	for (auto& tc : locationMark) {
		tc.render();
	}

	if (doWeird) {
		SDL_Rect bgarea = {0, 137, VIEW_W, 116};
		SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(g_renderer, &bgarea);
	}
	youWin.render();
	
	g_rm->publish();
}
