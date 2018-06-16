/*
	GRAFIIKKAOHJELMOINTI
	Metropolia AMK, 2016
*/
#pragma once

//
// Includes
//
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <Box2D/Box2D.h>

//
// Defines - tweak as you like
//
//#define WINDOW_WIDTH	640
//#define WINDOW_HEIGHT	480
//#define WINDOW_WIDTH	800
//#define WINDOW_HEIGHT	600
#define WINDOW_WIDTH	1280
#define WINDOW_HEIGHT	720
#define WINDOW_TITLE	"Esimerkki"
#define CLEAR_COLOR		0, 0, 0, 0
#define DRAW_COLOR		1.0, 1.0, 1.0

//
// Prototypes
//
int init();
int fini();

//
// Globals
//
extern SDL_Window*		window;
extern SDL_GLContext	gl_context;
