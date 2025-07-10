#include "GameObject.h"
#include <algorithm>

#define all(x) x.begin(), x.end()

GameObject::GameObject() : isDead(false), angleDeg(0) {}

GameObject::~GameObject()
{
	for(int i=components.size()-1; i >= 0; i--)
	{
		delete components[i];
	}
	components.clear();
}

void GameObject::Update(float dt)
{
	for(int i = components.size()-1; i >= 0; i--)
	{
		if (components[i] != nullptr)
		{
			components[i]->Update(dt);
		}
	}
}

void GameObject::Render()
{
	for(int i = components.size()-1; i >= 0; i--)
	{
		if (components[i] != nullptr)
		{
			components[i]->Render();
		}
	}
}

bool GameObject::IsDead()
{
	return isDead;
}

void GameObject::RequestDelete()
{
	isDead = true;
}

void GameObject::AddComponent(Component* cpt)
{
	components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt)
{
	auto it = std::find(all(components), cpt);
	if(it != components.end())
	{
		delete *it;
		components.erase(it);
	}
}

Component* GameObject::GetComponent(std::string type)
{
	auto it = std::find_if(all(components),
		[&type](Component* cpt) { return cpt->Is(type); });

	if(it != components.end())
	{
		return *it;
	}

	return nullptr;
}

void GameObject::Start()
{
	for(auto& cpt : components)
	{
		if (cpt != nullptr)
		{
			cpt->Start();
		}
		started = true;
	}
}

void GameObject::NotifyCollision(GameObject& other)
{
	for(auto& cpt : components)
	{
		if (cpt != nullptr)
		{
			cpt->NotifyCollision(other);
		}
	}
}
