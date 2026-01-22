#include "objects.hpp"

VECTOR_GRAPH::VECTOR_GRAPH(std::vector<VECTOR2f> vertices, std::vector<std::pair<int, int>> edges, float radius)
{
	this->vertices = vertices;
	this->edges = edges;
	this->radius = radius;
}

VECTOR_GRAPH::VECTOR_GRAPH()
{
	this->vertices = std::vector<VECTOR2f>(0);
	this->edges = std::vector<std::pair<int, int>>(0);
	this->radius = 0;
}

OBJECT::OBJECT(VECTOR_GRAPH vectorGraph, COLOR color)
{
	this->vectorGraph = vectorGraph;
	this->rotation = 0.0;
	this->color = color;
	this->graphSize = 0;
	this->pos = VECTOR2f(0);
	this->vel = VECTOR2f(0);
}

void OBJECT::draw(bool flipX, bool flipY)
{
	VECTOR2i flipGraph = VECTOR2i(flipX ? -1 : 1, flipY ? -1 : 1);

	for (auto& [a, b] : vectorGraph.edges)
	{
		VECTOR2f ap = (vectorGraph.vertices[a] * graphSize).scale(flipGraph).rotate(rotation);
		VECTOR2f bp = (vectorGraph.vertices[b] * graphSize).scale(flipGraph).rotate(rotation);
		VECTOR2i aV = (pos + ap);
		VECTOR2i bV = (pos + bp);
		DxLibAddon::DrawLineAA(aV,bV,color);
	}
}

void OBJECT::move()
{
	pos += vel;
}

void OBJECT::wrapPosition(VECTOR2f topLeft, VECTOR2f bottomRight)
{
	VECTOR2f size = bottomRight - topLeft;
	pos -= topLeft;
	pos.x = fmod(pos.x + size.x, size.x);
	pos.y = fmod(pos.y + size.y, size.y);
	pos += topLeft;
}

float OBJECT::getRadius() const
{
	return vectorGraph.radius * graphSize;
}

bool OBJECT::isColliding(const OBJECT& other) const
{
	double distance = (pos - other.pos).magnitude();
	double rs = this->getRadius() + other.getRadius();
	return distance < rs;
}

void OBJECT::setGraph(const VECTOR_GRAPH& vectorGraph)
{
	this->vectorGraph = vectorGraph;
}

ASTEROID::ASTEROID(OBJECT obj, float rotation)
{
	this->obj = obj;
	this->obj.rotation = rotation;
	this->size = 0;
}