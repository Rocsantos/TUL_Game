#include "TileMap.h"

#include "Game.h"
#include "InputManager.h"

#include <fstream>

/******************************************************************************
 * 
 * TileSet Class Definiton
 * 
*******************************************************************************/

TileSet::TileSet(std::string file, int _tileWidth, int _tileHeight):
	tileWidth(_tileWidth), tileHeight(_tileHeight)
{
	tileSet.Open(file);
	int frameCountW = tileSet.GetWidth() / tileWidth;
	int frameCountH = tileSet.GetHeight() / tileHeight;
	tileSet.SetFrameCount(frameCountW, frameCountH);
	tileCount = frameCountW * frameCountH;
}

void TileSet::RenderTile(unsigned int index, int x, int y)
{
	if(index < tileCount)
	{
		tileSet.SetFrame(index);
		tileSet.Render(x, y, tileWidth, tileHeight);
	}
}

int TileSet::GetTileWidth()
{
	return tileWidth;
}

int TileSet::GetTileHeight()
{
	return tileHeight;
}

/******************************************************************************
 * 
 * TileMap Class Definiton
 * 
*******************************************************************************/

TileMap::TileMap(GameObject& associated, std::string file, TileSet* _tileSet) :
	Component(associated)
{
	Load(file);
	SetTileSet(_tileSet);
}
void TileMap::Load(std::string file)
{
	int tile;
	char comma;
	std::ifstream mapFile(file);
	if(not mapFile.is_open())
	{
		Game::CrashWithError("Não foi possível carregar o mapa: ", file);
	}

	mapFile >> mapWidth >> comma
					>> mapHeight >> comma
					>> mapDepth >> comma;
	while(not mapFile.eof())
	{
		mapFile >> tile;
		tileMatrix.push_back(tile);
		if (mapFile.peek() == ',')
			mapFile >> comma;
	}

	mapFile.close();
}

void TileMap::SetTileSet(TileSet* _tileSet)
{
	tileSet.reset(_tileSet);
}

int& TileMap::At(int x, int y, int z)
{
	if(x < 0 || y < 0 || x >= mapWidth || y >= mapHeight)
	{
		return tileMatrix[0];
	}
	return tileMatrix[x + y * mapWidth + z * mapWidth * mapHeight];
}

void TileMap::Render()
{
	for(u_int i = 0; i < mapDepth; i++)
	{
		RenderLayer(i);
	}
}

void TileMap::RenderLayer(int layer)
{
	for(int y = 0; y < mapHeight; y++)
	{
		for(int x = 0; x < mapWidth; x++)
		{
			int tileIndex = At(x, y, layer);
			if(tileIndex >= 0)
			{
				Rect box = associated.box;
				float posX = box.x + x * tileSet->GetTileWidth();
				float posY = box.y + y * tileSet->GetTileHeight();
				tileSet->RenderTile(tileIndex, posX, posY);
			}
		}
	}
}

int TileMap::GetWidth()
{
	return mapWidth;
}

int TileMap::GetHeight()
{
	return mapHeight;
}

int TileMap::GetDepth()
{
	return mapDepth;
}

bool TileMap::Is(std::string type)
{
	return type == "TileMap";
}

/******************************************************************************
 * 
 * Camera Class Definiton
 * 
*******************************************************************************/
Vec2 Camera::pos(0, 0);
Vec2 Camera::speed(500, 500);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject& newFocus)
{
	focus = &newFocus;
}

void Camera::Unfollow()
{
	focus = nullptr;
}

void Camera::Update(float dt)
{
	if(focus != nullptr)
	{
		Rect box = focus->box;
		pos = Vec2(box.x, box.y) - (Vec2(600 - box.w, 450 - box.h));
		if(pos.x < 0) pos.x = 0;
		if(pos.x > 600) pos.x = 600;
		if(pos.y < 0) pos.y = 0;
		if(pos.y > 180) pos.y = 180;
	}
	else
	{
		InputManager& input = InputManager::GetInstance();
		int dx(0), dy(0);
		if(input.IsKeyDown(LEFT_ARROW_KEY))	dx -= speed.x * dt;
		if(input.IsKeyDown(RIGHT_ARROW_KEY))dx += speed.x * dt;
		if(input.IsKeyDown(UP_ARROW_KEY))	dy -= speed.y * dt;
		if(input.IsKeyDown(DOWN_ARROW_KEY))	dy += speed.y * dt;

		pos.x += dx;
		pos.y += dy;
		if (pos.x < 0) pos.x = 0;
		if (pos.y < 0) pos.y = 0;
		if (pos.x > 1200) pos.x = 1200;
		if (pos.y > 1650) pos.y = 1650;
	}
}
