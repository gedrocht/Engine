#include "Map.h"

Map::Map(){
	m_gTileCenterOffset = new Vector2( kTileSize/2, kTileSize/2 );
	m_gTileHalfExtents = new Vector2( kTileSize/2, kTileSize/2 );
	m_platformer = new Platformer();

	m_aabbTemp = new AABB( );
}

Map::Map( Platformer *platformer ) {
	m_gTileCenterOffset = new Vector2( kTileSize/2, kTileSize/2 );
	m_gTileHalfExtents = new Vector2( kTileSize/2, kTileSize/2 );
	m_platformer = platformer;
		
	//Assert( m_Map.length==m_Width*m_Height, "Map dimensions don't match constants!" );
	
	m_aabbTemp = new AABB( );
}

/// Check some basic stuff with the coordinate system
void Map::UnitTest( ) {
	int iMin = 0;
	int jMin = 0;
	
	float xMin = TileCoordsToWorldX( iMin );
	float yMin = TileCoordsToWorldY( jMin );
	
	int iMax = 9;
	int jMax = 9;
	
	float xMax = TileCoordsToWorldX( iMax );
	float yMax = TileCoordsToWorldY( jMax );
	
	int iMinCheck = WorldCoordsToTileY( yMin );
	
	//Assert( iMin==iMinCheck, "UnitTest(): fail!" );
}

int Map::GetTile( int i, int j ) {
	return GetTileSafe( m_Map, i, j );
}

int Map::GetTileSafe( vector<int> map, int i, int j ) {
	if ( i >= 0 && i < m_width && j >= 0 && j < m_height )
	{
		return map[j*m_width+i];
	}
	else 
	{
		return kInvalid;
	}
}

/// calculate the position of a tile: 0,0 maps to Constants.kWorldHalfExtents
float Map::TileCoordsToWorldX( int i ) {
	return i*kTileSize - kWorldHalfExtents->m_x;
}

/// calculate the position of a tile: 0,0 maps to Constants.kWorldHalfExtents 
float Map::TileCoordsToWorldY( int j ) {
	return j*kTileSize - kWorldHalfExtents->m_y;
}

/// go from world coordinates to tile coordinates
int Map::WorldCoordsToTileX( float worldX ) {
	return ( worldX + kWorldHalfExtents->m_x )/kTileSize;
}

/// go from world coordinates to tile coordinates
int Map::WorldCoordsToTileY( float worldY ) {
	return ( worldY + kWorldHalfExtents->m_y )/kTileSize;
}

int Map::GetTileFromPos( Vector2 *pos ) {
	int i = WorldCoordsToTileX( pos->m_x );
	int j = WorldCoordsToTileY( pos->m_y );
	
	return GetTile( i, j );
}

bool Map::IsTileObstacle( int tile ) {
	return tile==kPlatform;
}

void Map::FillInTileAabb( int i, int j, AABB *outAabb ) {
	outAabb->Initialize( (new Vector2(
							TileCoordsToWorldX(i), 
							TileCoordsToWorldY(j)
						))->AddTo(m_gTileCenterOffset), m_gTileHalfExtents );
}

/// Call out to the action for each tile within the given world space bounds
/*
void Map::DoActionToTilesWithinAabb( Vector2 *v_min, Vector2 *v_max, Function *action, float dt ) { //FIXME
	// round down
	int minI = WorldCoordsToTileX(v_min->m_x);
	int minJ = WorldCoordsToTileY(v_min->m_y);
	
	// round up
	int maxI = WorldCoordsToTileX(v_max->m_x+0.5);
	int maxJ = WorldCoordsToTileY(v_max->m_y+0.5);
	
	for ( int i = minI; i<=maxI; i++ )
	{
		for ( int j = minJ; j<=maxJ; j++ )
		{
			// generate aabb for this tile
			FillInTileAabb( i, j, m_aabbTemp );
			
			// call the delegate on the main collision map
			action( m_aabbTemp, GetTile( i, j ), dt, i, j );
		}
	}
}
*/