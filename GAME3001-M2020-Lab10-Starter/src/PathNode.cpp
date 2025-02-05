#include "PathNode.h"

#include "CollisionManager.h"

PathNode::PathNode(glm::vec2 position)
	:m_bLOS(false)
{
	getTransform()->position = position;
	setWidth(Config::TILE_SIZE);
	setHeight(Config::TILE_SIZE);
	setType(PATH_NODE);
}

PathNode::~PathNode()
= default;

void PathNode::draw()
{
}

void PathNode::update()
{
	
}

void PathNode::clean()
{
}

void PathNode::setLOS(const bool LOS)
{
	m_bLOS = LOS;
}

bool PathNode::getLOS() const
{
	return m_bLOS;
}
