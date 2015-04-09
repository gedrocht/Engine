#pragma once

#include "Map.h"
#include "Constants.h"
#include "Collide.h"
#include "Platformer.h"
class MoveableObject { // : public IAABB, public ICircle {
public:
	// friction with ground - 1=totally sticky, 0=ice
	float kGroundFriction;

	Vector2* m_pos;
	Vector2* m_posCorrect;
	Vector2* m_vel;
	float m_radius;
	Vector2* m_halfExtents;

	Platformer* m_platformer;
	Map* m_map;

	Contact* m_contact;

	bool m_onGround;
	bool m_onGroundLast;

	bool m_dead;

	MoveableObject( );
	Vector2 *Initialize( Vector2* pos, Map *map, Platformer* parent );
	float get_m_Radius( );
	Vector2* get_m_Centre( );
	Vector2* get_m_HalfExtents( );
	Vector2* get_m_Pos( );
	void set_m_Pos( Vector2 *pos );
	Vector2* get_m_Vel( );
	void set_m_Vel( Vector2* vel );
	bool get_m_OnGround( );
	bool get_m_OnGroundLast( );
	bool get_m_TileMapped( );
	bool get_m_Dead( );
	void set_m_Dead( bool dead );
	void Update( float dt );
	bool get_m_HasWorldCollision( );
	bool get_m_ApplyGravity( );
	bool get_m_ApplyFriction( );
	bool get_m_ForceUpdate( );
	void PreCollisionCode( );
	void PostCollisionCode( );
	void Collision( float dt );
	void InnerCollide( AABB *tileAabb, int tileType, float dt, int i, int j );
	void LandingTransition( );
	void CollisionResponse( Vector2 *normal, float dist, float dt );
	bool HeadingTowards( Vector2 *towardsPoint, MoveableObject *candidate );
};