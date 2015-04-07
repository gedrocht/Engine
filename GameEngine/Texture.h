#define FREEGLUT_STATIC
#include "Libraries/freeglut/glut.h"  // GLUT, include glu.h and gl.h
#include "Libraries/soil/SOIL.h"

#pragma once

class Texture{
	int x,
		y,
		width,
		height,
		left,
		right,
		top,
		bottom;
	void setRect( int x, int y, int width, int height );
public:
	Texture( char *path, int x, int y, int width, int height );
	GLuint texture;
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getLeft();
	int getRight();
	int getTop();
	int getBottom();
	void setX( int x );
	void setY( int y );
	void setWidth( int width );
	void setHeighT( int height );
	void calcLeft();
	void calcRight();
	void calcTop();
	void calcBottom();
	bool isColliding( Texture *other );
	bool isOnTopOf( Texture *other );
	void DEBUG_printSelf();
};