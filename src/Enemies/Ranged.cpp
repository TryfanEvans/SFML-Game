#include "Enemy.h"

Ranged::Ranged(Map* map, int x, int y) :
	Enemy("Ranged"),
	pellet(map)
{
	speed = 40;
	charge_duration = 0.6;
	//Makes me think, should the enemies array be upgraded into a complete class instead of just an std::vector? A convient place to store textures
	//In fact, I'll do exactly that with the animation update, since it's kind of weird refactoring this and then deleting it
	if (!texture.loadFromFile("content/lemon.png"))
	{
		std::cout << "failed to load texture";
	}
	this->map = map;
	sprite.setOrigin(16, 16);
	sprite.setTexture(texture);
	setGridPosition(x, y);
}

void Ranged::update(double dt, float player_x, float player_y, bool& dead)
{
	if (pellet.active)
	{
		pellet.launch(tx, ty, 1600, dt);

		if (contact(player_x, player_y))
		{
			std::cout << "shot the player, gosh!";
			dead = true;
		}

		if ((pellet.resolveCollision() && !pellet.contact(x, y)) || (pellet.vx == 0 && pellet.vy == 0))
		{
			pellet.active = false;
		}
		if (getObstructed(tx, ty))
		{
			state = "pathfinding";
		}
	}

	if (state == "pathfinding")
	{
		if (getObstructed(player_x, player_y))
		{
			pathfinding(dt);
		}
		else if (cooldown_progress > cooldown_duration)
		{
			charge_progress = 0;
			cooldown_progress = 0;
			pellet.stored = false;
			pellet.setPosition(x, y);
			pellet.active = true;
			pellet.charge_progress = 0;
		}
		else if (cooldown_progress < cooldown_duration - 0.5)
		{
			tx = player_x;
			ty = player_y;
		}
		cooldown_progress += dt;
		if (!pellet.stored)
		{
			launch(tx, ty, -50, dt);
		}
	}
	else if (state == "stunned")
	{
		stunned_progress += dt;
		if (stunned_progress > stunned_duration)
		{
			stunned_progress = 0;
			state = "pathfinding";
		}
	}

	this->resolveCollision();
	if (state == "passive")
	{
		if (getDistance(player_x, player_y) < 220 && !getObstructed(player_x, player_y))
		{
			state = "pathfinding";
		};
	}
	x += vx;
	y += vy;
}

void Ranged::render(sf::RenderTarget* target)
{
	sprite.setPosition(x, y);
	if (state == "stunned")
	{
		sprite.setColor(sf::Color(100, 100, 100));
	}
	else
	{
		sprite.setColor(sf::Color(255, 255, 255));
	}
	target->draw(sprite);
	pellet.render(target);
}