#ifndef STATE_H
#define STATE_H

#include <vector>
#include <memory>

#include "GameObject.h"

class State
{
protected:
	bool started;
	bool popRequested;
	bool quitRequested;
	std::vector<std::shared_ptr<GameObject>> objectArray;
	void StartArray();
	void UpdateArray(float dt);
	void RenderArray();

public:
	State();
	virtual ~State();
	virtual void LoadAssets() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Start() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	std::weak_ptr<GameObject> AddObject(GameObject* go);
	std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
	void RemoveObject(GameObject* go);

	bool PopRequested();
	bool QuitRequested();
};

#endif
