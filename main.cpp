#include <SDL.h>
#include <cstdlib>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h"
#include "modelInstance.h"

namespace {
	const int kInitWindowWidth = 800;
	const int kInitWindowHeight = 800;
}

static SDL_Window* gWindow = nullptr;
static SDL_GLContext gGLContext;
static Renderer gRenderer;

static int appIsRunning = 1;

static glm::mat4 viewMatrix(1.0);

static ModelInstance testInst;
static ModelInstance testInst2;

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

	if (gRenderer.create(gWindow, RENDERER_SOFTWARERENDER) < 0)
		return -1;

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
		case SDL_SCANCODE_UP:
			viewMatrix = glm::translate(viewMatrix,
						    glm::vec3(0, 1, 0));
			gRenderer.setViewMatrix(viewMatrix);
			break;
		case SDL_SCANCODE_DOWN:
			viewMatrix = glm::translate(viewMatrix,
						    glm::vec3(0, -1, 0));
			gRenderer.setViewMatrix(viewMatrix);
			break;
		case SDL_SCANCODE_LEFT:
			viewMatrix = glm::translate(viewMatrix,
						    glm::vec3(1, 0, 0));
			gRenderer.setViewMatrix(viewMatrix);
			break;
		case SDL_SCANCODE_RIGHT:
			viewMatrix = glm::translate(viewMatrix,
						    glm::vec3(-1, 0, 0));
			gRenderer.setViewMatrix(viewMatrix);
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		if (event.motion.state == SDL_BUTTON_LMASK) {
			float dx =  ((float) event.motion.xrel /
				     kInitWindowWidth);
			float dy =  ((float) event.motion.yrel /
				     kInitWindowHeight);

			viewMatrix = glm::translate(viewMatrix,
						    glm::vec3(dx, -dy, 0.f));
			gRenderer.setViewMatrix(viewMatrix);
		}
		break;
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			int newWidth = event.window.data1;
			int newHeight = event.window.data2;

			gRenderer.windowResizeHandler(newWidth, newHeight);
		}
		break;

	case SDL_MOUSEWHEEL:
		if (event.wheel.y > 0) {
			viewMatrix = glm::scale(viewMatrix, glm::vec3(1.5));
			gRenderer.setViewMatrix(viewMatrix);
		} else {
			viewMatrix = glm::scale(viewMatrix, glm::vec3(0.5));
			gRenderer.setViewMatrix(viewMatrix);
		}
		break;
	}
}

static void
update()
{
	testInst2.setModelMatrix(glm::rotate(testInst2.getModelMatrix(),
					     0.02f,
					     glm::vec3(0.f, 1.0f, 0.f)));
}

static void
render()
{
	gRenderer.setClearColor(0.3, 0.3, 0.3, 1.f);
	gRenderer.clear();

	/*
	 * Do what i want here
	 */
	gRenderer.setDrawColor(0.2, 1.f, 0.f);
	testInst.render(gRenderer);
	testInst2.render(gRenderer);

	gRenderer.present();
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

	gRenderer.setRenderLogicalSize(250, 250);
	gRenderer.windowResizeHandler(kInitWindowWidth, kInitWindowHeight);
	gRenderer.setViewMatrix(viewMatrix);

	testInst.load(gRenderer, "cube.obj");
	testInst2.load(gRenderer, "cube.obj");
	testInst2.setModelMatrix(glm::translate(glm::mat4(1.0),
						glm::vec3(10.f, 0.f, 0.f)));

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
