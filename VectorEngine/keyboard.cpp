#include "keyboard.hpp"

KEYPRESS::KEYPRESS() : down(false), up(false), isHold(false), lastState(false), state(false) {}

void KEYPRESS::update()
{
	if (state != lastState) {
		down = state;
		up = !state;
		isHold = false;
		lastState = state;
		return;
	}
	lastState = state;
	if (state) {
		if (isHold) {
			return;
		}
		if (down) {
			down = false;
			isHold = true;
			return;
		}
		return;
	}
	else {
		if (up) {
			up = false;
			return;
		}
		return;
	}
}

void MOUSE::update()
{
	int xd = x;
	int yd = y;
	GetMousePoint(&x, &y);
	uint8_t state = GetMouseInput();
	xdir = xd * mouseSensitivity;
	ydir = yd * mouseSensitivity;
	left.state = (state & MOUSE_INPUT_LEFT) != 0;
	middle.state = (state & MOUSE_INPUT_MIDDLE) != 0;
	right.state = (state & MOUSE_INPUT_RIGHT) != 0;
	left.update();
	middle.update();
	right.update();
}

void updateKeys(std::map<int, KEYPRESS>& keys)
{
	std::vector<char> keyAll(256, 0);
	GetHitKeyStateAll(keyAll.data());
	for (int i = 0; i < keyAll.size(); i++) {
		keys[i].state = keyAll[i];
		keys[i].update();
	}
}

bool isAnyKeyDown(std::map<int, KEYPRESS>& keys)
{
	for (auto [_, key] : keys) {
		if (key.down) return true;
	}
	return false;
}
