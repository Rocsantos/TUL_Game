#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <memory>
#include <vector>

#include "GameObject.h"
#include "Music.h"
#include "TileMap.h"
#include "State.h"

class StageState: public State
{
private:
	Music music;
	TileSet* tileSet;
public:
	Camera camera;
	StageState();
	~StageState();
	bool QuitRequested();
	void LoadAssets();
	void Update(float dt);
	void Render();
	void Start();
	void Pause();
	void Resume();
};

#endif
