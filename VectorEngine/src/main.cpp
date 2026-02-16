#include "main.hpp"

ASTEROID titleAsteroid;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hprevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("ASTEROIDS");
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b);
	SetDrawScreen(DX_SCREEN_BACK);

	SetAlwaysRunFlag(TRUE);

	Initialize();

	GAME_STATE gameState = GAME_TITLE;
	int screenDelay = 0;

	int timer = 0;

	while (ProcessMessage() == 0)
	{
		updateKeys();
		switch (gameState)
		{
		case GAME_TITLE:
			titleScreen(screenDelay, gameState, timer);
			break;
		case GAME_LOAD:
			loadScreen(screenDelay, gameState);
			break;
		case GAME_GAME:
			gameScreen(screenDelay, gameState);
			break;
		case GAME_CLEAR:
			clearScreen(screenDelay, gameState);
			break;
		case GAME_OVER:
			gameOverScreen(screenDelay, gameState);
			break;
		}
		DxLibAddon::doDelay();

		if (checkKey(KEY_INPUT_ESCAPE).down) break;
	}

	for (auto mem : soundMem)
	{
		DeleteSoundMem(mem);
	}

	DxLib_End();
	return 0;
}

void titleScreen(int& screenDelay, GAME_STATE& gameState, int& timer)
{
	ClearDrawScreen();


	titleAsteroid.obj.rotation -= DEG2RAD / 4;
	drawAsteroid(titleAsteroid);


	std::string titleText = "ASTEROIDS";
	DxLibAddon::DrawString(WINDOW_CENTER - VECTOR2i(0, 40), titleText, WHITE, 90, true);
	if (timer % 120 < 60)
	{
		std::string pressText = "press any key to start";
		DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 100), pressText, WHITE, 30, true);
	}


	std::string upDownText = "W(ª)/S(«)    Move Forwards/Backwards";
	DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 150), upDownText, WHITE, 20, true);
	std::string leftRightText = "A(©)/D(¨)    Spin Left/Right        ";
	DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 170), leftRightText, WHITE, 20, true);
	std::string shootText = "Space(Z)       Shoot                  ";
	DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 190), shootText, WHITE, 20, true);
	std::string boostText = "Shift(X)       Boost                  ";
	DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 210), boostText, WHITE, 20, true);
	if (isAnyKeyDown())
	{
		screenDelay = 4.5 * FPS;
		PlaySoundMem(sfx_getReady, DX_PLAYTYPE_BACK);
		score = 0;
		gameState = GAME_LOAD;
		timer = 0;
	}
	ScreenFlip();
	timer++;
}

void loadScreen(int& screenDelay, GAME_STATE& gameState)
{
	ClearDrawScreen();
	drawScore();
	std::string readyText = "get ready...";
	DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 100), readyText, WHITE, 30, true);
	screenDelay--;
	if (screenDelay <= 0)
	{
		gameState = GAME_GAME;
		lives = INITIAL_LIVES;
		score = 0;
		level = 0;
		asteroids.clear();
		spawnAsteroids();
		return;
	}
	ScreenFlip();
}

void gameScreen(int& screenDelay, GAME_STATE& gameState)
{
	if (lives == 0)
	{
		gameState = GAME_OVER;
		screenDelay = 5 * FPS;
		PlaySoundMem(sfx_gameOver, DX_PLAYTYPE_BACK);
		return;
	}
	bool isClear = game();
	if (isClear)
	{
		level++;
		gameState = GAME_CLEAR;
		screenDelay = 5 * FPS;
		PlaySoundMem(sfx_levelClear, DX_PLAYTYPE_BACK);
		return;
	}
}

void clearScreen(int& screenDelay, GAME_STATE& gameState)
{
	std::string readyText = "Level Clear!";
	DxLibAddon::DrawString(WINDOW_CENTER + VECTOR2i(0, 100), readyText, WHITE, 30, true);
	screenDelay--;
	if (screenDelay <= 0)
	{
		gameState = GAME_GAME;
		asteroids.clear();
		spawnAsteroids();
		return;
	}
	ScreenFlip();
}

