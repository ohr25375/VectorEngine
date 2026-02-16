#pragma once

#include "objects.hpp"

VECTOR_GRAPH playerGraph(
	{
		VECTOR2f(0, -4/3.0),
		VECTOR2f(-0.5, 2/3.0),
		VECTOR2f(0.5, 2/3.0)
	},
	{
		{{0, 1}, 1},
		{{0, 2}, 1},
		{{1, 2}, 1}
	},
	0.2577
);

VECTOR_GRAPH exhaustGraph(
	{
		VECTOR2f(-0.75, 0),
		VECTOR2f(-0.5, 1),
		VECTOR2f(-0.25, 0),
		VECTOR2f(0, 2),
	},
	{
		{{0, 1}, 1},
		{{1, 2}, 1},
		{{2, 3}, 1},
	},
	0
);

VECTOR_GRAPH bulletGraph(
	{
		VECTOR2f(0, -1),
		VECTOR2f(1, 0),
		VECTOR2f(0, 1),
		VECTOR2f(-1, 0)
	},
	{
		{{0,1}, 3},
		{{1,2}, 3},
		{{2,3}, 3},
		{{3,0}, 3}
	},
	1
);

VECTOR_GRAPH largeAsteroidGraph(
	{
		VECTOR2f(-3.5, 1.5),
		VECTOR2f(-2.5, 2),
		VECTOR2f(-1.5, 3.5),
		VECTOR2f(2, 3),
		VECTOR2f(3.5, 0),
		VECTOR2f(2.5, -2.5),
		//VECTOR2f(0, 0),
		VECTOR2f(1.5, -2.5),
		VECTOR2f(-0.5, -3.5),
		VECTOR2f(-3.5, -1.5),
	},
	{
		{{0,1}, 1},
		{{1,2}, 1},
		{{2,3}, 1},
		{{3,4}, 1},
		{{4,5}, 1},
		{{5,6}, 1},
		{{6,7}, 1},
		{{7,8}, 1},
		{{8,0}, 1},
	},
	3.5
);

VECTOR_GRAPH asteroidDoodad(
	{
		VECTOR2f(-2, -1.5),
		VECTOR2f(-1.5, -1),
		VECTOR2f(-2, -0.5),
		VECTOR2f(-2.5, -1),
		VECTOR2f(1, 0.5),
		VECTOR2f(2, 1.5),
		VECTOR2f(1.5, 2.5),
		VECTOR2f(0.5, 2.5),
		VECTOR2f(-0.5, 1.5)
	},
	{
		{{0,1}, 1},
		{{1,2}, 1},
		{{2,3}, 1},
		{{3, 0}, 1},

		{{4,5}, 1},
		{{5,6}, 1},
		{{6,7}, 1},
		{{7,8}, 1},
		{{8,4}, 1}
	},
	3.5
);

VECTOR_GRAPH scoreGraph(
	{
		VECTOR2f(-6.5, -2),
		VECTOR2f(-9.5, -2),
		VECTOR2f(-9.5, 0),
		VECTOR2f(-6.5, 0),
		VECTOR2f(-6.5, 2),
		VECTOR2f(-9.5, 2),

		VECTOR2f(-2.5, -2),
		VECTOR2f(-5.5, -2),
		VECTOR2f(-5.5, 2),
		VECTOR2f(-2.5, 2),

		VECTOR2f(1.5, -2),
		VECTOR2f(-1.5, -2),
		VECTOR2f(-1.5, 2),
		VECTOR2f(1.5, 2),

		VECTOR2f(2.5, 2),
		VECTOR2f(2.5, -2),
		VECTOR2f(5.5, -2),
		VECTOR2f(5.5, 0),
		VECTOR2f(2.5, 0),
		VECTOR2f(5.5, 2),

		VECTOR2f(9.5, -2),
		VECTOR2f(6.5, -2),
		VECTOR2f(6.5, 2),
		VECTOR2f(9.5, 2),

		VECTOR2f(6.5, 0),
		VECTOR2f(9.5, 0),
	},
	{
		{{0,1}, 1},
		{{1,2}, 1},
		{{2,3}, 1},
		{{3,4}, 1},
		{{4,5}, 1},

		{{6,7}, 1},
		{{7,8}, 1},
		{{8,9}, 1},

		{{10,11}, 1},
		{{11,12}, 1},
		{{12,13}, 1},
		{{13,10}, 1},

		{{14,15}, 1},
		{{15,16}, 1},
		{{16,17}, 1},
		{{17,18}, 1},
		{{18,19}, 1},

		{{20, 21}, 1},
		{{21, 22}, 1},
		{{22, 23}, 1},

		{{24, 25}, 1},
	},
	0
);

VECTOR_GRAPH lineGraph(
	{
		VECTOR2f(-1, 0),
		VECTOR2f(1, 0),
	},
	{
		{{0, 1}, 1},
	},
	0
);

std::vector<VECTOR_GRAPH> numberGraphs = {
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 2),
			VECTOR2f(-1.5, 2)
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{3,0}, 1}
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(0, -2),
			VECTOR2f(0, 2),
		},
		{
			{{0,1}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 0),
			VECTOR2f(-1.5, 0),
			VECTOR2f(-1.5, 2),
			VECTOR2f(1.5, 2),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{3,4}, 1},
			{{4,5}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 2),
			VECTOR2f(-1.5, 2),
			VECTOR2f(-0.5, 0),
			VECTOR2f(1.5, 0),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{4,5}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(-1.5, 0),
			VECTOR2f(1.5, 0),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 2),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{3,4}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(1.5, -2),
			VECTOR2f(-1.5, -2),
			VECTOR2f(-1.5, 0),
			VECTOR2f(1.5, 0),
			VECTOR2f(1.5, 2),
			VECTOR2f(-1.5, 2),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{3,4}, 1},
			{{4,5}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(-1.5, 2),
			VECTOR2f(1.5, 2),
			VECTOR2f(1.5, 0),
			VECTOR2f(-1.5, 0),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{3,4}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 2),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(-1.5, -2),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 2),
			VECTOR2f(-1.5, 2),
			VECTOR2f(-1.5, 0),
			VECTOR2f(1.5, 0),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{3,0}, 1},
			{{4,5}, 1},
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(1.5, 0),
			VECTOR2f(-1.5, 0),
			VECTOR2f(-1.5, -2),
			VECTOR2f(1.5, -2),
			VECTOR2f(1.5, 2),
		},
		{
			{{0,1}, 1},
			{{1,2}, 1},
			{{2,3}, 1},
			{{3,4}, 1},
		},
		0
	),
};