#pragma once

#include <Math.h>
#include "Platformer.h"
#include "AABB.h"
#include "Map.h"

class Map;
class Platformer;
class AABB;

class Player// : public Character
{
public:
	// how high do they jump?
	float kPlayerJumpVel;

	// how many frames does tha player flash for?
	int kHurtFrames;

	// controls how fast the player's velocity moves towards the target velocity
	// 1.0 = in one frame, 0 = never
	float kReachTargetScale;

	// how fast the player walks
	float kWalkSpeed;

	Vector2 *m_velTarget;
	Vector2 *m_vel;
	Vector2 *m_pos;

	//Keyboard *m_keyboard:Keyboard;

	AABB *m_tileAabb;

	bool m_tryToMove;
	bool m_flyMode;

	Player( );
	Vector2 *Initialize(Vector2 *pos, Map *map, Platformer *parent);
	//void MakeTemporaryilyInvunerable( );
	bool get_m_HasWorldCollision( );
	void Update( float dt );
	//void KeyboardControl( float dt );
	bool get_m_ApplyFriction( );
};