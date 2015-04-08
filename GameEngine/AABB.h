#include "IAABB.h"
#include "Vector2.h"

#pragma once

class AABB {// : IAABB {
public:
	Vector2 *m_Center;
	Vector2 *m_HalfExtents;

	AABB( Vector2 *center, Vector2 *halfExtents );
	void Initialize( Vector2 *center, Vector2 *halfExtents );
	Vector2 *get_m_Center();
	void set_m_Center( Vector2 *p );
	Vector2 *get_m_HalfExtents();
	Vector2 *get_m_BottomLeft();
	Vector2 *get_m_BottomRight();
	Vector2 *get_m_TopLeft();
	Vector2 *get_m_TopRight();
	Vector2 *get_m_Min();
	Vector2 *get_m_Max();
	Vector2 *MinInto( Vector2 *v );
	void Enlarge( float amount );
	void EnlargeY( float amount );
	bool Overlap( IAABB *a, IAABB *b );
	bool Within( Vector2 *p );
	Vector2 *GetRandomPointWithin( float scaleX, float scaleY );
	Vector2 *ClampInto( Vector2 *candidate );
	void UpdateFrom( Vector2 *center, Vector2 *halfExtents );
};