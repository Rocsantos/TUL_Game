#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "GameObject.h"
#include "Music.h"
#include "Timer.h"

#include <string>

class Zombie: public Component
{
private:
	int hitpoints;
	Sound deathSound;
	bool hit;
	Sound hitSound;
	Timer hitTimer;
public:
	Zombie(GameObject& associated);
	void Update(float dt);
	bool Is(std::string type);
	void Damage(int damage);
	void NotifyCollision(GameObject& other);
};

class Wave
{
public:
	int zombies;
	float cooldown;
	Wave(int zombies, float cooldown) : zombies(zombies), cooldown(cooldown) {}
};

class WaveSpawner: public Component
{
private:
	int zombieCounter, currentWave;
	std::vector<Wave> waves;
	Timer zombieCooldown;

public:
	WaveSpawner(GameObject& associated);
	void Start() {}
	void Update(float dt);
	bool Is(std::string type);
	void NotifyCollision(GameObject& other);
	void Render() {}
};

#endif