void gameOverScreen(int& screenDelay, GAME_STATE& gameState)
{
	ClearDrawScreen();
	std::string titleText = "GAME OVER";
	DxLibAddon::DrawString(WINDOW_CENTER - VECTOR2i(0, 40), titleText, WHITE, 70, true);
	screenDelay--;
	if (screenDelay <= 0)
	{
		gameState = GAME_TITLE;
		screenDelay = 5 * FPS;
	}
	ScreenFlip();
}

bool game()
{
	OBJECT line(lineGraph);
	line.graphSize = 10;

	player.pos = WINDOW_CENTER;
	player.vel = VECTOR2f(0);
	player.rotation = 0;
	exhaust.pos = player.pos;

	resetParticles(pointParticles);
	resetParticles(deathParticles);

	resetAsteroidPositions();

	int time = 0;
	bool isBulletVisible = false;
	bool isPlayerAlive = true;
	int respawnTimer = -1;
	
	int lifeScore = score % LIVES_INCREMENT;


	while (ProcessMessage() == 0)
	{
		// Refresh
		ClearDrawScreen();
		time++;
		updateKeys();
		if (isPlayerAlive)
		{
			controlPlayer(isBulletVisible, time);
		}
		else if (respawnTimer == 0)
		{
			respawnTimer = -1;
			return false;
		}
		else if (respawnTimer > 0)
		{
			respawnTimer--;
			drawParticles(deathParticles, line, false);
		}

		if (isBulletVisible)
		{
			isBulletVisible = drawBullet();
		}

		for (int i = asteroids.size() - 1; i >= 0; i--)
		{
			asteroids[i].obj.move();
			asteroids[i].obj.wrapPosition(VECTOR2f(-(asteroids[i].obj.getRadius())), WINDOW + VECTOR2i(asteroids[i].obj.getRadius()));
			if (asteroids[i].obj.isColliding(bullet) && isBulletVisible)
			{
				int particleCount = max((asteroids[i].size + 1), 1) * 3 * max(asteroids[i].size / 2, 1);
				spawnParticles(pointParticles, asteroids[i].obj.pos, particleCount, PARTICLE_INITIAL_SPEED, FPS * PARTICLE_TIME);
				PlaySoundMem(sfx_breakAsteroid, DX_PLAYTYPE_BACK);

				// ADD SCORE
				int points = ASTEROID_SCORES[asteroids[i].size];
				score += points;
				lifeScore += points;

				// GIVE LIVES
				if (lifeScore > LIVES_INCREMENT)
				{
					lives++;
					lifeScore -= LIVES_INCREMENT;
					PlaySoundMem(sfx_newLife, DX_PLAYTYPE_BACK);
				}


				isBulletVisible = false;
				if (asteroids[i].size == 0)
				{
					asteroids.erase(asteroids.begin() + i);
					continue;
				}

				// SPLIT ASTEROID
				asteroids[i].size -= 1;
				asteroids[i].obj.rotation = fmod(mt() / 1000.0, 2 * M_PI);
				asteroids[i].obj.vel = VECTOR2f(0, -1).rotate(bullet.rotation + M_PI / 4 + fmod(mt() / 1000.0, M_PI / 8)) * ASTEROID_SPEED[asteroids[i].size];
				asteroids[i].obj.graphSize = ASTEROID_SIZE[asteroids[i].size];
				asteroids.push_back(ASTEROID(asteroids[i]));
				asteroids[i].obj.vel = asteroids[i].obj.vel.rotate(-M_PI / 4 + fmod(mt() / 1000.0, M_PI / 8));
				asteroids[i].obj.rotation = fmod(mt() / 1000.0, 2 * M_PI);

			}
			else if (asteroids[i].obj.isColliding(player) && isPlayerAlive)
			{
				// KILL PLAYER
				isPlayerAlive = false;
				respawnTimer = FPS * PLAYER_RESPAWN_TIMER;
				spawnParticles(deathParticles, player.pos, PLAYER_DEATH_PARTICLE_COUNT, PLAYER_DEATH_PARTICLE_INITIAL_SPEED, respawnTimer);
				PlaySoundMem(sfx_death, DX_PLAYTYPE_BACK);
				StopSoundMem(sfx_thrust);
				lives--;
			}
			drawAsteroid(asteroids[i]);
		}

		drawParticles(pointParticles, bullet);


		drawLives();
		drawScore();

		if (asteroids.empty()) return true;
		ScreenFlip();

		DxLibAddon::doDelay();
		if (checkKey(KEY_INPUT_ESCAPE).down) return false;
	}
	return false;
}

