#include "Platformer.h"

Platformer::Platformer( ) {
	super( );
	
	// keyboard controller
	m_keyboard = new Keyboard( this->stage );
	
	// temporary vector2 pool for fast allocation
	m_gTempVectorPool = new VectorPool( 10000 );
	
	m_dynamicGfx = new vector<Sprite>( );
	
	// create the single map and all the tiles which go with it
	m_map = new SimpleMap(this);
	CreateTilesInner( m_map->m_Map );
	
	// camera controls what we see
	m_camera = new Camera( this, m_player );
	
	// set 30 fps
	this->stage->frameRate = kDesiredFps;
	
	// start the update loop
	Start( );
}

/// Acessor for the keyboard
Keyboard *Platformer::get m_Keyboard( ) {
	return m_keyboard;
}

/// Acessor for the player
Player *Platformer::get m_Player( ) {
	return m_player;
}

/// Create all the tiles in the game
void Platformer::CreateTilesInner( vector<int> *tileSet, bool addtoScene ) {
	var index:int = 0;
	for each( int tileCode in tileSet )
	{
		MovieClip *tile;
		
		// calculate the position of each tile: 0,0 maps to Constants.kWorldHalfExtents
		int tileI = index % m_map->m_Width;
		int tileJ = index / m_map->m_Width;
		
		int tileX = Map::TileCoordsToWorldX(tileI);
		int tileY = Map::TileCoordsToWorldY(tileJ);
		
		Vector2 *tilePos = new Vector2( tileX, tileY );
		
		// create each tile
		switch ( tileCode )
		{
			//
			// foreground tiles
			//
			
			case eTileTypes::kEmpty:
				tile = 0;
				break;
			case eTileTypes::kPlatform:
			{
				/*
				tile = new MovieClip( );
				tile.graphics.beginFill( 0xffffff );
				tile.graphics.drawRect( 0, 0, Constants.kTileSize, Constants.kTileSize );
				tile.graphics.endFill( );
				*/
			}
			break;
			
			
			
			//
			// characters
			//
			
			case eTileTypes::kPlayer:
			{
				tile = m_player = new Player(SpawnMo( PlayerFla, tilePos ));
				tilePos = m_player->m_Pos;
			}
			break;
		}
		
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
		
		index++;
	}
}

void Platformer::Update( float dt ) {
	if ( dt>0 )
	{
		// fixed frame rate
		dt = 1.0/30.0;
		
		m_keyboard->Update( );
		
		ClearDynamicGfx( );
		
		// update all moveable objects
		m_player->Update( dt );
		
		// camera depends on player
		m_camera->Update( dt );
		
		// clear vector2 allocator
		m_gTempVectorPool->Clear( );
	}
}

/// Debug function
void Platformer::DrawPoint( Vector2 *p, int colour, float radius ) {
	Sprite *spr = new Sprite( );
	
	/*
	spr.graphics.beginFill( colour );
	spr.graphics.drawCircle( 0, 0, radius );
	spr.graphics.endFill( );
	*/
	
	spr->x = p->m_x;
	spr->y = p->m_y;
	
	m_dynamicGfx->push( spr );
	this->addChild( spr );
}

/// Debug function
void Platformer::ClearDynamicGfx( ) {
	for each(Sprite *s in m_dynamicGfx)
	{
		this->removeChild( s );
	}
	
	m_dynamicGfx = new vector<Sprite>( );
}

/// Spawn a MoveableObject of the given type at the given location
MoveableObject *Platformer::SpawnMo( Class *type, Vector2 *pos, bool addToScene ) {
	Class *instance = new type();							
	instance->Initialise( pos, m_map, this, args );
	
	if ( addToScene )
	{
		this->addChild( instance );
	}
	
	return instance;
}