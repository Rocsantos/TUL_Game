#include "StageState.h"

#include <algorithm>

#include "Collider.h"
#include "Game.h"
#include "Character.h"
#include "State.h"
#include "Sprite.h"
#include "InputManager.h"

StageState::StageState() : State() {}
StageState::~StageState() {}

void StageState::LoadAssets()
{
    music.Open("assets/sfx/BGM.wav");
    music.Play(-1);

    auto bg = new GameObject();
    bg->AddComponent(new SpriteRenderer(*bg, "assets/img/Background.png", 1, 1, true));
    AddObject(bg);

	auto bg2 = new GameObject();
	bg2->AddComponent(new SpriteRenderer(*bg2, "assets/img/garden/backround.png"));
	AddObject(bg2);

	auto cloud = new GameObject();
	cloud->AddComponent(new SpriteRenderer(*cloud, "assets/img/garden/clouds.png"));
	AddObject(cloud);

	auto landscape = new GameObject();
	landscape->AddComponent(new SpriteRenderer(*landscape, "assets/img/garden/landscape.png"));
	AddObject(landscape);

	auto landscape2 = new GameObject();
	landscape2->AddComponent(new SpriteRenderer(*landscape2, "assets/img/garden/landscape2.png"));
	AddObject(landscape2);

	auto landscape3 = new GameObject();
	landscape3->AddComponent(new SpriteRenderer(*landscape3, "assets/img/garden/landscape3.png"));
	AddObject(landscape3);

	auto landscape4 = new GameObject();
	landscape4->AddComponent(new SpriteRenderer(*landscape4, "assets/img/garden/landscape4.png"));
	AddObject(landscape4);

	auto player = new GameObject();
	player->AddComponent(new Character(*player, "assets/img/Player.png"));
	player->box.x = 0;
	player->box.y = 700;
	AddObject(player);

	camera.Follow(*player);
}

void StageState::Update(float dt)
{
	InputManager &input = InputManager::GetInstance();

	camera.Update(dt);

	if(input.KeyPress(ESCAPE_KEY) or input.QuitRequested())
	{
		quitRequested = true;
	}

	std::vector<std::shared_ptr<GameObject>> objColliders;

    for(int i = objectArray.size()-1; i >= 0; i--)
    {
        GameObject* obj = objectArray[i].get();
		obj->Update(dt);

		Component* collider = obj->GetComponent("Collider");

		if(collider != nullptr)
		{
			objColliders.push_back(objectArray[i]);
		}
    }

    for(int i = objColliders.size()-1; i >= 1; i--)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			Collider* A = (Collider*)objColliders[i]->GetComponent("Collider");
			Collider* B = (Collider*)objColliders[j]->GetComponent("Collider");
			if(A->IsColliding(B))
			{
				objColliders[i]->NotifyCollision(*objColliders[j]);
				objColliders[j]->NotifyCollision(*objColliders[i]);
			}
		}
	}

	std::sort(objectArray.begin() + 5,
		objectArray.end(),
		[](const auto& a, const auto& b)
		{
			return a->box.y > b->box.y;
		}
	);
}

void StageState::Render()
{
    RenderArray();
}

void StageState::Start()
{
	StartArray();
}

void StageState::Pause() {}
void StageState::Resume() {}
