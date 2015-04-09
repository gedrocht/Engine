#pragma once

#include "AABB.h"
#include <vector>
#include "eTileTypes.h"
//#include "Platformer.h"
#include "Player.h"


//class Platformer; //FIXME

class Player;

using namespace std;

class Map{
public:
	Vector2 *m_gTileCenterOffset;
	Vector2 *m_gTileHalfExtents;

	AABB *m_aabbTemp;
	
	//Platformer *m_platformer; //FIXME
	//BEGIN PLATFORMER
	int PLATFORMER_kMaxCharacters;
	Player *PLATFORMER_m_player;
	//Map *PLATFORMER_m_map; //FIXME
	Player *PLATFORMER_get_m_Player( );
	void PLATFORMER_CreateTilesInner( vector<int> *tileSet, bool addtoScene );
	void PLATFORMER_Update( float dt );
	void PLATFORMER_DrawPoint( Vector2 *p, int colour, float radius );
	void PLATFORMER_ClearDynamicGfx( );
	//END PLATFORMER

	vector<int> m_Map;

	int m_width;
	int m_height; 

	Map();
	//Map( Platformer *platformer );
	void UnitTest( );
	int GetTile( int i, int j );
	int GetTileSafe( vector<int> map, int i, int j );
	static float TileCoordsToWorldX( int i );
	static float TileCoordsToWorldY( int j );
	int WorldCoordsToTileX( float worldX );
	int WorldCoordsToTileY( float worldY );
	int GetTileFromPos( Vector2 *pos );
	static bool IsTileObstacle( int tile );
	void FillInTileAabb( int i, int j, AABB *outAabb );
	//void DoActionToTilesWithinAabb( Vector2 *v_min, Vector2 *v_max, Function *action, float dt ); //FIXME
};