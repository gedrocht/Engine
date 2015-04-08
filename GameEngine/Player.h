#include <Math.h>
#include "Vector2.h"

class Player //: Character
{
	// how high do they jump?
	float kPlayerJumpVel = 900*1.2;

	// how many frames does tha player flash for?
	int kHurtFrames = 120;

	// controls how fast the player's velocity moves towards the target velocity
	// 1.0 = in one frame, 0 = never
	float kReachTargetScale = 0.7;

	// how fast the player walks
	float kWalkSpeed = 80;

	Vector2 *m_velTarget:Vector2;

	Keyboard *m_keyboard:Keyboard;

	AABB *m_tileAabb:AABB;

	bool m_tryToMove:Boolean;
	bool m_flyMode:Boolean;

	Player( );
	Vector2 *Initialise(Vector2 *pos, Map *map, Platformer *parent);
	void MakeTemporaryilyInvunerable( );
	bool get_m_HasWorldCollision( );
	void Update( float dt );
	void KeyboardControl( float dt );
	bool get_m_ApplyFriction( );
}