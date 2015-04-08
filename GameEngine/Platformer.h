#include "Vector2.h"
#include "AABB.h"
#include "Map.h"

class Platformer //: GameLoop
{
	int kMaxCharacters = 50;

	Map *m_map;

	// fast allocator for vector2s, cleared once per frame
	VectorPool *m_gTempVectorPool;

	Keyboard *m_keyboard;
	Player *var m_player;
	Camera *var m_camera;

	vector<Sprite> *m_dynamicGfx;
	
	Platformer( );
	Keyboard *get m_Keyboard( );
	Player *get m_Player( );
	void CreateTilesInner( vector<int> *tileSet, bool addtoScene );
	void Update( float dt );
	void DrawPoint( Vector2 *p, int colour, float radius );
	void ClearDynamicGfx( );
	MoveableObject *SpawnMo( Class *type, Vector2 *pos, bool addToScene );
};