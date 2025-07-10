#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <vector>

#include "GeometricForms.h"

class GameObject;

class Component
{
protected:
	GameObject& associated;
public:
	Component(GameObject& go): associated(go) {}
	virtual ~Component() {}
	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual bool Is(std::string type) { return false; }
	virtual void NotifyCollision(GameObject& other) {}
};

class GameObject
{
private:
	std::vector<Component *> components;
	bool isDead, started;
public:
	Rect box;
	float angleDeg;
	GameObject();
	~GameObject();
	void Start();
	void Update(float dt);
	void Render();
	bool IsDead();
	void RequestDelete();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(std::string type);
	void NotifyCollision(GameObject& other);
};

#endif
