#pragma once

#include <Math.h>

#define PI 3.141593

#ifndef MIN_MAX
#define MIN_MAX

static float kGravity = 100;
static float kTwoPi = PI*2;
static float kMaxSpeed = 300;
static int kTileSize = 64;
static float k24FpsTimeStep = 1.0/24.0;
static float kDesiredFps = 30.0;
static float kPlaneHeight = 12;
static int kPlayerWidth = 30;

static float _max( float a, float b ){
	if( a > b )
		return a;
	else
		return b;
}

static float _min( float a, float b ){
	if( a < b )
		return a;
	else
		return b;
}

#endif