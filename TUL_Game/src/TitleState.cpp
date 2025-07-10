#include "TitleState.h"

#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"
#include "StageState.h"

TitleState::TitleState() : State() {}
TitleState::~TitleState() {}

void TitleState::LoadAssets()
{
	auto title_go = new GameObject();
	title_go->AddComponent(new SpriteRenderer(*title_go, "assets/img/Title.png"));
	AddObject(title_go);
}

void TitleState::Update(float dt)
{
	InputManager &input = InputManager::GetInstance();

	if (input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
	{
		popRequested = true;
	}

	if (input.IsKeyDown(SPACE_KEY))
	{
		Game::GetInstance().Push(new StageState());
	}
}

void TitleState::Render()
{
	RenderArray();
}

void TitleState::Start()
{
	StartArray();
}

void TitleState::Pause() {}
void TitleState::Resume() {}
