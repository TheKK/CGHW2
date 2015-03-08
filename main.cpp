#include <SDL.h>
#include <cstdlib>

#include "hw2.h"
#include "glwrapper.h"

namespace {
	const int kInitWindowWidth = 300;
	const int kInitWindowHeight = 300;
}

static SDL_Window* gWindow = nullptr;
static SDL_GLContext gGLContext;

static int appIsRunning = 1;

static int logicalWindowWidth = 3;
static int logicalWindowHeight = 3;

static int
init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return -1;

	gWindow = SDL_CreateWindow(
		"Hi",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		kInitWindowWidth, kInitWindowHeight,
		SDL_WINDOW_OPENGL);
	if (!gWindow)
		return -1;

	gGLContext = SDL_GL_CreateContext(gWindow);

	return 0;
}

static void
quit()
{
	SDL_Quit();

	if (gWindow) {
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
	}

	SDL_GL_DeleteContext(gGLContext);
}

static void
eventHandler(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_QUIT:
		appIsRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_Q:
			appIsRunning = false;
			break;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			int newWidth = event.window.data1;
			int newHeight = event.window.data2;

			HW2::windowResizeHandler(newWidth, newHeight);
		}
		break;
	}
}

static void
update()
{
}

static void
render()
{
	GLWrapper::setClearColor(0.3, 0.3, 0.3, 1.f);
	GLWrapper::clearScreen();

	/*
	 * Do what i want here
	 */
	GLWrapper::setDrawColor(0.2, 1.f, 0.f);
	HW2::drawCircle(150, 150, 50, 8);

	SDL_GL_SwapWindow(gWindow);
}

int
main(int argc, char* argv[])
{
	SDL_Event event;

	if (init()) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError());
		quit();

		return EXIT_FAILURE;
	}

	HW2::setRenderLogicalSize(kInitWindowWidth, kInitWindowHeight);
	HW2::windowResizeHandler(kInitWindowWidth, kInitWindowHeight);

	while (appIsRunning) {
		while (SDL_PollEvent(&event))
			eventHandler(event);
		update();
		render();

		SDL_Delay(30);
	}

	quit();

	return EXIT_SUCCESS;
}
