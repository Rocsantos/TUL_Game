#ifndef TILEMAP_H
#define TILEMAP_H

#include "Sprite.h"

#include <vector>
#include <memory>

class TileSet
{
private:
	Sprite tileSet;
	int tileWidth,
		tileHeight,
		tileCount;
public:
	TileSet(std::string file, int _tileWidth, int _tileHeight);
	void RenderTile(unsigned int index, int x, int y);
	int GetTileWidth();
	int GetTileHeight();
};

class TileMap : public Component
{
private:
	std::unique_ptr<TileSet> tileSet;
	std::vector<int> tileMatrix;
	int mapWidth,
		mapHeight,
		mapDepth;
public:
	TileMap(GameObject& associated, std::string file, TileSet* _tileSet);
	void Load(std::string file);
	void SetTileSet(TileSet* _tileSet);
	int& At(int x, int y, int z=0);
	void Render();
	void RenderLayer(int layer);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	bool Is(std::string type);
};

class Camera
{
private:
	static GameObject* focus;
public:
	static Vec2 pos, speed;
	Camera() {}
	static void Follow(GameObject& newFocus);
	static void Unfollow();
	static void Update(float dt);
};

#endif
