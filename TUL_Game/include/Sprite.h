#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "GameObject.h"

class Sprite
{
private:
	SDL_Texture* texture;
	int width,
		height,
		frameCountW,
		frameCountH;
	SDL_Rect clipRect;
	Vec2 scale;
	SDL_RendererFlip flip;
public:
	bool cameraFollower;
	Sprite();
	Sprite(std::string file, int _frameCountW=1, int _frameCountH=1, bool cameraFollower=false);
	~Sprite();
	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, int w, int h, float angle=0);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void SetFrame(int frame);
	void SetFrameCount(int _frameCountW, int _frameCountH);
	void SetScale(float scaleX=1, float scaleY=1);
	Vec2 GetScale();
	void SetFlip(SDL_RendererFlip _flip);
};

class SpriteRenderer: public Component
{
private:
	Sprite sprite;
	float angle;
public:
	SpriteRenderer(GameObject& go);
	SpriteRenderer(GameObject& go, std::string file, int frameCountW=1, int frameCountH=1, bool cameraFollower=false);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Open(std::string);
	void SetFrameCount(int frameCountW, int frameCountH);
	void SetFrame(int frame, SDL_RendererFlip flip=SDL_FLIP_NONE);
	void SetScale(float scaleX, float scaleY);
};

#endif
