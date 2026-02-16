#pragma once

#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <map>
#include <numeric>
#include <format>

#include "vector2.hpp"
#include "color.hpp"
#include "DxLibAddon.hpp"
#include "keyboard.hpp"
#include "objects.hpp"
#include "entities.hpp"
#include "enum.hpp"
#include "resource.h"


// Game Parameters
const int SCREEN_SPACE_WIDTH = 768;
const int SCREEN_SPACE_HEIGHT = 768;

const int WINDOW_WIDTH = SCREEN_SPACE_WIDTH;
const int WINDOW_HEIGHT = SCREEN_SPACE_HEIGHT;

const VECTOR2i WINDOW = VECTOR2i(WINDOW_WIDTH, WINDOW_HEIGHT);
const VECTOR2i WINDOW_CENTER = WINDOW / 2;

const std::string GAME_WINDOW_NAME = "Asteroids";
const int COLOR_DEPTH = 32;
const COLOR BACKGROUND_COLOR(0x000000, 0xff);

const int BRIGHTNESS = 128;
const int GLARE = 12;

std::mt19937 mt;
std::random_device rd;

const int ROTATION_SPEED = 3;
const float FRICTION = 0.99;

const float ARROW_BASE_SPEED = 0.03;
const float ARROW_MAX_VEL = 2;
const float ARROW_BOOST_SPEED = ARROW_MAX_VEL * 3;
const int ARROW_BORDER_SIZE = 30;
const int PLAYER_RESPAWN_TIMER = 3;

const float BULLET_SPEED = 15;

const int STARTING_ASTEROID_COUNT = 5;
const std::vector<int> ASTEROID_SIZE = {5,10,20,30,40,50,60,};
const std::vector<float> ASTEROID_SPEED = {1.5,1,0.7,0.6,0.5,0.4,0.3,};
const std::vector<int> ASTEROID_SCORES = {5,10,25,50,100,250,500};
const std::vector<int> ASTEROID_SPAWN_COUNT = { 6, 4, 3, 2, 1, 1, 1,};

const float PARTICLE_INITIAL_SPEED = 2;
const float PARTICLE_TIME = 1;
const int PLAYER_DEATH_PARTICLE_COUNT = 5;
const float PLAYER_DEATH_PARTICLE_INITIAL_SPEED = 0.3;

int sfx_shoot;
int sfx_thrust;
int sfx_breakAsteroid;
int sfx_death;
int sfx_boost;
int sfx_gameOver;
int sfx_getReady;
int sfx_newLife;
int sfx_levelClear;

std::vector<int> soundMem;


std::vector<ASTEROID> asteroids;
std::vector<POINT_PARTICLE> pointParticles;
std::vector<POINT_PARTICLE> deathParticles;

OBJECT player;
OBJECT exhaust;
OBJECT bullet;
OBJECT largeAsteroid;
OBJECT scoreObject;
OBJECT numberObject;

int score;
const int ASTEROID_INITIAL_SPAWN_BUDGET = 1;
int level;
int lives;
const int INITIAL_LIVES = 3;

const int LIVES_INCREMENT = 10000;

uint64_t skippedFrames = 0;

bool game();
void drawAsteroid(const ASTEROID& asteroid);
void titleScreen(int& screenDelay, GAME_STATE& gameState, int& timer);
void loadScreen(int& screenDelay, GAME_STATE& gameState);
void gameScreen(int& screnDelay, GAME_STATE& gameState);
void clearScreen(int& screnDelay, GAME_STATE& gameState);
void gameOverScreen(int& screnDelay, GAME_STATE& gameState);
void resetParticles(std::vector<POINT_PARTICLE>& particles);
bool drawBullet();
void drawLives();
void drawScore();
void spawnAsteroids();
void resetAsteroidPositions();
void resetAsteroidPosition(ASTEROID& ast);
void Initialize();
void drawParticles(std::vector<POINT_PARTICLE>& particles, OBJECT particle, bool canShrink = true);
void controlPlayer(bool& isBulletVisible, int time);
void spawnParticles(std::vector<POINT_PARTICLE>& particles, VECTOR2f pos, int count, float speed, int time);
int registerSoundMem(TCHAR* path, std::vector<int> list);