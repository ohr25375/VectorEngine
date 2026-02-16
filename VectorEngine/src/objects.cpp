#include "objects.hpp"

static int brightness = 128;
static int glare = 1;

void setBrightness(const int value)
{
	brightness = value;
}

void setGlareValue(const int value)
{
	glare = value;
}

VECTOR_GRAPH::VECTOR_GRAPH(std::vector<VECTOR2f> vertices, std::vector<std::pair<std::pair<int, int>, float>> edges, float radius)
{
	this->vertices = vertices;
	this->edges = edges;
	//this->radius = radius;
	float r = 0;
	for (auto v : vertices)
	{
		if (v.magnitude() > r)
		{
			r = v.magnitude();
		}
	}
	this->radius = r;
}

VECTOR_GRAPH::VECTOR_GRAPH()
{
	this->vertices = std::vector<VECTOR2f>(0);
	this->edges = std::vector<std::pair<std::pair<int, int>, float>>(0);
	//this->radius = 0;
	float r = 0;
	for (auto v : vertices)
	{
		if (v.magnitude() > r)
		{
			r = v.magnitude();
		}
	}
	this->radius = r;
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

void OBJECT::draw(bool flipX, bool flipY) const
{
	VECTOR2i flipGraph = VECTOR2i(flipX ? -1 : 1, flipY ? -1 : 1);

	for (auto& [edges, thickness] : vectorGraph.edges)
	{
		auto& [a, b] = edges;
		VECTOR2f ap = (vectorGraph.vertices[a] * graphSize).scale(flipGraph).rotate(rotation);
		VECTOR2f bp = (vectorGraph.vertices[b] * graphSize).scale(flipGraph).rotate(rotation);
		VECTOR2i aV = (pos + ap);
		VECTOR2i bV = (pos + bp);
		int blendValue = brightness / glare;
		SetDrawBlendMode(DX_BLENDMODE_ADD, blendValue);
		for (int i = 1; i <= glare; i++)
		{
			DxLibAddon::DrawLineAA(aV, bV, color, thickness + i);
		}
		SetDrawBlendMode(DX_BLENDMODE_ADD, brightness);
		DxLibAddon::DrawLineAA(aV, bV, color, thickness);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
	return collisionByGraph(other);
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

bool OBJECT::collisionByRadius(const OBJECT& other) const
{
	double distance = (pos - other.pos).magnitude();
	double rs = getRadius() + other.getRadius();
	return distance < rs;
}

bool OBJECT::collisionByGraph(const OBJECT& other) const
{
	if (!collisionByRadius(other)) return false;
	for (auto v : other.vectorGraph.vertices)
	{
		VECTOR2f checkingVertex = (v * other.graphSize).rotate(other.rotation) + other.pos;
		int touchingEdges = 0;

		auto filtered = vectorGraph.edges;

		filtered.erase(std::remove_if(filtered.begin(), filtered.end(), [&](const auto& n) {
			VECTOR2f v1 = vectorGraph.vertices[n.first.first].rotate(rotation) * graphSize + pos;
			VECTOR2f v2 = vectorGraph.vertices[n.first.second].rotate(rotation) * graphSize + pos;

			bool isEdgeAbove = v1.y < checkingVertex.y && v2.y < checkingVertex.y;
			bool isEdgeBelow = v1.y > checkingVertex.y && v2.y > checkingVertex.y;
			bool isEdgeLeft = v1.x < checkingVertex.x && v2.x < checkingVertex.x;

			bool isEdgeNotCrossing = isEdgeAbove || isEdgeBelow || isEdgeLeft;
			return isEdgeNotCrossing;
			}), filtered.end());
		for (auto [edges, size] : filtered)
		{
			auto [vi1, vi2] = edges;
			VECTOR2f v1 = vectorGraph.vertices[vi1].rotate(rotation) * graphSize + pos;
			VECTOR2f v2 = vectorGraph.vertices[vi2].rotate(rotation) * graphSize + pos;
			VECTOR2f edgeDir = (v2 - v1).normalized();
			VECTOR2f checkDir = (checkingVertex - v1).normalized();
			bool isIntersect = edgeDir.x > checkDir.x;

			if (isIntersect)
			{
				touchingEdges++;
			}

		}
		if ((touchingEdges & 1) != 0)
		{
			return true;
		}
	}
	return false;
}
