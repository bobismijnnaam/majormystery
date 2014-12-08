// Author: Bob Rubbens - Knights of the Compiler
// Creation date: za 26-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <Eigen/Dense>
#include <SDL2/SDL2_gfxPrimitives.h>

// Private
#include "nnb/log/log.hpp"
#include "main/global.hpp"
#include "world/BeginSlopeTile.hpp"

BeginSlopeTile::BeginSlopeTile() :
	SlopedTile(1, 0) {

}

BeginSlopeTile::BeginSlopeTile(int slopeOrder) :
	SlopedTile(slopeOrder, 0) {}

void BeginSlopeTile::debugRender(SDL_Renderer *tgt, int x, int y, Camera const &cam) const {
	nnb::IntRect screenView = cam.getPixelViewi();
	
	Eigen::Vector2i pts[3];

	pts[0] << x * TILE_SIZE - screenView.x, y * TILE_SIZE - screenView.y;
	pts[1] << pts[0][0] + TILE_SIZE, pts[0][1];

	int deltaY = TILE_SIZE / (float) order;

	switch (dir) {
		case nnb::Dir2::LEFT:
			pts[2] << pts[0][0], pts[0][0] + deltaY;
			break;
		case nnb::Dir2::RIGHT:
			pts[2] << pts[1][0], pts[1][1] + deltaY;
			break;
		default:
			pts[2] << pts[0][0], pts[0][1] + 1;
			NNB_LOG << "ERROR, DEFAULT CASE SHOULD NOT BE TRIGGERED. SHITBONKERS";
			break;
	}

	// Makes everything orientated correctly, since the whole coördinate system
	// expects (0; 0) to be in the bottom left but SDL screen expects (0; 0) to
	// be in the top left - thus we must FLIP
	for (Eigen::Vector2i &v : pts) {
		v[1] = SCR_H - v[1];
	}

	filledTrigonRGBA(tgt, pts[0][0], pts[0][1],
						pts[1][0], pts[1][1],
						pts[2][0], pts[2][1],
						0, 0, 0, 255);

}