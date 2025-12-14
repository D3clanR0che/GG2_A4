#include "Framework.h"
#include "SurvivorsGame.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Player.h"
#include "Bat.h"
#include "Slime.h"
#include "MathFuncs.h"
#include "SurvivorsCamera.h"
#include "PathfindingTestbed/Tilemap.h"
#include "PathfindingTestbed/Pathfinder.h"
#include "WorldMap.h"

namespace fw
{

	const int SurvivorsGame::c_numEnemies = 1000;
	const int SurvivorsGame::c_numPickups = 300;
	const int SurvivorsGame::c_initialXPRequiredToLevelUp = 10;
	const float SurvivorsGame::c_XPMultiplierPerLevel = 1.5f;
	const float SurvivorsGame::c_initialEnemySpawnTime = 3.0f;
	const int SurvivorsGame::c_numSides = 360;
	const ivec2 SurvivorsGame::c_mapSize = { 100, 50 };
	const vec2 SurvivorsGame::c_tileSize = { 40.0f,40.0f };
	const float SurvivorsGame::c_spriteDuration = 0.1f;

	SurvivorsGame::SurvivorsGame()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_pResourceManager = new ResourceManager();

		Texture* texture = new Texture("Data/Textures/DungeonCrawler.png");
		m_pResourceManager->add("DungeonCrawlerTexture", texture);

		SpriteSheet* spritesheet = new SpriteSheet("Data/Textures/DungeonCrawler.json");
		m_pResourceManager->add("DungeonCrawlerSpriteSheet", spritesheet);

