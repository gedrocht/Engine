#include "Scalar.h"


int kMaxRandValue = 65535;

/// Return only the fractional component of n - always positive
float Scalar::Frac( float n ) {
	float _abs = abs( n );
	return _abs-floor( _abs );
}

/// x = 1.5, range = 1
/// t = 1.5 / 1 = 1.5
/// ft = 0.5
/// return = 1*0.5 = 0.5 
float Scalar::Wrap( float x, float range ) {
	float t = x / range;
	float ft = Frac(t);
	return range * ft;
}

float Scalar::EaseOut( float x ) {
	float a=x-1;
	return a*a*a + 1;
}

float Scalar::EaseOutVel( float x ) {
	float a=x-1;
	return a*a*3;
}

float Scalar::RandBetween( float a, float b ) {
	//return random( )*( b-a )+a;

	return (rand() % (int)(b*100.0-a*100.0) + (int)(a*100.0))/100.0; //TESTME
}

int Scalar::RandBetweenInt( int a, int b ) {
	return int(RandBetween( a, b ));
}

int Scalar::Randint( ) {
	//return int(random( )*kMaxRandValue);
	return rand() % kMaxRandValue; //TESTME
}

int Scalar::RandInt( ) {
	//return int(random( )*kMaxRandValue);
	return rand() % kMaxRandValue; //TESTME 
}

/*
float Scalar::FromVector2( Vector2 *v ) {
	return atan2( v->m_y, v->m_x );
}
*/

/// 0xrrggbb
int Scalar::MakeColour( int r, int g, int b ) {
	return r|( g<<8 )|( b<<16 );
}

int Scalar::RedFromColour( int c ) {
	return c&0xff;
}

int Scalar::GreenFromColour( int c ) {
	return (c>>8)&0xff;
}

int Scalar::BlueFromColour( int c ) {
	return (c>>16)&0xff;
}

float Scalar::InfinityCurve( float x ) {
	return -1/(x+1) + 1;
}

/*
ColorTransform *Scalar::ColorTransformFromBGR( int bgr ) {
	return new ColorTransform( Scalar.BlueFromColour( bgr )/255.0, Scalar.GreenFromColour( bgr )/255.0, Scalar.RedFromColour( bgr )/255.0 );
}

ColorTransform *Scalar::ColorTransformFromRGB( int rgb ) {
	return new ColorTransform( Scalar.RedFromColour( rgb )/255.0, Scalar.GreenFromColour( rgb )/255.0, Scalar.BlueFromColour( rgb )/255.0 );
}
*/

float Scalar::RadToDeg( float radians ) {
	return ( radians/PI )*180;
}

float Scalar::Clamp( float a, float f_min, float f_max ) {
	a = _max( f_min, a );
	a = _min( f_max, a );
	return a;
}

float Scalar::Sign( float a ) {
	return a>=0 ? 1 : -1;
}