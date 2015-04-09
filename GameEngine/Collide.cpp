#include "Collide.h"

/// Helper function which checks for internal edges
bool Collide::IsInternalCollision( int tileI, int tileJ, Vector2 *normal, Map *map ){
	int nextTileI = tileI + normal->m_x;
	int nextTileJ = tileJ + normal->m_y;
	
	int currentTile = map->GetTile( tileI, tileJ );
	int nextTile = map->GetTile( nextTileI, nextTileJ );
	
	bool internalEdge = map->IsTileObstacle(nextTile);
	
	return internalEdge;
}

/// Returns information about distance and direction from point to AABB
bool Collide::AabbVsAabbInternal( Vector2 *delta, Vector2 *aabbCenter, Vector2 *aabbHalfExtents, Vector2 *point, Contact *outContact ){
	// form the closest plane to the point
	Vector2* planeN = delta->get_m_MajorAxis()->NegTo();
	Vector2* planeCentre = planeN->Mul( aabbHalfExtents )->AddTo(aabbCenter);
	
	// distance point from plane
	Vector2* planeDelta = point->Sub( planeCentre );
	float dist = planeDelta->Dot( planeN );
	
	// form point
	
	// build and push
	outContact->Initialize( planeN, dist, point );
	
	// collision?
	return true;
}

bool Collide::AabbVsAabb( IAABB *a, IAABB *b, Contact *outContact, int tileI, int tileJ, Map *map, bool checkInternal ){
	//Vector2* combinedExtentsB = Platformer::m_gTempVectorPool->AllocateClone( b->m_HalfExtents )->AddTo(a->m_HalfExtents);
	Vector2 *combinedExtentsB = (new Vector2( b->get_m_HalfExtents()->m_x, b->get_m_HalfExtents()->m_y ))->AddTo(a->m_HalfExtents ); //TESTME
	Vector2* combinedPosB = b->m_Center;
	
	Vector2* delta = combinedPosB->Sub(a->m_Center);
	
	AabbVsAabbInternal( delta, combinedPosB, combinedExtentsB, a->m_Center, outContact );
	
	//
	// check for internal edges
	//
	
	if( checkInternal ){
		return !IsInternalCollision( tileI, tileJ, outContact->m_normal, map );
	} else  {
		return true;
	}
}

bool Collide::PointInAabb( Vector2* point, AABB *aabb ){
	Vector2* delta = point->Sub( aabb->m_Center );
	
	return	abs(delta->m_x) < aabb->m_HalfExtents->m_x &&
			abs(delta->m_y) < aabb->m_HalfExtents->m_y;
}

/// Only collide with the top plane of Aabb b
bool Collide::AabbVsAabbTopPlane( IAABB *a, IAABB *b, Contact *outContact, int tileI, int tileJ, Map *map ){
	bool collideAabb = AabbVsAabb( a, b, outContact, tileI, tileJ, map, false );
	if( collideAabb ) {
		// these conditions ensure that we only collide with the top plane, and that we have to be greater than 
		// -Constants.kPlaneHeight away from the surface for this collision to return true
		if ( outContact->m_normal->m_y < 0 && outContact->m_dist >= -kPlaneHeight ){
			return true;
		}
	}
	
	return false;
}
