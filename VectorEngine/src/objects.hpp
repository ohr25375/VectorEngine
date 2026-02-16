#pragma once

#include <vector>
#include <random>

#include "vector2.hpp"
#include "color.hpp"
#include "DxLibAddon.hpp"

extern void setBrightness(int value);
void setGlareValue(int value);

class VECTOR_GRAPH
{
public:
	std::vector<VECTOR2f> vertices;
	std::vector<std::pair<std::pair<int, int>, float>> edges;
	float radius;

	VECTOR_GRAPH(std::vector<VECTOR2f> vertices, std::vector<std::pair<std::pair<int, int>, float>> edges, float radius);
	VECTOR_GRAPH();

private:
};

class OBJECT
{
public:
	VECTOR2f pos;
	double rotation;
	VECTOR2f vel;
	float graphSize;
	COLOR color;

	OBJECT(VECTOR_GRAPH vectorGraph = VECTOR_GRAPH(), COLOR color = COLOR(0xffffff));
	void draw(bool flipX = false, bool flipY = false) const;
	void move();
	void wrapPosition(VECTOR2f topLeft, VECTOR2f bottomRight);
	float getRadius() const;
	bool isColliding(const OBJECT& other) const;
	void setGraph(const VECTOR_GRAPH& vectorGraph);

private:
	VECTOR_GRAPH vectorGraph;
	bool collisionByRadius(const OBJECT& other) const;
	bool collisionByGraph(const OBJECT& other) const;
};

class ASTEROID
{
public:
	int size;
	OBJECT obj;

	ASTEROID(OBJECT obj = OBJECT(), float rotation = 0);

private:
};

class POINT_PARTICLE
{
public:
	bool isActive = false;
	VECTOR2f pos;
	VECTOR2f vel;
	int time = 0;
	float rotation;
	float scaleMod;
};