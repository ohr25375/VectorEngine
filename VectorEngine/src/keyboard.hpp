#pragma once

#include "DxLib.h"
#include <cstdint>
#include <map>
#include <vector>
#include <cassert>

class KEYPRESS
{
public:
	bool down : 1;
	bool up : 1;
	bool isHold : 1;
	bool state : 1;

	KEYPRESS();
	void update();
private:
	bool lastState : 1;
};

class MOUSE
{
public:
	int x, y;
	double xdir, ydir;
	double mouseSensitivity = 1.0;
	KEYPRESS left, right, middle;
	void update();

private:
	int xd, yd;
};

void updateKeys();

bool isAnyKeyDown();

KEYPRESS checkKey(int keyCode);