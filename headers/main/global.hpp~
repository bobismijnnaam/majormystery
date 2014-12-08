// File: global.hpp
// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

// Public
#include <SDL2/SDL.h>
#include <memory>

// Private
#include "main/global.hpp"
#include "nnb/states/StateMachine.hpp"
#include "nnb/utils/GameFrame.hpp"
#include "nnb/resources/Settings.hpp"
#include "nnb/resources/FontManager.hpp"
#include "nnb/resources/TextureManager.hpp"
#include "game/RendererManager.hpp"

extern SDL_Window *g_window;
extern SDL_Surface *g_windowSurface;
extern SDL_Renderer *g_renderer;

extern std::unique_ptr<nnb::StateMachine> g_gm;
extern std::unique_ptr<nnb::FontManager> g_fm;
extern std::unique_ptr<nnb::TextureManager> g_tm;

extern nnb::GameFrame g_gf;
extern nnb::Settings g_sts;

extern int SCR_W;
extern int SCR_H;
extern std::string SCR_TITLE;

extern int VIEW_W;
extern int VIEW_H;

extern int WORLD_W;
extern int WORLD_H;

extern std::string chosenLvl;

extern int justDid;
extern int woodsCaught;
extern int cityCaught;
extern int golfCaught;

extern std::unique_ptr<RendererManager> g_rm;

#endif
