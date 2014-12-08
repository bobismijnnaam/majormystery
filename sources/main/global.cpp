// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 2014-11-07
// Contact: http://plusminos.nl - @broervanlisa - gmail (bobrubbens)

// Public
#include <SDL2/SDL.h>

// Private
#include "main/global.hpp"
#include "nnb/states/StateMachine.hpp"
#include "nnb/utils/GameFrame.hpp"
#include "nnb/resources/TextureManager.hpp"

SDL_Window *g_window = NULL;
SDL_Surface *g_windowSurface = NULL;
SDL_Renderer *g_renderer = NULL;

std::unique_ptr<nnb::StateMachine> g_gm(nullptr);
std::unique_ptr<nnb::FontManager> g_fm(nullptr);
std::unique_ptr<nnb::TextureManager> g_tm(nullptr);

nnb::GameFrame g_gf;
nnb::Settings g_sts;

int SCR_W = 0;
int SCR_H = 0;
std::string SCR_TITLE = "";
int VIEW_W = 0;
int VIEW_H = 0;
int WORLD_W = 2048;
int WORLD_H = 1536;

std::string chosenLvl = "";

int justDid = 0;
int woodsCaught = 0;
int cityCaught = 0;
int golfCaught = 0;

std::unique_ptr<RendererManager> g_rm(nullptr);