		Animation* animation = new Animation(texture, c_spriteDuration);
		animation->addUVTransform(spritesheet->GetUVTransform("knight_idle_anim_f0"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_idle_anim_f1"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_idle_anim_f2"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_idle_anim_f3"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_idle_anim_f4"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_idle_anim_f5"));
		m_pResourceManager->add("KnightIdleAnimation", animation);

		animation = new Animation(texture, c_spriteDuration);
		animation->addUVTransform(spritesheet->GetUVTransform("knight_run_anim_f0"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_run_anim_f1"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_run_anim_f2"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_run_anim_f3"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_run_anim_f4"));
		animation->addUVTransform(spritesheet->GetUVTransform("knight_run_anim_f5"));
		m_pResourceManager->add("KnightMovingAnimation", animation);


		animation = new Animation(texture, c_spriteDuration);
		animation->addUVTransform(spritesheet->GetUVTransform("fly_anim_f0"));
		animation->addUVTransform(spritesheet->GetUVTransform("fly_anim_f1"));
		animation->addUVTransform(spritesheet->GetUVTransform("fly_anim_f2"));
		animation->addUVTransform(spritesheet->GetUVTransform("fly_anim_f3"));
		m_pResourceManager->add("BatAnimation", animation);


		animation = new Animation(texture, c_spriteDuration);
		animation->addUVTransform(spritesheet->GetUVTransform("slime_idle_anim_f0"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_idle_anim_f1"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_idle_anim_f2"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_idle_anim_f3"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_idle_anim_f4"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_idle_anim_f5"));
		m_pResourceManager->add("SlimeIdleAnimation", animation);


		animation = new Animation(texture, c_spriteDuration);
		animation->addUVTransform(spritesheet->GetUVTransform("slime_run_anim_f0"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_run_anim_f1"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_run_anim_f2"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_run_anim_f3"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_run_anim_f4"));
		animation->addUVTransform(spritesheet->GetUVTransform("slime_run_anim_f5"));
		m_pResourceManager->add("SlimeMovingAnimation", animation);


		AnimationCollection* collection = new AnimationCollection();
		collection->addAnimation("Idle", m_pResourceManager->get<Animation>("KnightIdleAnimation"));
		collection->addAnimation("Moving", m_pResourceManager->get<Animation>("KnightMovingAnimation"));
		m_pResourceManager->add("player", collection);

		collection = new AnimationCollection();
		collection->addAnimation("Idle", m_pResourceManager->get<Animation>("BatAnimation"));
		collection->addAnimation("Moving", m_pResourceManager->get<Animation>("BatAnimation"));
		m_pResourceManager->add("bat", collection);

		collection = new AnimationCollection();
		collection->addAnimation("Idle", m_pResourceManager->get<Animation>("SlimeIdleAnimation"));
		collection->addAnimation("Moving", m_pResourceManager->get<Animation>("SlimeMovingAnimation"));
		m_pResourceManager->add("slime", collection);

		std::vector<fw::VertexFormat> trianglePoints = { {vec2(-0.5f, -0.5f)}, {vec2(0.5f, -0.5f)}, {vec2(0.0f, 0.5f)} };

		std::vector<fw::VertexFormat> boxPoints = {
			{ { -0.5f, -0.5f }, 255, 255, 255, 255, { 0, 0 } },
			{ { 0.5f, -0.5f }, 255, 255, 255, 255, { 1, 0 } },
			{ { -0.5f, 0.5f }, 255, 255, 255, 255, { 0, 1 } },
			{ { 0.5f, 0.5f }, 255, 255, 255, 255, { 1, 1} }
		};

		std::vector<fw::VertexFormat> diamondPoints = { {vec2(0.0f,-0.5f)}, {vec2(0.5f,0.0f)}, {vec2(-0.5f,0.0f)}, {vec2(0.0f,0.5f)} };

		std::vector<fw::VertexFormat> barPoints = { {vec2(0.0f,-0.5f)}, {vec2(0.5f,-0.5f)}, {vec2(0.0f,0.5f)}, {vec2(0.5f,0.5f)} };

		float aspectRatio = 1280.0f / 720.0f;

		m_pCamera = new SurvivorsCamera(vec2(1280.0f / 2.0f, 720.0f / 2.0f), aspectRatio, 720.0f / 4.0f);
		m_pHudCamera = new Camera(vec2(1280.0f / 2.0f, 720.0f / 2.0f), aspectRatio, 720.0f / 2.0f);
		ShaderProgram* pShader = new ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Basic.frag");
		m_pResourceManager->add("BasicShader", pShader);

		pShader = new ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/Texture.frag");
		m_pResourceManager->add("TextureShader", pShader);


		m_meshes["triangle"] = new Mesh(GL_TRIANGLES, trianglePoints);
		m_meshes["box"] = new Mesh(GL_TRIANGLE_STRIP, boxPoints);
		m_meshes["diamond"] = new Mesh(GL_TRIANGLE_STRIP, diamondPoints);
		m_meshes["bar"] = new Mesh(GL_TRIANGLE_STRIP, barPoints);
		m_meshes["tile"] = new fw::Mesh(GL_TRIANGLE_STRIP, { {{0,0}}, {{1,0}}, {{0,1}}, {{1,1}} });

		m_pWorldMap = new WorldMap(m_pResourceManager->get<ShaderProgram>("BasicShader"), c_mapSize, c_tileSize, m_meshes["tile"]);

		std::vector<float> m_points;

		m_points.push_back(0.0f);
		m_points.push_back(0.0f);

		float radiansPerSide = 2.0f * (float)PI / (float)c_numSides;  //TODO: Randomize number of sides

		for (int i = 0; i < c_numSides; i++)
		{
			float angle = i * radiansPerSide;

			m_points.push_back(cosf(angle));
			m_points.push_back(sinf(angle));
		}

		m_points.push_back(cosf(radiansPerSide * c_numSides));
		m_points.push_back(sinf(radiansPerSide * c_numSides));

		// Create a player.
		m_pPlayer = new Player(this, m_meshes["box"], m_pResourceManager->get<ShaderProgram>("TextureShader"));

		// Fill a vector with enemies.
		for (int i = 0; i < c_numEnemies; i++)
		{
			Enemy* pEnemy;

			int randEnemy = randInt(1, 2);

			if (randEnemy == 1)
			{
				pEnemy = new Bat(this, m_meshes["box"], m_pResourceManager->get<ShaderProgram>("TextureShader"));
			}
			else
			{
				pEnemy = new Slime(this, m_meshes["box"], m_pResourceManager->get<ShaderProgram>("TextureShader"));
			}

			m_enemies.push_back(pEnemy);
		}

		// Fill a vector with pickups.
		for (int i = 0; i < c_numPickups; i++)
		{
			Pickup* pPickup = new Pickup(this, m_meshes["circle"], m_pResourceManager->get<ShaderProgram>("BasicShader"));
			m_pickups.push_back(pPickup);
		}

		m_pHealthBar = new ProgressBar(m_meshes["bar"], m_pResourceManager->get<ShaderProgram>("BasicShader"), vec2(140.0f, 100.0f), vec2(840.0f, 50.0f), 0.0f, DarkRed(), Red(), m_pPlayer->getHealthAddress(), m_pPlayer->getMaxHealthAddress());


		reset();
	}

	SurvivorsGame::~SurvivorsGame()
	{
		// Delete all objects.
		delete m_pPlayer;

		for (Enemy* pEnemy : m_enemies)
		{
			delete pEnemy;
		}

		for (Pickup* pPickup : m_pickups)
		{
			delete pPickup;
		}

		for (const auto& pair : m_meshes)
		{
			delete pair.second;
		}
	}

	void SurvivorsGame::reset()
	{
		m_gameOver = false;
		m_enemiesKilled = 0;
		m_timePlayed = 0;

		m_enemySpawnTimer = 0;

		for (Enemy* pEnemy : m_enemies)
		{
			pEnemy->reset();
		}

		for (Pickup* pPickup : m_pickups)
		{
			pPickup->reset();
		}

		m_pPlayer->reset();
		m_pPlayer->setHealth();
		m_pPlayer->setActive(true);
		m_pPlayer->setPosition({ 1280 / 2.0f, 720 / 2.0f });

		m_pWorldMap->generateTilemap();
	}

	void SurvivorsGame::update(float deltaTime)
	{
		int startx = 3;
		int starty = 1;
		int endx = 0;
		int endy = 6;

		if (m_gameOver == false)
		{
			m_timePlayed += deltaTime;
		}

		if (m_gameOver == false)
		{
			m_pPlayer->update(deltaTime);
			m_pCamera->setPosition(m_pPlayer->getPosition());
		}

		if (m_pPlayer->isMoving())
		{
			m_pCamera->setZoom(720.0f / 2.0f);
		}
		else
		{
			m_pCamera->setZoom(720.0f / 4.0f);
		}

		m_pCamera->update(deltaTime);

		for (Enemy* pEnemy : m_enemies)
		{
			if (pEnemy->isActive())
			{
				pEnemy->update(deltaTime);
			}
		}

		for (Pickup* pPickup : m_pickups)
		{
			if (pPickup->isActive())
			{
				pPickup->update(deltaTime);
			}
		}

		if (m_gameOver == false)
		{
			m_enemySpawnTimer -= deltaTime;
			if (m_enemySpawnTimer < 0)
			{
				m_enemySpawnTimer = c_initialEnemySpawnTime;
				spawnEnemies();
			}
		}

	}

	void SurvivorsGame::draw()
	{
		//ClearBackground( RAYWHITE );

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//DrawText( "Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY );
		m_pWorldMap->draw(m_pCamera);


		for (Pickup* pPickup : m_pickups)
		{
			if (pPickup->isActive())
			{
				pPickup->draw(m_pCamera);
			}
		}

		for (Enemy* pEnemy : m_enemies)
		{
			if (pEnemy->isActive())
			{
				pEnemy->draw(m_pCamera);
			}
		}

		if (m_gameOver == false)
		{
			m_pPlayer->draw(m_pCamera);
		}

		m_pHealthBar->draw(m_pHudCamera);
	}

	void SurvivorsGame::onKey(int keyCode, fw::KeyState keyState)
	{
		if (keyCode == 'R' && keyState == fw::KeyState::Pressed)
		{
			reset();
		}

		if (keyCode == '1' && keyState == fw::KeyState::Pressed)
		{
			m_drawDebugData = !m_drawDebugData;
		}

		// Send key events to the player.
		m_pPlayer->onKey(keyCode, keyState);
	}

	void SurvivorsGame::spawnEnemies()
	{
		for (int i = 0; i < 10; i++)
		{
			int side = randInt(0, 3);
			vec2 pos;
			if (side == 0) // Left
			{
				pos = vec2(randFloat(-264, -64), randFloat(0, 704));
			}
			else if (side == 1) // Right
			{
				pos = vec2(randFloat(1280, 1480), randFloat(0, 704));
			}
			else if (side == 2) // Top
			{
				pos = vec2(randFloat(0, 1280), randFloat(704, 904));
			}
			else if (side == 3) // Bottom
			{
				pos = vec2(randFloat(0, 1280), randFloat(-264, -64));
			}

			spawnEnemy(pos);
		}
	}

	void SurvivorsGame::spawnEnemy(vec2 pos)
	{
		Enemy* pEnemy = nullptr;

		// Find the first inactive Enemy.
		for (int i = 0; i < c_numEnemies; i++)
		{
			if (m_enemies[i]->isActive() == false)
			{
				pEnemy = m_enemies[i];
				break;
			}
		}

		if (pEnemy != nullptr)
		{
			pEnemy->setActive(true);
			pEnemy->setPosition(pos);
		}
	}

	void SurvivorsGame::spawnPickup(vec2 pos)
	{
		Pickup* pPickup = nullptr;

		// Find the first inactive Pickup.
		for (int i = 0; i < c_numPickups; i++)
		{
			if (m_pickups[i]->isActive() == false)
			{
				pPickup = m_pickups[i];
				break;
			}
		}

		if (pPickup != nullptr)
		{
			pPickup->setActive(true);
			pPickup->setPosition(pos);
		}
	}

	void SurvivorsGame::handleCollisions()
	{

		// Enemies hitting the player.
		for (int e = 0; e < c_numEnemies; e++)
		{
			if (m_enemies[e]->isActive() && !m_enemies[e]->isFadingOut())
			{
				vec2 enemyPos = m_enemies[e]->getPosition();
				float enemyRadius = m_enemies[e]->getRadius();

				vec2 playerPos = m_pPlayer->getPosition();
				float playerRadius = m_pPlayer->getRadius();

				vec2 distanceBetween = enemyPos - playerPos;

				float distance = distanceBetween.length();

				if (distance <= playerRadius + enemyRadius)
				{
					m_pPlayer->damagePlayer();
					m_enemies[e]->applyDamage(5000);

					if (m_pPlayer->getHealth() <= 0)
					{
						m_gameOver = true;
					}
				}
			}
		}

		// Player hitting pickups.
		for (int p = 0; p < c_numPickups; p++)
		{
			if (m_pickups[p]->isActive() && !m_pickups[p]->isAnimating())
			{
				vec2 pickupPos = m_pickups[p]->getPosition();
				float pickupRadius = m_pickups[p]->getRadius();

				// Check if they collide with the player.
				vec2 playerPos = m_pPlayer->getPosition();
				float playerPickupRadius = m_pPlayer->getPickupRadius();

				if ((playerPos - pickupPos).length() < playerPickupRadius + pickupRadius)
				{
					m_pickups[p]->pickupObject(playerPos);
				}
			}
		}
	}

	void SurvivorsGame::onEnemyKilled(vec2 location)
	{
		spawnPickup(location);
		m_enemiesKilled++;
	}

	Enemy* SurvivorsGame::getClosestEnemy(vec2 pos)
	{
		float closestDistance = FLT_MAX;
		Enemy* pClosestEnemy = nullptr;

		for (int i = 0; i < c_numEnemies; i++)
		{
			if (m_enemies[i]->isActive() && m_enemies[i]->getHealth() > 0)
			{
				vec2 enemyPos = m_enemies[i]->getPosition();

				// Don't target enemies that are offscreen.
				if (enemyPos.x < 0.0f || enemyPos.x > 1280 ||
					enemyPos.y < 0.0f || enemyPos.y > 720)
				{
					continue;
				}

				float distance = (m_enemies[i]->getPosition() - pos).length();
				if (distance < closestDistance)
				{
					closestDistance = distance;
					pClosestEnemy = m_enemies[i];
				}
			}
		}

		return pClosestEnemy;
	}
}
