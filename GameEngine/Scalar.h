#pragma once

#include <Math.h>
#include "Constants.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Scalar {
public:
	static const int kMaxRandValue = 65535;

	float Frac( float n );
	float Wrap( float x, float range );
	float EaseOut( float x );
	float EaseOutVel( float x );
	static float RandBetween( float a, float b );
	static int RandBetweenInt( int a, int b );
	int Randint( );
	int RandInt( );
	//float FromVector2( Vector2 *v );
	int MakeColour( int r, int g, int b );
	int RedFromColour( int c );
	int GreenFromColour( int c );
	int BlueFromColour( int c );
	float InfinityCurve( float x );
	/*
	ColorTransform *ColorTransformFromBGR( int bgr );
	ColorTransform *ColorTransformFromRGB( int rgb );
	*/
	float RadToDeg( float radians );
	static float Clamp( float a, float min, float max );
	static float Sign( float a );
};