#pragma once

#include <Math.h>
#include "PointAndDistanceContainer.h"

class Circle {
public:
	Vector2 *m_pos;
	float m_radius;

	Circle::Circle( Vector2 *pos, float radius );
	Vector2 *Circle::get_m_Pos();
	void Circle::set_m_Pos( Vector2 *p );
	float Circle::get_m_Radius();
	void Circle::set_m_Radius( float newRadius );
	bool Circle::Contains( Vector2 *p );
	float Circle::DistanceToPoint( Vector2 *p );
	Vector2 *Circle::ClosestPointOnEdge( Vector2 *p, float bias );
	PointAndDistanceContainer *Circle::ClosestPointAndDistOnEdge( Vector2 *p );
	bool Circle::CircleCircleIntersect( Circle *a, Circle *b, Vector2 *pointAOut, Vector2 *pointBOut );
	float RayCast( Vector2 *start, Vector2 *end, bool invert );
};