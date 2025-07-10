#include "Character.h"

#include "Animator.h"
#include "Collider.h"
#include "Game.h"
#include "InputManager.h"
#include "Sprite.h"
#include "TileMap.h"

#define HORIZONTAL 0
#define VERTICAL 1

Character* Character::player = nullptr;

/******************************************************************************
 * 
 * Character Class Definiton
 * 
*******************************************************************************/

Character::Character(GameObject& associated, std::string sprite) :
	Component(associated), speed(500, 500), linearSpeed(0), hp(10)
{
	SpriteRenderer *spriteRenderer = new SpriteRenderer(associated, sprite, 10, 4);
	spriteRenderer->SetScale(3.0f, 3.0f);
	associated.AddComponent(spriteRenderer);

	Animator *animator = new Animator(associated);
	animator->AddAnimation("char_walking", Animation(10, 17, 64));
	animator->AddAnimation("char_idle", Animation(0, 9, 128));
	animator->AddAnimation("char_jumping", Animation(20, 25, 128));
	animator->AddAnimation("char_dead", Animation(30, 39, 256));

	associated.AddComponent(animator);

	associated.AddComponent(new PlayerController(associated));

	associated.AddComponent(new Collider(associated));

	if(player == nullptr)
	{
		player = this;
	}
}

Character::~Character()
{
	if(this == player)
	{
		player = nullptr;
	}
}

void Character::Start()
{
}

void Character::Update(float dt)
{
	deathTimer.Update(dt);
	cooldownTimer.Update(dt);
	Animator *animator = (Animator *)associated.GetComponent("Animator");

	if(jumping)
	{
		if(cooldownTimer.Get() < 0.6)
			associated.box.y -= 300 * dt;

		else if(cooldownTimer.Get() < 1.2)
			associated.box.y += 300 * dt;

		else
			jumping = false;

	}

	if(hp <= 0)
	{
		if(deathTimer.Get() == dt)
		{
			animator->SetAnimation("char_dead");
			if (player == this)
			{
				Camera::Unfollow();
				player = nullptr;
			}
			Camera::Unfollow();
		}
		else if(deathTimer.Get() > 5.0f)
		{
			associated.RequestDelete();
		}
	}
	else
	{
		if(taskQueue.size() != 0)
		{
			Command task = taskQueue.front();
			if(task.type == Command::MOVE)
			{
				if(task.pos.x >= 0)
				{
					animator->SetAnimation("char_walking");
				}
				else
				{
					animator->SetAnimation("char_walking", SDL_FLIP_HORIZONTAL);
				}
				if(task.pos.y < 0)
				{
					associated.box += task.pos * (200.0f * dt);
					animator->SetAnimation("char_jumping");
					jumping = true;
				}
				associated.box += task.pos * (100.0f * dt);
				taskQueue.pop();
			}
			else if (task.type == Command::SHOOT)
			{
				if(not jumping)
				{
					jumping = true;
					cooldownTimer.Restart();
				}
			}
		}
		else
		{
			if(not jumping)
			{
				animator->SetAnimation("char_idle");
			}
			else
			{
				animator->SetAnimation("char_jumping");
			}
		}
	}
}

bool Character::Is(std::string type)
{
	return type == "Character";
}

void Character::Issue(Command task)
{
	taskQueue.push(task);
}

void Character::NotifyCollision(GameObject& other)
{
	if(cooldownTimer.Get() > 0.5f)
	{
		hp--;
		cooldownTimer.Restart();
		if (not hp)
		{
			deathTimer.Restart();
		}
	}
	return;
}

Vec2 Character::GetPos()
{
	return associated.box.Center();
}

/******************************************************************************
 * 
 * PlayerController Class Definiton
 * 
*******************************************************************************/

PlayerController::PlayerController(GameObject& go) : Component(go) {}

void PlayerController::Update(float dt)
{
	InputManager& input = InputManager::GetInstance();
	int keys[4] = { W_KEY, S_KEY, A_KEY, D_KEY };
	int move[2] = { 0, 0 };
	for(int key: keys)
	{
		if(not input.IsKeyDown(key))
		{
			continue;
		}
		switch (key)
		{
		case A_KEY:
			move[HORIZONTAL]--;
			break;
		case D_KEY:
			move[HORIZONTAL]++;
			break;
		case W_KEY:
			move[VERTICAL]--;
			break;
		case S_KEY:
			move[VERTICAL]++;
			break;
		default:
			break;
		}
	}

	Character* character = (Character*) associated.GetComponent("Character");
	if(move[0] or move[1])
	{
		Command moveCommand(Command::MOVE, move[HORIZONTAL], move[VERTICAL]);
		character->Issue(moveCommand);
	}

	if(input.KeyPress(SPACE_KEY))
	{
		Command jump(Command::SHOOT, 0, 0);
		character->Issue(jump);
	}
}

bool PlayerController::Is(std::string type)
{
	return type == "PlayerController";
}