void drawAsteroid(const ASTEROID& asteroid)
{
	static OBJECT asteroidDoodadObject(asteroidDoodad);
	asteroid.obj.draw();
	asteroidDoodadObject.graphSize = asteroid.obj.graphSize;
	asteroidDoodadObject.rotation = asteroid.obj.rotation;
	asteroidDoodadObject.pos = asteroid.obj.pos;
	asteroidDoodadObject.color = asteroid.obj.color;
	asteroidDoodadObject.draw();
}

void resetParticles(std::vector<POINT_PARTICLE>& particles)
{
	for (auto& p : particles)
	{
		p.isActive = false;
	}
}

bool drawBullet()
{
	bullet.move();
	if (
		bullet.pos.x < -ARROW_BORDER_SIZE ||
		bullet.pos.x > WINDOW.x + ARROW_BORDER_SIZE ||
		bullet.pos.y < -ARROW_BORDER_SIZE ||
		bullet.pos.y > WINDOW.y + ARROW_BORDER_SIZE)
	{
		return false;
	}
	bullet.draw();
	return true;
}

void drawLives()
{
	for (int i = 0; i < lives; i++)
	{
		OBJECT lifeObject(playerGraph);
		lifeObject.graphSize = 15;
		lifeObject.pos = VECTOR2i(1.5 * lifeObject.graphSize, 3 * lifeObject.graphSize);
		lifeObject.pos.x += 1.5 * lifeObject.graphSize * i;
		lifeObject.draw();
	}
}

void drawScore()
{
	scoreObject.draw();
	std::string scoreString = std::format("{:05}", score);
	for (int i = scoreString.length() - 1; i >= 0; i--)
	{
		int n = scoreString[i] - '0';
		numberObject.setGraph(numberGraphs[n]);
		numberObject.pos = VECTOR2i(WINDOW_WIDTH - 2.5 * numberObject.graphSize, 3 * numberObject.graphSize);
		numberObject.pos.y += 6 * numberObject.graphSize;
		numberObject.pos.x -= 4 * numberObject.graphSize * (scoreString.length() - i - 1);
		numberObject.draw();
	}
}


void spawnAsteroids()
{
	int asteroidSpawnBudget = ASTEROID_INITIAL_SPAWN_BUDGET + pow(1.5, level);
	for (int i = 0; i < asteroidSpawnBudget; i++)
	{
		ASTEROID ast(largeAsteroid, fmod(mt() / 1000.0, 2));
		ast.size = mt() % ASTEROID_SIZE.size();
		for (int j = 0; j < ASTEROID_SPAWN_COUNT[ast.size]; j++)
		{
			resetAsteroidPosition(ast);
			asteroids.push_back(ast);
		}
	}
}

void resetAsteroidPositions()
{
	for (auto& ast : asteroids)
	{
		resetAsteroidPosition(ast);
	}
}

void resetAsteroidPosition(ASTEROID& ast)
{
	ast.obj.vel = VECTOR2f(0, 1).rotate(mt() * DEG2RAD) * ASTEROID_SPEED[ast.size];
	ast.obj.graphSize = ASTEROID_SIZE[ast.size];
	ast.obj.pos = (VECTOR2f(0, 1) * WINDOW_CENTER.x).rotate(mt() * DEG2RAD) + WINDOW_CENTER;
	ast.obj.rotation = (mt() * DEG2RAD);
}

