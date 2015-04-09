#pragma once

#include "Vector2.h"
#include "IAABB.h"
#include "AABB.h"
#include "Contact.h"
#include "Map.h"

//class AABB;
class Map;

class Collide {
public:
	bool IsInternalCollision( int tileI, int tileJ, Vector2 *normal, Map *map );
	bool AabbVsAabbInternal( Vector2 *delta, Vector2 *aabbCenter, Vector2 *aabbHalfExtents, Vector2 *point, Contact *outContact );
	bool AabbVsAabb( IAABB *a, IAABB *b, Contact *outContact, int tileI, int tileJ, Map *map, bool checkInternal );
	bool PointInAabb( Vector2* point, AABB *aabb );
	bool AabbVsAabbTopPlane( IAABB *a, IAABB *b, Contact *outContact, int tileI, int tileJ, Map *map );
};