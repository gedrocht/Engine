/*
#pragma once

#include "Vector2.h"
#include "Map.h"
#include "Player.h"
#include <vector>

using namespace std;

class Player;

class Platformer //: GameLoop
{
public:
	int kMaxCharacters;

	Map *m_map;

	// fast allocator for vector2s, cleared once per frame
	//VectorPool *m_gTempVectorPool; //FIXME

	//Keyboard *m_keyboard;
	Player *m_player;
	//Camera *m_camera;

	//vector<Sprite> *m_dynamicGfx;
	
	Platformer( );
	//Keyboard *get m_Keyboard( );
	Player *get_m_Player( );
	void CreateTilesInner( vector<int> *tileSet, bool addtoScene );
	void Update( float dt );
	void DrawPoint( Vector2 *p, int colour, float radius );
	void ClearDynamicGfx( );
	//MoveableObject *SpawnMo( Class *type, Vector2 *pos, bool addToScene );
};
*/