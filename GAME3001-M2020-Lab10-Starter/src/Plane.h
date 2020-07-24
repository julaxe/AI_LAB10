#pragma once
#ifndef __PLANE__
#define __PLANE__

#include "Sprite.h"

class Plane final : public Sprite
{
public:
	Plane();
	~Plane();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void setPatrol(bool state) { patrol = state; }
	bool IsPatrolling() { return patrol; }

private:
	void Patrol();
	void buildPath();
	bool Move(int x, int y);
	void m_buildAnimations();
	bool patrol;
	
};

#endif /* defined (__PLANE__) */
