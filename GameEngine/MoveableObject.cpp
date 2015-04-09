#include "MoveableObject.h"

MoveableObject::MoveableObject( ) {
	//super( ); //FIXME
	kGroundFriction = 0.6;
	
	// get collsion radius
	m_radius = kPlayerWidth/2;
	m_halfExtents = new Vector2( m_radius, m_radius );
	
	m_vel = new Vector2( );
	m_posCorrect = new Vector2( );
	
	m_contact = new Contact( );
	
	m_dead = false;
}

/// Replaces the constructor since we can't have any parameters due to the CS4 symbol inheritance
Vector2 *MoveableObject::Initialize( Vector2* pos, Map *map, Platformer* parent ) {
	// position in the centre of the tile in the X and resting on the bottom of the tile in the Y
	//if ( m_TileMapped ) //FIXME
	if( true ) //FIXME
	{
		pos->m_x += kTileSize/2;
		pos->m_y += kTileSize-m_radius;
	}
	
	m_pos = pos;
	//m_platformer = parent; //FIXME
	m_map = map;
	
	return pos;
}

float MoveableObject::get_m_Radius( ) {
	return m_radius;
}

Vector2* MoveableObject::get_m_Centre( ) {
	return m_pos;
}

Vector2* MoveableObject::get_m_HalfExtents( ) {
	return m_halfExtents;
}

Vector2* MoveableObject::get_m_Pos( ) {
	return m_pos;
}

void MoveableObject::set_m_Pos( Vector2 *pos ) {
	m_pos = pos;
	
	// update visual
	/*
	this->x = pos->m_x;
	this->y = pos->m_y;
	*/

}

Vector2* MoveableObject::get_m_Vel( ) {
	return m_vel;
}

void MoveableObject::set_m_Vel( Vector2* vel ) {
	m_vel = vel;
}

bool MoveableObject::get_m_OnGround( ) {
	return m_onGround;
}

bool MoveableObject::get_m_OnGroundLast( ) {
	return m_onGroundLast;
}

bool MoveableObject::get_m_TileMapped( ) {
	return true;
}

bool MoveableObject::get_m_Dead( ) {
	return m_dead;
}

void MoveableObject::set_m_Dead( bool dead ) {
	m_dead = dead;
}

/// Apply gravity, do collision and integrate position
void MoveableObject::Update( float dt ) {
	//if ( m_ApplyGravity )  //FIXME
	if( true ) //FIXME
	{
		m_vel->AddYTo( kGravity );
		
		// clamp max speed
		m_vel->m_y = min( m_vel->m_y, kMaxSpeed*2 );
	}
	
	//if ( m_HasWorldCollision )
	if( true )  //FIXME
	{
		// do complex world collision
		Collision( dt );
	}
	
	// integrate position
	m_pos->MulAddScalarTo( m_vel->Add(m_posCorrect), dt );
	
	// force the setter to act
	this->m_pos = m_pos;
	m_posCorrect->Clear( );
}

bool MoveableObject::get_m_HasWorldCollision( ) {
	return false;
}

bool MoveableObject::get_m_ApplyGravity( ) {
	return false;
}

bool MoveableObject::get_m_ApplyFriction( ) {
	return false;
}

bool MoveableObject::get_m_ForceUpdate( ) {
	return false;
}

void MoveableObject::PreCollisionCode( ) {
	m_onGroundLast = m_onGround;
	m_onGround = false;
}

void MoveableObject::PostCollisionCode( ) {
}

/// Do collision detection and response for this object
void MoveableObject::Collision( float dt ) {
	// where are we predicted to be next frame?
	//Vector2 *predictedPos = Platformer::m_gTempVectorPool->AllocateClone( m_pos )->MulAddScalarTo( m_vel, dt );  //FIXME
	Vector2 *predictedPos = (new Vector2( m_pos->m_x, m_pos->m_y))->MulAddScalarTo( m_vel, dt );  //FIXME
	
	// find min/max
	Vector2 *v_min = m_pos->Min( predictedPos );
	Vector2 *v_max = m_pos->Max( predictedPos );
	
	// extend by radius
	v_min->SubFrom( m_halfExtents );
	v_max->AddTo( m_halfExtents );
	
	// extend a bit more - this helps when player is very close to boundary of one map cell
	// but not intersecting the next one and is up a ladder
	v_min->SubFrom( kExpand );
	v_max->AddTo( kExpand );
	
	PreCollisionCode( );
	
	//m_map->DoActionToTilesWithinAabb( v_min, v_max, InnerCollide, dt ); //FIXME
	
	PostCollisionCode( );
}

/// Inner collision response code
void MoveableObject::InnerCollide( AABB *tileAabb, int tileType, float dt, int i, int j ) {
	// is it collidable?
	if ( Map::IsTileObstacle( tileType ) )
	{
		// standard collision responce
		//bool collided = Collide::AabbVsAabb( this, tileAabb, m_contact, i, j, m_map, true ); //FIXME //FIXME
		bool collided = false; //FIXME
		if ( collided )
		{
			CollisionResponse( m_contact->m_normal, m_contact->m_dist, dt );
		}
	}
}

void MoveableObject::LandingTransition( ) {
}

/// Collision Reponse - remove normal velocity
void MoveableObject::CollisionResponse( Vector2 *normal, float dist, float dt ) {
	// get the separation and penetration separately, this is to stop pentration 
	// from causing the objects to ping apart
	float separation = max( dist, 0 );
	float penetration = min( dist, 0 );
	
	// compute relative normal velocity require to be object to an exact stop at the surface
	float nv = m_vel->Dot( normal ) + separation/dt;
	
	// accumulate the penetration correction, this is applied in Update() and ensures
	// we don't add any energy to the system
	m_posCorrect->SubFrom( normal->MulScalar( penetration/dt ) );
	
	if ( nv < 0 )
	{
		// remove normal velocity
		m_vel->SubFrom( normal->MulScalar( nv ) );
		
		// is this some ground?
		if ( normal->m_y < 0 )
		{
			m_onGround = true;
			
			// friction
			//if ( m_ApplyFriction )  //FIXME
			if( true )  //FIXME
			{
				// get the tanget from the normal (perp vector)
				Vector2 *tangent = normal->get_m_Perp();
				
				// compute the tangential velocity, scale by friction
				float tv = m_vel->Dot( tangent )*kGroundFriction;
				
				// subtract that from the main velocity
				m_vel->SubFrom( tangent->MulScalar( tv ) );
			}
			
			if (!m_onGroundLast)
			{
				// this transition occurs when this object 'lands' on the ground
				LandingTransition( );
			} 
		}
	}
}

/// Is the given candidate heading towards towardsPoint? 
bool MoveableObject::HeadingTowards( Vector2 *towardsPoint, MoveableObject *candidate ) {
	float deltaX = towardsPoint->m_x - candidate->m_pos->m_x;
	bool headingTowards = deltaX*candidate->m_vel->m_x > 0;
	
	return headingTowards;
}
