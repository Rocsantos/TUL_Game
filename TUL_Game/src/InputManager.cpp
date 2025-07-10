#include "InputManager.h"

#define INCLUDE_SDL
#include "SDL_include.h"

#include "TileMap.h"
#include "Game.h"

#define KEYSYM event.key.keysym.sym
#define BUTTON event.button.button

InputManager* InputManager::instance = nullptr;

InputManager& InputManager::GetInstance()
{
	if(not instance)
		instance = new InputManager();
	return *instance;
}

InputManager::InputManager(): mouseX(0), mouseY(0), updateCounter(0)
{
	for(int i=0; i<6; i++)
	{
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}
}

InputManager::~InputManager()
{
	delete instance;
	instance = nullptr;
}

void InputManager::Update()
{
	updateCounter++; // Incrementa o contador antes de processar os eventos
	quitRequested = false; // Reseta a flag de quitRequested
	SDL_GetMouseState(&mouseX, &mouseY); // Atualiza a posição do mouse

	SDL_Event event;
	SDL_PollEvent(&event); // Pega o evento atual

	switch(event.type)
	{
		case SDL_QUIT:
			quitRequested = true;
			break;
		case SDL_KEYDOWN:
			if(not event.key.repeat)
			{
				keyState[KEYSYM] = true;
				keyUpdate[KEYSYM] = updateCounter;
			}
			break;
		case SDL_KEYUP:
			keyState[KEYSYM] = false;
			keyUpdate[KEYSYM] = updateCounter;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseState[BUTTON] = true;
			mouseUpdate[BUTTON] = updateCounter;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseState[BUTTON] = false;
			mouseUpdate[BUTTON] = updateCounter;
			break;
	}
}

bool InputManager::KeyPress(int key)
{
	return keyState[key] and (keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key)
{
	return not keyState[key] and (keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key)
{
	return keyState[key];
}

bool InputManager::MousePress(int button)
{
	return mouseState[button] and mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button)
{
	return not mouseState[button] and mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button)
{
	return mouseState[button];
}

int InputManager::GetMouseX() const
{
	return mouseX;
}

int InputManager::GetMouseY() const
{
	return mouseY;
}

Vec2 InputManager::GetMousePos()
{
	return Vec2(mouseX, mouseY);
}

Vec2 InputManager::GetWorldMousePos()
{
	return GetMousePos() + Camera::pos;
}

bool InputManager::QuitRequested() const
{
	return quitRequested;
}
