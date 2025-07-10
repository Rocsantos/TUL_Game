#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Music.h"
#include "Timer.h"

#include <memory>
#include <queue>
#include <string>

class Command{
public:
	enum CommandType { MOVE, SHOOT };
	CommandType type;
	Vec2 pos;
	Command(CommandType type, float x, float y) : type(type), pos(Vec2(x, y)) {}
};

class Character : public Component
{
private:
	std::weak_ptr<GameObject> gun;
	std::queue<Command> taskQueue;
	bool jumping;
	Vec2 speed;
	float linearSpeed;
	int hp;
	Timer deathTimer, cooldownTimer;
public:
	static Character* player;
	Character(GameObject& associated, std::string sprite);
	~Character();
	void Start();
	void Update(float dt);
	void Render() {}
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
	void Issue(Command task);
	Vec2 GetPos();
};

class Gun : public Component
{
private:
	Sound shootSound, reloadSound;
	int cooldown;
	Timer cdTimer;
	std::weak_ptr<GameObject> character;
	float angle;
public:
	Gun(GameObject& associated, std::weak_ptr<GameObject> character);
	~Gun() {}
	void Start() {}
	void Update(float dt);
	void Render() {}
	bool Is(std::string type);
	void Shoot(Vec2 target);
};

class PlayerController : public Component
{
public:
	PlayerController(GameObject& associated);
	void Start() {}
	void Update(float dt);
	void Render() {}
	bool Is(std::string type);
};

class Bullet : public Component
{
private:
	Vec2 speed;
	float distanceLeft;
	int damage;
	bool targetsPlayer;
public:
	Bullet(GameObject& associated, float angle, float speed, int damage, int MaxDistance, bool targetsPlayer = false);
	~Bullet() {}
	void Start() {}
	void Update(float dt);
	void Render() {}
	bool Is(std::string type);
	int GetDamage() const;
	void NotifyCollision(GameObject& other);
};
#endif
