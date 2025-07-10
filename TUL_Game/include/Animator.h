#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <vector>
#include <unordered_map>

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Animation
{
public:
	int frameStart,
			frameEnd,
			frameTime;
	SDL_RendererFlip flip;
	Animation() : frameStart(0), frameEnd(0), frameTime(0), flip(SDL_FLIP_NONE) {}
	Animation(int fStart, int fEnd, int fTime, SDL_RendererFlip _flip=SDL_FLIP_NONE) : frameStart(fStart), frameEnd(fEnd), frameTime(fTime), flip(_flip) {}
};

class Animator : public Component
{
private:
	std::unordered_map<std::string, Animation> animations;
	int frameStart,
			frameEnd,
			currentFrame;
	float frameTime;
	Timer timer;
	SDL_RendererFlip flip;
public:
	Animator(GameObject& go);
	void Update(float dt);
	void Render() {}
	bool Is(std::string type);
	void SetAnimation(std::string name, SDL_RendererFlip _flip=SDL_FLIP_NONE);
	void AddAnimation(std::string name, Animation animation);
};

#endif
