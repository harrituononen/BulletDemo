/*
	GRAFIIKKAOHJELMOINTI
	Metropolia AMK, 2016
*/
#include "esimerkki.h"

SDL_Window*		window		= 0;
SDL_GLContext	gl_context	= 0;


/*
	Init SDL etc.
*/
int init()
{
	// RNG seed.
	srand((unsigned)time(0));

	// For SDL initialization and window creation, see
	// https://wiki.libsdl.org/SDL_CreateWindow
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 0;
	window = SDL_CreateWindow
	(
		WINDOW_TITLE,					// window title
		SDL_WINDOWPOS_UNDEFINED,		// initial x position
		SDL_WINDOWPOS_UNDEFINED,		// initial y position
		WINDOW_WIDTH,					// width, in pixels
		WINDOW_HEIGHT,					// height, in pixels
		SDL_WINDOW_OPENGL				// flags
	);
	if (!window)
		return 0;

	// For OpenGL context creation, see
	// https://wiki.libsdl.org/SDL_GL_CreateContext
	gl_context = SDL_GL_CreateContext(window);
	if (!gl_context)
		return 0;

	// For GLEW initialization, see
	// http://glew.sourceforge.net/basic.html
	if (glewInit() != GLEW_OK)
		return 0;

	return 1;
}


/*
	Global finalizations.
*/
int fini()
{
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}
