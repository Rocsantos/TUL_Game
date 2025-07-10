#ifndef COLLIDER_H
#define COLLIDER_H

#include "GameObject.h"
#include "GeometricForms.h"

#include <algorithm>
#include <cmath>

class Collider: public Component
{
private:
	Vec2 scale,
		offset;
public:
	Rect box;
	Collider(GameObject& associated, Vec2 scale={1, 1}, Vec2 offset={0, 0});
	void Start() {};
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetScale(Vec2 _scale);
	void SetOffset(Vec2 _offset);
	bool IsColliding (Collider* other);
};

#endif
