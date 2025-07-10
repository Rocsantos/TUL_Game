#include "Platform.h"

#include "GameObject.h"

Platform::Platform(GameObject& associated) : GameObject(associated) {}
Platform::~Platform() {}
void Platform::Start() {}
void Platform::Update(float dt) {}
void Platform::Render() {}

bool Platform::Is(std::string type)
{
	return type == "Platform";
}

void Platform::NotifyCollision(GameObject& other)
{
	
}
