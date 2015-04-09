#include "Map.h"

Map::Map(){
	m_gTileCenterOffset = new Vector2( kTileSize/2, kTileSize/2 );
	m_gTileHalfExtents = new Vector2( kTileSize/2, kTileSize/2 );
	//m_platformer = new Platformer();



	/////BEGIN PLATFORMER


	//super( ); //TESTME
	
	PLATFORMER_kMaxCharacters = 50;

	// keyboard controller
	//m_keyboard = new Keyboard( this->stage );
	
	//m_dynamicGfx = new vector<Sprite>( );
	
	// create the single map and all the tiles which go with it
	//m_map = new SimpleMap(this);  //TESTME
	
	
	
	
	
	//////////
	//PLATFORMER_m_map = new Map();// new vector<int>(); //TESTME
	//////////
	
	
	
	
	
	//CreateTilesInner( m_map, true ); //TESTME
	
	// camera controls what we see
	//m_camera = new Camera( this, m_player );
	
	// set 30 fps
	// this->stage->frameRate = kDesiredFps;
	
	// start the update loop
	//Start( );



	/////END PLATFORMER



	m_aabbTemp = new AABB( );
}

/*
Map::Map( Platformer *platformer ) {
	m_gTileCenterOffset = new Vector2( kTileSize/2, kTileSize/2 );
	m_gTileHalfExtents = new Vector2( kTileSize/2, kTileSize/2 );
	m_platformer = platformer;
		
	//Assert( m_Map.length==m_Width*m_Height, "Map dimensions don't match constants!" );
	
	m_aabbTemp = new AABB( );
}
*/

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

int Map::GetTileSafe( vector<int> *map, int i, int j ) {
	if ( i >= 0 && i < m_width && j >= 0 && j < m_height )
	{
		return (*map)[j*m_width+i];
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

void Map::FillInTileAabb( int i, int j, AABB *outAabb, int TILE_WIDTH, int TILE_HEIGHT ) {
	outAabb->Initialize( (new Vector2(
							//TileCoordsToWorldX(i), 
							//TileCoordsToWorldY(j)
							i*TILE_WIDTH,
							i*TILE_HEIGHT
						))->AddTo(m_gTileCenterOffset), m_gTileHalfExtents );
}

/// Call out to the action for each tile within the given world space bounds

/*
void Map::DoActionToTilesWithinAabb( Vector2 *v_min, Vector2 *v_max, Function *action, float dt ) { //TESTME
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












//////////BEGIN PLATFORMER
/// Acessor for the keyboard
/*
Keyboard *Platformer::get_m_Keyboard( ) {

	return m_keyboard;
}
*/

/// Acessor for the player
Player *Map::PLATFORMER_get_m_Player( ) {
	return PLATFORMER_m_player;
}

/// Create all the tiles in the game
void Map::PLATFORMER_CreateTilesInner( vector<int> *tileSet, bool addtoScene ) {
	int index = 0;
	//for each( int tileCode in tileSet )
	int tileCode;
	for(vector<int>::iterator it = tileSet->begin() ; it != tileSet->end(); ++it){
		tileCode = *it;
		//MovieClip *tile;
		
		// calculate the position of each tile: 0,0 maps to Constants.kWorldHalfExtents
		int tileI = index % m_width;
		int tileJ = index / m_width;
		
		int tileX = Map::TileCoordsToWorldX(tileI);
		int tileY = Map::TileCoordsToWorldY(tileJ);
		
		Vector2 *tilePos = new Vector2( tileX, tileY );
		
		// create each tile
		switch ( tileCode )
		{
			//
			// foreground tiles
			//
			/*
			case kEmpty:
				//tile = 0;
				break;
				*/
			/*
			case kPlatform:
			{
				tile = new MovieClip( );
				tile.graphics.beginFill( 0xffffff );
				tile.graphics.drawRect( 0, 0, Constants.kTileSize, Constants.kTileSize );
				tile.graphics.endFill( );
			}
			break;
			*/
			
			
			//
			// characters
			//
			
			case kPlayer: 
			{
				//tile = m_player = new Player(SpawnMo( PlayerFla, tilePos ));
				tilePos = PLATFORMER_m_player->m_pos;
			}
			break;
		}
		
		/*
		if ( tile!=null )
		{
			tile->x = tilePos->m_x;
			tile->y = tilePos->m_y;
			tile->cacheAsBitmap = true;
			
			if ( addtoScene )
			{
				this.addChild( tile );
			}
		}
		*/

		index++;
	}
}

/*
void Platformer::Update( float dt ) {
	if ( dt>0 )
	{
		// fixed frame rate
		dt = 1.0/30.0;
		
		//m_keyboard->Update( );
		
		ClearDynamicGfx( );
		
		// update all moveable objects
		m_player->Update( dt );
		
		// camera depends on player
		//m_camera->Update( dt );
		
		// clear vector2 allocator
		//m_gTempVectorPool->Clear( );
	}
}
*/

/// Debug function
/*
void Platformer::DrawPoint( Vector2 *p, int colour, float radius ) {
	Sprite *spr = new Sprite( );
	
	spr.graphics.beginFill( colour );
	spr.graphics.drawCircle( 0, 0, radius );
	spr.graphics.endFill( );
	
	spr->x = p->m_x;
	spr->y = p->m_y;
	
	m_dynamicGfx->push( spr );
	this->addChild( spr );
}
*/

/// Debug function
/*
void Platformer::ClearDynamicGfx( ) {
	for each(Sprite *s in m_dynamicGfx)
	{
		this->removeChild( s );
	}
	
	m_dynamicGfx = new vector<Sprite>( );
}
*/

/// Spawn a MoveableObject of the given type at the given location
/*
MoveableObject *Platformer::SpawnMo( Class *type, Vector2 *pos, bool addToScene ) {
	Class *instance = new type();							
	instance->Initialise( pos, m_map, this, args );
	
	if ( addToScene )
	{
		this->addChild( instance );
	}
	
	return instance;
}
*/
////////////END PLATFORMER