int registerSoundMem(const TCHAR* path, std::vector<int> list)
{
	int mem = LoadSoundMem(path);
	list.push_back(mem);
	return mem;
}

int registerSoundMemByResource(int path, std::vector<int> list)
{
	int mem = LoadSoundMemByResource(MAKEINTRESOURCE(path), "WAVE");
	list.push_back(mem);
	return mem;
}

void Initialize()
{
	sfx_shoot = registerSoundMemByResource(IDR_WAVE8, soundMem);
	sfx_thrust = registerSoundMemByResource(IDR_WAVE9, soundMem);
	sfx_breakAsteroid = registerSoundMemByResource(IDR_WAVE2, soundMem);
	sfx_death = registerSoundMemByResource(IDR_WAVE3, soundMem);
	sfx_boost = registerSoundMemByResource(IDR_WAVE1, soundMem);
	sfx_gameOver = registerSoundMemByResource(IDR_WAVE4, soundMem);
	sfx_getReady = registerSoundMemByResource(IDR_WAVE5, soundMem);
	sfx_newLife = registerSoundMemByResource(IDR_WAVE7, soundMem);
	sfx_levelClear = registerSoundMemByResource(IDR_WAVE6, soundMem);
	ChangeVolumeSoundMem(192, sfx_thrust);

	mt = std::mt19937(rd());

	player = OBJECT(playerGraph);
	exhaust = OBJECT(exhaustGraph);
	bullet = OBJECT(bulletGraph);
	largeAsteroid = OBJECT(largeAsteroidGraph);
	scoreObject = OBJECT(scoreGraph);
	numberObject = OBJECT(numberGraphs[0]);

	player.graphSize = 20;
	exhaust.graphSize = 10;
	bullet.graphSize = 5;
	largeAsteroid.graphSize = 5;
	scoreObject.graphSize = 5;
	numberObject.graphSize = 5;

	scoreObject.pos = VECTOR2i(WINDOW_WIDTH - 10.5 * scoreObject.graphSize, 3 * scoreObject.graphSize);

	pointParticles = std::vector<POINT_PARTICLE>(100, {.isActive = false});
	deathParticles = std::vector<POINT_PARTICLE>(PLAYER_DEATH_PARTICLE_COUNT, {.isActive = false});
	asteroids = std::vector<ASTEROID>(0);

	setGlareValue(GLARE);

	titleAsteroid = ASTEROID(largeAsteroid);
	titleAsteroid.size = ASTEROID_SIZE.size() - 1;
	resetAsteroidPosition(titleAsteroid);
	titleAsteroid.obj.pos = WINDOW_CENTER;
}

void drawParticles(std::vector<POINT_PARTICLE>& particles, OBJECT particle, bool canShrink)
{
	float size = particle.graphSize;
	for (auto& p : particles)
	{
		if (p.isActive)
		{
			if (p.time == 0)
			{
				p.isActive = false;
				continue;
			}
			p.time--;
			p.vel *= FRICTION;
			p.pos += p.vel;
			particle.pos = p.pos;
			float tSize = size;
			if (canShrink)
			{
				tSize *= (p.time / (FPS * PARTICLE_TIME));
			}
			particle.graphSize = tSize * p.scaleMod;
			particle.rotation = p.rotation;
			particle.draw();
		}
	}
}

