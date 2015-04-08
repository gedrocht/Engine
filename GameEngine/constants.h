
#include <Math.h>

#pragma once

#define PI 3.141593

float kGravity = 100;
float kTwoPi = PI*2;
float kMaxSpeed = 300;
int kTileSize = 64;
float k24FpsTimeStep = 1.0/24.0;
float kDesiredFps = 30.0;
float kPlaneHeight = 12;
int kPlayerWidth = 30;

int max( float a, float b ){
	if( a > b )
		return a;
	else
		return b;
}

int min( float a, float b ){
	if( a < b )
		return a;
	else
		return b;
}