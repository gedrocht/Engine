#include <Math.h>
#include "Vector2.h"

class Scalar {
	int kMaxRandValue = 65535;

	float Frac( n:Number );
	float Wrap( float *x, float *range );
	float EaseOut( float x );
	float EaseOutVel( float x );
	float RandBetween( float a, float b );
	int RandBetweenInt( int a, int b );
	int Randint( );
	int RandInt( );
	float FromVector2( Vector2 *v );
	int MakeColour( int r, int g, int b );
	int RedFromColour( int c );
	int GreenFromColour( int c );
	int BlueFromColour( int c );
	float InfinityCurve( float x );
	ColorTransform *ColorTransformFromBGR( int bgr );
	ColorTransform *ColorTransformFromRGB( int rgb );
	float RadToDeg( float radians );
	float Clamp( float a, float min, float max );
	float Sign( float a );
};