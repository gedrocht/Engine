#include "Player.h"

Player::Player( ) {
	//super(); //FIXME
	
	// how high do they jump?
	kPlayerJumpVel = 900*1.2;

	// how many frames does tha player flash for?
	kHurtFrames = 120;

	// controls how fast the player's velocity moves towards the target velocity
	// 1.0 = in one frame, 0 = never
	kReachTargetScale = 0.7;

	// how fast the player walks
	kWalkSpeed = 80;

	m_flyMode = false;
	
	// temporary storage for collision against tiles
	m_tileAabb = new AABB( );
				
	m_velTarget = new Vector2( );
}

/// Replaces the constructor since we can't have any parameters due to the CS4 symbol inheritance
Vector2 *Player::Initialize(Vector2 *pos, Map *map, Platformer *parent) {
	//Vector2 *newPos = super->Initialise( pos, map, parent ); //FIXME
	Vector2 *newPos = new Vector2();

	this->m_velTarget = new Vector2( );
	//m_keyboard = parent.m_Keyboard;
	
	return newPos;
}

/*
void Player::MakeTemporaryilyInvunerable( ) {
	m_hurtTimer = kHurtFrames;
}
*/

bool Player::get_m_HasWorldCollision( ) {
	return true;
}

void Player::Update( float dt ) {
	// player contol
	//KeyboardControl( dt ); //FIXME
	
	// integrate velocity
	if ( m_flyMode )
	{
		m_vel->MulScalarTo( 0.5 );
	}
	else
	{
		m_vel->AddYTo( kGravity );
	}
	
	// clamp speed
	m_vel->m_x = Scalar::Clamp( m_vel->m_x, -kMaxSpeed, kMaxSpeed );
	m_vel->m_y = min( m_vel->m_y, kMaxSpeed*2 );
	
	//super.Update( dt ); //FIXME
	
	/*
	if ( m_hurtTimer>0 )
	{
		//this.visible = (m_hurtTimer&1) == 1;
		m_hurtTimer--;
	}
	*/
}
/*
void Player::KeyboardControl( float dt ) {
	/*
	m_tryToMove = false;
	
	float moveSpeed;
	
	if ( m_flyMode )
	{
		moveSpeed = kWalkSpeed*4;
	}
	else 
	{
		moveSpeed = m_OnGround ? kWalkSpeed : kWalkSpeed/2;
	}
	
	m_velTarget.Clear( );
	
	
	//
	// normal walking controls
	//
	
	if ( m_keyboard->IsKeyDown( eKeyCodes::kLeftArrow ) )
	{
		m_vel->m_x -= moveSpeed;
		m_tryToMove = true;
		
		// face left
		this->scaleX = -1;
	}
	if ( m_keyboard->IsKeyDown( eKeyCodes::kRightArrow ) )
	{
		m_vel->m_x += moveSpeed;
		m_tryToMove = true;
		
		// face right
		this.scaleX = 1;
	}
	
	if (m_flyMode)
	{
		if ( m_keyboard->IsKeyDown( eKeyCodes::kUpArrow ) )
		{
			// fly mode controls
			m_vel->m_y -= moveSpeed;
			
			m_tryToMove = true;
		}
	}
	else
	{
		//
		// jump controls
		//
		
		if ( m_keyboard->IsKeyDownTransition( eKeyCodes::kUpArrow ) )
		{
			if ( m_OnGround )
			{
				m_vel->m_y -= kPlayerJumpVel;
			}
		}
	}
	*/
//}
	
bool Player::get_m_ApplyFriction( ) {
	return !m_tryToMove;
}
