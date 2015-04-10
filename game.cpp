#include <glm/gtc/matrix_transform.hpp>

#include "game.h"

namespace {
	const int kInitWindowWidth = 800;
	const int kInitWindowHeight = 800;
}

Game::Game(int argc, char* argv[])
{
	getOpt_(argc, argv);

	if (initSystem_() || initResource_()) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", SDL_GetError());

		throw std::runtime_error("[Game] Failed while construct");
	}
}

Game::~Game()
{
	quit_();
}

void
Game::execute()
{
	SDL_Event event;

	while (appIsRunning_) {
		while (SDL_PollEvent(&event))
			eventHandler_(event);
		update_();
		render_();

		SDL_Delay(30);
	}
}

void
Game::getOpt_(int argc, char* argv[])
{
}

int
Game::initSystem_()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return -1;

	window_ = SDL_CreateWindow(
		"Hi",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		kInitWindowWidth, kInitWindowHeight,
		SDL_WINDOW_OPENGL);
	if (!window_)
		return -1;

	glContext_ = SDL_GL_CreateContext(window_);
	if (!glContext_)
		return -1;

	if (renderer_.create(window_, RENDERER_SOFTWARERENDER) < 0)
		return -1;

	return 0;
}

int
Game::initResource_()
{
	renderer_.setRenderLogicalSize(250, 250);
	renderer_.windowResizeHandler(kInitWindowWidth, kInitWindowHeight);

	testInst_.load(renderer_, "cube.obj");
	testInst2_.load(renderer_, "cube.obj");
	testInst2_.setModelMatrix(glm::translate(glm::mat4(1.0),
						glm::vec3(10.f, 0.f, 0.f)));

	return 0;
}

void
Game::quit_()
{
	SDL_Quit();

	if (window_) {
		SDL_DestroyWindow(window_);
		window_ = NULL;
	}

	SDL_GL_DeleteContext(glContext_);
}

void
Game::eventHandler_(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_QUIT:
		appIsRunning_ = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_Q:
			appIsRunning_ = false;
			break;
		case SDL_SCANCODE_A:
			camera_.offsetPosition(camera_.getLeft());
			break;
		case SDL_SCANCODE_D:
			camera_.offsetPosition(camera_.getRight());
			break;
		case SDL_SCANCODE_W:
			camera_.offsetPosition(camera_.getForward());
			break;
		case SDL_SCANCODE_S:
			camera_.offsetPosition(camera_.getBackwrad());
			break;
		default:
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		camera_.offsetOrientation(event.motion.xrel, event.motion.yrel);
		break;
	case SDL_WINDOWEVENT:
		if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
			int newWidth = event.window.data1;
			int newHeight = event.window.data2;

			renderer_.windowResizeHandler(newWidth, newHeight);
		}
		break;
	}
}

void
Game::update_()
{
	testInst2_.setModelMatrix(glm::rotate(testInst2_.getModelMatrix(),
					     0.02f,
					     glm::vec3(0.f, 1.0f, 0.f)));
}

void
Game::render_()
{
	renderer_.setClearColor(0.3, 0.3, 0.3, 1.f);
	renderer_.clear();

	renderer_.setViewMatrix(camera_.getViewMatrix());

	renderer_.setDrawColor(0.2, 1.f, 0.f);
	testInst_.render(renderer_);
	testInst2_.render(renderer_);

	renderer_.present();
}
