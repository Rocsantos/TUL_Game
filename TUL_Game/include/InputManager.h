#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#include <vector>

#include "GeometricForms.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define SPACE_KEY SDLK_SPACE
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class InputManager
{
private:
	static InputManager* instance;
	bool mouseState[6],
		quitRequested;
	int mouseUpdate[6],
		mouseX, mouseY;
	unsigned int updateCounter;
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, unsigned int> keyUpdate;
	InputManager();
	~InputManager();
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);

	int GetMouseX() const;
	int GetMouseY() const;
	Vec2 GetMousePos();
	Vec2 GetWorldMousePos();

	bool QuitRequested() const;
	static InputManager& GetInstance();
};

#endif
