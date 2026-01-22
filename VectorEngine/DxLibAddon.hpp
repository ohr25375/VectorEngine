#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
#include <cstdint>

#include "DxLib.h"
#include "vector2.hpp"
#include "color.hpp"

#define FPS 60
#define DEG2RAD (M_PI / 180)
#define RAD2DEG (180 / M_PI)

class Graph;

namespace DxLibAddon
{
	int DrawString(VECTOR2i pos, std::string text, COLOR color, int size, bool isCentered = false);
	int DrawExtendGraph(VECTOR2i pos, VECTOR2i size, Graph graph, int transFlag);
	int DrawLine(VECTOR2i pos1, VECTOR2i pos2, COLOR color, int lineThickness = 1);
	int DrawLineAA(VECTOR2i pos1, VECTOR2i pos2, COLOR color, int lineThickness = 1);
	bool doDelay();
}

class Graph {
public:
	int graph;
	VECTOR2i bounds;
	int& width = bounds.x;
	int& height = bounds.y;

	Graph();
	Graph(std::string imagePath, int atlasCountX = 1, int atlasCountY = 1);
	Graph(int graph);

private:
	void InitializeGraph(int graph, int atlasCountX = 1, int atlasCountY = 1);
};