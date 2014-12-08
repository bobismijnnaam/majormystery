// Author: Bob Rubbens - Knights of the Compiler
// Creation date: ma 28-07-2014
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <Eigen/Dense>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

// Private
#include "nnb/log/log.hpp"
#include "world/EndSlopeTile.hpp"

EndSlopeTile::EndSlopeTile() :
	SlopedTile(1, 0) {

}

EndSlopeTile::EndSlopeTile(int slopeOrder) :
	SlopedTile(slopeOrder, 0) {

}

void EndSlopeTile::debugRender(SDL_Renderer *tgt, int x, int y, Camera const &cam) const {
	nnb::IntRect screenView = cam.getPixelViewi();
	
	Eigen::Vector2i pts[4];

	pts[0] << x * TILE_SIZE - screenView.x, y * TILE_SIZE - screenView.y;
	pts[1] << pts[0][0] + TILE_SIZE, pts[0][1];

	int deltaY = TILE_SIZE - TILE_SIZE / (float) order;

	switch (dir) {
		case nnb::Dir2::LEFT:
			pts[2] << pts[1][0], pts[1][1] + deltaY;
			pts[3] << pts[0][0], pts[0][1] + TILE_SIZE;
			break;
		case nnb::Dir2::RIGHT:
			pts[2] << pts[1][0], pts[1][1] + TILE_SIZE;
			pts[3] << pts[0][0], pts[0][1] + deltaY;
			break;
		default:
			pts[2] << pts[1][0], pts[1][1] + 1;
			pts[3] << pts[0][0], pts[0][1] + 2;
			NNB_LOG << "ERROR, DEFAULT CASE SHOULD NOT BE TRIGGERED. SHITBONKERS";
			break;
	}

	Sint16 vx[4];
	Sint16 vy[4];

	// Makes everything orientated correctly, since the whole coördinate system
	// expects (0; 0) to be in the bottom left but SDL screen expects (0; 0) to
	// be in the top left - thus we must FLIP
	// Oh, and we also convert those Vector2f[] to two int[]
	for (int i = 0; i < 4; i++) {
		pts[i][1] = SCR_H - pts[i][1];
		vx[i] = pts[i][0];
		vy[i] = pts[i][1];
	}
	
	filledPolygonRGBA(tgt, vx, vy, 4, 0, 0, 0, 255);
}