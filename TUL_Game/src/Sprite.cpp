#include "Sprite.h"

#include <math.h>

#include "TileMap.h"
#include "Game.h"
#include "Resource.h"

/******************************************************************************
 * 
 * Sprite Class Definiton
 * 
*******************************************************************************/

Sprite::Sprite(): texture(nullptr), width(0), height(0), cameraFollower(false),
    frameCountW(1), frameCountH(1), clipRect({0, 0, 0, 0}), scale({1, 1}), flip(SDL_FLIP_NONE) {}

Sprite::Sprite(std::string file, int _frameCountW, int _frameCountH, bool cameraFollower) :
    frameCountW(_frameCountW), frameCountH(_frameCountH)
{
    Open(file);
}

Sprite::~Sprite() {}

int Sprite::GetWidth()
{
    return width / frameCountW * scale.x;
}

int Sprite::GetHeight()
{
    return height / frameCountH * scale.y;
}

bool Sprite::IsOpen()
{
    return texture != nullptr;
}

void Sprite::Open(std::string file)
{
    texture = Resource::GetImage(file);
    if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0)
    {
        Game::CrashWithError("Erro ao inicializar QueryTexture: ", SDL_GetError());
    }

    SetClip(clipRect.x, clipRect.y, GetWidth(), GetHeight());
}

void Sprite::SetClip(int x, int y, int w, int h)
{
    clipRect = {x, y, w, h};
}

void Sprite::Render(int x, int y, int w, int h, float angle)
{
	Vec2 pos(0, 0);
	if (not cameraFollower)
	{
		pos = Camera::pos;
	}
    SDL_Rect dstrect = {x - (int) pos.x, y - (int) pos.y, w, h};
    SDL_RenderCopyEx(Game::GetRenderer(), texture, &clipRect, &dstrect, angle, nullptr, flip);
}

void Sprite::SetFrame(int frame)
{
    int x = (frame % frameCountW) * (width / frameCountW),
        y = (frame / frameCountW) * (height / frameCountH);
    SetClip(x, y, width / frameCountW, height / frameCountH);
}

void Sprite::SetFrameCount(int _frameCountW, int _frameCountH)
{
    frameCountW = _frameCountW;
    frameCountH = _frameCountH;
}

void Sprite::SetScale(float scaleX, float scaleY)
{
	if (scaleX == 0)
	{
		scaleX = 1.0f;
	}
	if (scaleY == 0)
	{
		scaleY = 1.0f;
	}
	scale = Vec2(scaleX, scaleY);
}

Vec2 Sprite::GetScale()
{
	return scale;
}

void Sprite::SetFlip(SDL_RendererFlip _flip)
{
	flip = _flip;
}

/******************************************************************************
 * 
 * SpriteRenderer Class Definiton
 * 
*******************************************************************************/

SpriteRenderer::SpriteRenderer(GameObject &_associated) : Component(_associated) {}

SpriteRenderer::SpriteRenderer(GameObject &_associated, std::string file, int frameCountW, int frameCountH, bool cameraFollower) : Component(_associated)
{
	sprite.cameraFollower = cameraFollower;
    SetFrameCount(frameCountW, frameCountH);
    Open(file);
}

void SpriteRenderer::Update(float dt) {}

void SpriteRenderer::Render()
{
    Rect b = associated.box;
    sprite.Render(b.x, b.y, sprite.GetWidth(), sprite.GetHeight(), associated.angleDeg);
}

bool SpriteRenderer::Is(std::string type)
{
    return type == "SpriteRenderer";
}

void SpriteRenderer::Open(std::string file)
{
    sprite.Open(file);
    associated.box.w = sprite.GetWidth();
    associated.box.h = sprite.GetHeight();
}

void SpriteRenderer::SetFrame(int frame, SDL_RendererFlip flip)
{
	sprite.SetFlip(flip);
    sprite.SetFrame(frame);
}

void SpriteRenderer::SetFrameCount(int frameCountW, int frameCountH)
{
    sprite.SetFrameCount(frameCountW, frameCountH);
}

void SpriteRenderer::SetScale(float scaleX, float scaleY)
{
	sprite.SetScale(scaleX, scaleY);
	associated.box += Vec2(sprite.GetWidth()/-2, sprite.GetHeight()/-2);
	associated.box.w = sprite.GetWidth();
	associated.box.h = sprite.GetHeight();
}
