#include "Texture.h"
#include <iostream>

Texture::Texture( char *path, int x, int y, int width, int height ){
	this->setRect( x, y, width, height );

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glFrontFace(GL_CW);

    texture = SOIL_load_OGL_texture(
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if( 0 == texture )
        fprintf( stderr, "SOIL loading error: '%s'\n", SOIL_last_result());
}

void Texture::setRect( int x, int y, int width, int height ){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	calcLeft();
	calcRight();
	calcTop();
	calcBottom();
}

void Texture::calcLeft(){
	this->left = x;
}

void Texture::calcRight(){
	this->right = x + width;
}

void Texture::calcTop(){
	this->top = y;
}

void Texture::calcBottom(){
	this->bottom = y + height;
}

int Texture::getX(){ return x; }
int Texture::getY(){ return y; }
int Texture::getWidth(){ return width; }
int Texture::getHeight(){ return height; }
int Texture::getLeft(){ return left; }
int Texture::getRight(){ return right; }
int Texture::getTop(){ return top; }
int Texture::getBottom(){ return bottom; }

void Texture::setX( int x ){
	this->x = x;
	calcLeft();
	calcRight();
}

void Texture::setY( int y ){
	this->y = y;
	calcTop();
	calcBottom();
}

void Texture::setWidth( int width ){
	this->width = width;
	calcLeft();
	calcRight();
}

void Texture::setHeighT( int height ){
	this->height = height;
	calcTop();
	calcBottom();
}

bool Texture::isColliding( Texture *other ){
	if( left >= other->left && left <= other->right ){
		if( bottom >= other->top && bottom <= other->bottom )
			return true;
	}

	return false;
}

bool Texture::isOnTopOf( Texture *other ){
	if( bottom + 1 == other->top &&
		left >= other->left && left <= other->right  )
			return true;
	return false;
}

void Texture::DEBUG_printSelf(){
	printf( "x: %d\ny: %d\nwidth: %d\nheight: %d\nleft: %d\nright: %d\ntop: %d\nbottom: %d\n",
			getX(),
			getY(),
			getWidth(),
			getHeight(),
			getLeft(),
			getRight(),
			getTop(),
			getBottom() );
}