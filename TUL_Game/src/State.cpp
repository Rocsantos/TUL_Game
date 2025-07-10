#include "State.h"

#include <algorithm>

State::State() : started(false), popRequested(false), quitRequested(false) {}

State::~State()
{
	objectArray.clear();
}

void State::UpdateArray(float dt)
{
	for(int i = objectArray.size()-1; i >= 0; i--)
	{
		objectArray[i]->Update(dt);
	}

	for(int i = objectArray.size()-1; i >= 0; i--)
	{
		if(objectArray[i]->IsDead())
		{
			objectArray.erase(objectArray.begin() + i);
			i--;
		}
	}
}

void State::RenderArray()
{
	for(int i = 0; i < objectArray.size(); i++)
	{
		objectArray[i]->Render();
	}
}


void State::StartArray()
{
	if(not started)
	{
		LoadAssets();
		for(int i = objectArray.size()-1; i >= 0; i--)
		{
			objectArray[i]->Start();
		}
		started = true;
	}
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go)
{
	std::shared_ptr<GameObject> goPtr(go);
    objectArray.push_back(goPtr);
	if (started)
	{
		goPtr->Start();
	}
	return std::weak_ptr<GameObject>(goPtr);
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go)
{
	for(auto& obj : objectArray)
	{
		if(obj.get() == go)
		{
			return std::weak_ptr<GameObject>(obj);
		}
	}
	return std::weak_ptr<GameObject>();
}

void State::RemoveObject(GameObject* go)
{
	for(int i = objectArray.size()-1; i >= 0; i--)
	{
		if(objectArray[i].get() == go)
		{
			objectArray.erase(objectArray.begin() + i);
			return;
		}
	}
}

bool State::PopRequested()
{
	return popRequested;
}

bool State::QuitRequested()
{
	return quitRequested;
}
