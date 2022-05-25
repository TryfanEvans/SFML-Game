#include "Melee.h"

#ifndef Ranged_H
	#define Ranged_H
class Ranged : public Enemy
{
public:
	std::string type = "Ranged";
	Pellet pellet;
	float const cooldown_duration = 3;
	float cooldown_progress = 0;
	sf::Texture texture;

	float tx;
	float ty;

	Ranged();
	void update(double dt, float player_x, float player_y, Map* map, bool& alive);
	void render(sf::RenderTarget* target);
};

#endif