#pragma once

#include "Vector2.h"

class PointAndDistanceContainer {
public:
	Vector2 *m_pos;
	float m_dist;

	PointAndDistanceContainer( Vector2 *p, float dist );
};