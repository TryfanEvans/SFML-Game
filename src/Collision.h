#include "Map.h"

#ifndef Solid_H
	#define Solid_H
class Solid
{

public:
	int contactRadius = 16;
	int tileSize;
	int speed;
	float x;
	float y;
	float getX();
	float getY();

	float vy = 0;
	float vx = 0;
	void move(Map& map);

	float getDistance(float tx, float ty);

	bool resolveCollision(Map& map);
	std::tuple<float, float> resolveCornerCollision(int ex, int ey, int tx, int ty);
	int resolveEdgeCollision(int edge, int selfPos);
	void setPosition(double x, double y, int tileSize);
	std::tuple<float, float> getGridPosition();

	double charge_duration = 0;
	double charge_progress = 0;
	void launch(float tx, float ty, double power, float dt, Map& map);
	bool contact(float tx, float ty);
};

#endif