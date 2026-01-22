#pragma once

#include "objects.hpp"

VECTOR_GRAPH playerGraph(
	{
		VECTOR2f(0, -4/3.0),
		VECTOR2f(-0.5, 2/3.0),
		VECTOR2f(0.5, 2/3.0)
	},
	{
		{0, 1},
		{0, 2},
		{1, 2}
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
		{0, 1},
		{1, 2},
		{2, 3},
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
		{0,1},
		{1,2},
		{2,3},
		{3,0}
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
		VECTOR2f(1.5, -2.5),
		VECTOR2f(-0.5, -3.5),
		VECTOR2f(-3.5, -1.5),
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
		{0,1},
		{1,2},
		{2,3},
		{3,4},
		{4,5},
		{5,6},
		{6,7},
		{7,8},
		{8,0},

		{9,10},
		{10,11},
		{11,12},
		{12, 9},

		{13,14},
		{14,15},
		{15,16},
		{16,17},
		{17,13}
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
		{0,1},
		{1,2},
		{2,3},
		{3,4},
		{4,5},

		{6,7},
		{7,8},
		{8,9},

		{10,11},
		{11,12},
		{12,13},
		{13,10},

		{14,15},
		{15,16},
		{16,17},
		{17,18},
		{18,19},

		{20, 21},
		{21, 22},
		{22, 23},

		{24, 25},
	},
	0
);

VECTOR_GRAPH lineGraph(
	{
		VECTOR2f(-1, 0),
		VECTOR2f(1, 0),
	},
	{
		{0, 1},
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
			{0,1},
			{1,2},
			{2,3},
			{3,0}
		},
		0
	),
	VECTOR_GRAPH(
		{
			VECTOR2f(0, -2),
			VECTOR2f(0, 2),
		},
		{
			{0,1},
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
			{0,1},
			{1,2},
			{2,3},
			{3,4},
			{4,5},
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
			{0,1},
			{1,2},
			{2,3},
			{4,5},
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
			{0,1},
			{1,2},
			{3,4},
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
			{0,1},
			{1,2},
			{2,3},
			{3,4},
			{4,5},
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
			{0,1},
			{1,2},
			{2,3},
			{3,4},
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
			{0,1},
			{1,2},
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
			{0,1},
			{1,2},
			{2,3},
			{3,0},
			{4,5},
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
			{0,1},
			{1,2},
			{2,3},
			{3,4},
		},
		0
	),
};