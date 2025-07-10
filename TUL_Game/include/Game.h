#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <string>
#include <stack>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"

class Game
{
private:
	static Game* instance;
	float dt;
	unsigned int frameStart;

	State* storedState;
	std::stack<std::unique_ptr<State>> stateStack;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Game(std::string title, int width, int height);
	~Game();
	void CalculateDeltaTime();
public:
	static void CrashWithError(std::string msg, std::string error);
	static Game& GetInstance();
	static SDL_Renderer* GetRenderer();
	static State& GetCurrentState();
	void Push(State* state);
	void Run();
	float GetDeltaTime();
};

#endif
