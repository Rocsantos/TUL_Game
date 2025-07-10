#include "Animator.h"

#include "Game.h"
#include "GameObject.h"

#include <vector>
#include <unordered_map>

Animator::Animator(GameObject& go):
	Component(go),
	frameStart(0),
	frameEnd(0),
	currentFrame(0),
	frameTime(0.0) {}

void Animator::Update(float dt)
{
	if (frameTime == 0)
	{
		if(currentFrame != frameStart)
		{
			currentFrame = frameStart;
		}
		SpriteRenderer* sprite = (SpriteRenderer*) associated.GetComponent("SpriteRenderer");
		if(sprite != nullptr)
		{
			sprite->SetFrame(currentFrame, flip);
		}
		return;
	}

	timer.Update(dt);
	if(timer.Get() >= frameTime/1000.0f)
	{
		currentFrame++;
		if(currentFrame >= frameEnd or currentFrame < frameStart)
		{
			currentFrame = frameStart;
		}
		SpriteRenderer* sprite = (SpriteRenderer*) associated.GetComponent("SpriteRenderer");
		if(sprite != nullptr)
		{
			sprite->SetFrame(currentFrame, flip);
		}
		timer.Restart();
	}
}

bool Animator::Is(std::string type)
{
	return type == "Animator";
}

void Animator::SetAnimation(std::string name, SDL_RendererFlip _flip)
{
	auto animation = animations.find(name);
	if(animation != animations.end())
	{
		frameStart = animations[name].frameStart;
		frameEnd = animations[name].frameEnd;
		frameTime = animations[name].frameTime;
		flip = (_flip != SDL_FLIP_NONE? _flip: animations[name].flip);
	}
}

void Animator::AddAnimation(std::string name, Animation animation)
{
	if(animations.find(name) != animations.end())
		return;
	animations[name] = animation;
}
