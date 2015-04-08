#include "Vector2.h"

class Map{
	Vector2 *m_gTileCentreOffset:Vector2 = new Vector2( kTileSize/2, kTileSize/2 );
	Vector2 *m_gTileHalfExtents:Vector2 = new Vector2( kTileSize/2, kTileSize/2 );

	AABB *m_aabbTemp;
	Platformer *m_platformer;

	Map( Platformer *platformer );
	void UnitTest( );
	int GetTile( int i, int j );
	int GetTileSafe( Vector<int> map, int i, int j );
	float TileCoordsToWorldX( int i );
	float TileCoordsToWorldY( int j );
	int WorldCoordsToTileX( float worldX );
	int WorldCoordsToTileY( float worldY );
	int GetTileFromPos( Vector2 *pos );
	bool IsTileObstacle( int tile );
	void FillInTileAabb( int i, int j, AABB *outAabb );
	void DoActionToTilesWithinAabb( Vector2 *v_min, Vector2 *v_max, Function *action, float dt );
};