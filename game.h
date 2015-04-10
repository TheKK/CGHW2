#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <stdexcept>

#include "renderer.h"
#include "camera.h"
#include "modelInstance.h"

class Game
{
public:
	Game(int argc, char* argv[]);
	~Game();

	/* Disable copy constructor since we won't need two Game */
	Game(const Game& otherGame) = delete;
	Game& operator=(const Game& otherGame) = delete;

	void execute();
private:
	SDL_Window* window_;
	SDL_GLContext glContext_;

	Camera camera_;
	Renderer renderer_;

	bool appIsRunning_;

	ModelInstance testInst_;
	ModelInstance testInst2_;

	void getOpt_(int argc, char* argv[]);
	int initSystem_();
	int initResource_();
	void quit_();
	void eventHandler_(const SDL_Event& event);
	void update_();
	void render_();
};

#endif /* GAME_H */