void controlPlayer(bool& isBulletVisible, int time)
{
	static bool isBoosted = false;
	static bool pastAccelerating = false;
	bool accelerating = false;
	float playerAcc = ARROW_BASE_SPEED;
	bool isOverSpeed = player.vel.magnitude() > ARROW_MAX_VEL;
	// Inputs
	if (checkKey(KEY_INPUT_A).isHold || checkKey(KEY_INPUT_LEFT).isHold)
	{
		player.rotation += ROTATION_SPEED * DEG2RAD;
	}
	if (checkKey(KEY_INPUT_D).isHold || checkKey(KEY_INPUT_RIGHT).isHold)
	{
		player.rotation -= ROTATION_SPEED * DEG2RAD;
	}

	if ((checkKey(KEY_INPUT_LSHIFT).down || checkKey(KEY_INPUT_X).down) && !isBoosted)
	{
		playerAcc = ARROW_BOOST_SPEED;
		isBoosted = true;
		player.vel += VECTOR2f(0, -playerAcc).rotate(player.rotation);
		isOverSpeed = true;
		PlaySoundMem(sfx_boost, DX_PLAYTYPE_BACK);
	}

	if ((checkKey(KEY_INPUT_SPACE).down || checkKey(KEY_INPUT_Z).down) && !isBulletVisible)
	{
		isBulletVisible = true;
		bullet.pos = player.pos - (VECTOR2f(0, 4 / 3.0).scale(player.graphSize)).rotate(player.rotation);
		bullet.rotation = player.rotation;
		bullet.vel = VECTOR2f(0, -BULLET_SPEED).rotate(bullet.rotation);
		PlaySoundMem(sfx_shoot, DX_PLAYTYPE_BACK);
	}

	if (checkKey(KEY_INPUT_W).isHold || checkKey(KEY_INPUT_UP).isHold)
	{
		if (!isOverSpeed)
		{
			player.vel += VECTOR2f(0, -playerAcc).rotate(player.rotation);
		}
		accelerating = true;
	}
	else if (checkKey(KEY_INPUT_S).isHold || checkKey(KEY_INPUT_DOWN).isHold)
	{
		if (!isOverSpeed)
		{
			player.vel += VECTOR2f(0, playerAcc).rotate(player.rotation);
		}
		accelerating = true;
	}

	if (!accelerating || isOverSpeed)
	{
		player.vel = player.vel.normalized() * player.vel.magnitude() * FRICTION;
	}
	if (!isOverSpeed && isBoosted)
	{
		isBoosted = false;
	}

	if (accelerating && !CheckSoundMem(sfx_thrust))
	{
		PlaySoundMem(sfx_thrust, DX_PLAYTYPE_LOOP);
	}
	else if (!accelerating && CheckSoundMem(sfx_thrust))
	{
		StopSoundMem(sfx_thrust);
	}

	player.move();
	player.wrapPosition(VECTOR2f(-ARROW_BORDER_SIZE), WINDOW + VECTOR2i(ARROW_BORDER_SIZE));

	player.draw();

	if (accelerating && time % 2)
	{
		exhaust.pos = player.pos + (VECTOR2f(0, 2 / 3.0).scale(player.graphSize)).rotate(player.rotation);
		exhaust.rotation = player.rotation;
		exhaust.draw();
		exhaust.draw(true);
	}

	pastAccelerating = accelerating;
}

void spawnParticles(std::vector<POINT_PARTICLE>& particles, VECTOR2f pos, const int count, const float speed, const int time)
{
	for (int i = 0; i < count; i++)
	{
		auto iterator = std::ranges::find_if(particles, [](POINT_PARTICLE p) {return !p.isActive;});
		if (iterator == particles.end())
		{
			iterator = std::min_element(particles.begin(), particles.end(), [](const POINT_PARTICLE& a, const POINT_PARTICLE& b) {return a.time > b.time;});
		}
		if (iterator != particles.end())
		{ 
			iterator->isActive = true;
			iterator->pos = pos;
			iterator->vel = VECTOR2f(0, 1).rotate(mt() * DEG2RAD).normalized() * speed;
			iterator->time = time;
			iterator->rotation = fmod(mt() / 1000.0, 2 * M_PI);
			iterator->scaleMod = 1 + fmod(mt() / 10.0, 1);
		}
	}
}
