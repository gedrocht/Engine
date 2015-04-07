#include "Physical.h"

#include <iostream>
using namespace std;

Physical::Physical( Texture *texture ){
	this->Vx = 0;
	this->Vy = 0;
	this->texture = texture;
	this->active = false;
}

void Physical::update(){
	if( Vx != 0 )
		this->texture->setX( this->texture->getX() + Vx );
	if( Vy != 0 )
		this->texture->setY( this->texture->getY() + Vy );
}