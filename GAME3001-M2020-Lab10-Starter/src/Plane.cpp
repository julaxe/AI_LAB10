#include "Plane.h"
#include "TextureManager.h"


Plane::Plane()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));

	// set frame width
	setWidth(65);

	// set frame height
	setHeight(65);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	
	buildPath();
	m_buildAnimations();
}

Plane::~Plane()
= default;

void Plane::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the plane sprite with simple propeller animation
	TextureManager::Instance()->playAnimation(
		"spritesheet", getAnimation("plane"),
		x, y, 0.5f, 0, 255, true);
}

void Plane::update()
{
	getTransform()->position += getRigidBody()->velocity;

	if (IsPatrolling())
	{
		Patrol();
	}
	else {
		getRigidBody()->velocity = glm::vec2(0, 0);
	}
}

void Plane::clean()
{
}

void Plane::Patrol()
{
	if (m_path.size() > 0)
	{
		if (Move(m_path[currentPath]->getTransform()->position.x, m_path[currentPath]->getTransform()->position.y))
		{
			currentPath++;
			if (currentPath >= m_path.size())
				currentPath = 0;
		}
	}
}

void Plane::buildPath()
{
	currentPath = 0;
	m_path.push_back(new PathNode(glm::vec2(1 * Config::TILE_SIZE - Config::TILE_SIZE*0.5, 1 * Config::TILE_SIZE - Config::TILE_SIZE*0.5)));
	m_path.push_back(new PathNode(glm::vec2((Config::COL_NUM ) * Config::TILE_SIZE - Config::TILE_SIZE * 0.5, 1 * Config::TILE_SIZE - Config::TILE_SIZE * 0.5)));
	m_path.push_back(new PathNode(glm::vec2((Config::COL_NUM) * Config::TILE_SIZE - Config::TILE_SIZE * 0.5, Config::ROW_NUM  * Config::TILE_SIZE - Config::TILE_SIZE * 0.5)));
	m_path.push_back(new PathNode(glm::vec2(1 * Config::TILE_SIZE - Config::TILE_SIZE * 0.5, Config::ROW_NUM * Config::TILE_SIZE - Config::TILE_SIZE * 0.5)));
}

bool Plane::Move(int x, int y)
{
	int dy = y - getTransform()->position.y;
	int dx = x - getTransform()->position.x;

	float angle = atan2(dy, dx);
	//std::cout << angle * 180 / M_PI << std::endl;
	int speed = 2;
	getRigidBody()->velocity = glm::vec2(speed * cos(angle), speed * sin(angle));
	if (abs(dx) < 3 && abs(dy) < 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Plane::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}