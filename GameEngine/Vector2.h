#include "Constants.h"
#include "Point.h"
#include <string.h>

#pragma once

class Vector2 {
public:
	float m_x;
	float m_y;

	Vector2();
	Vector2( float x, float y );
	void Initialize( float x, float y );
	Vector2 *Add( Vector2 *v );
	Vector2 *AddTo( Vector2* v );
	Vector2 *SubFrom( Vector2 *v );
	Vector2* SubScalar( float s );
	Vector2* AddScalar( float s );
	Vector2* SubScalarFrom( float s );
	Vector2* AddScalarTo( float s );
	Vector2* AddX( float x );
	Vector2* AddY( float y );
	Vector2* SubX( float x );
	Vector2* SubY( float y );
	Vector2* AddXTo( float x );
	Vector2* AddYTo( float y );
	Vector2 *SubXFrom( float x );
	Vector2* SubYFrom( float y );
	Vector2* Sub( Vector2 *v );
	Vector2* Mul( Vector2 *v );
	Vector2* MulTo( Vector2 *v );
	Vector2* Div( Vector2 *v );
	Vector2* MulScalar( float s );
	Vector2* MulScalarTo( float s );
	Vector2* MulAddScalarTo( Vector2 *v, float s );
	Vector2* MulSubScalarTo( Vector2 *v, float s );
	float Dot( Vector2 *v );
	float get_m_LenSqr();
	float get_m_Len();
	Vector2* get_m_Abs();
	Vector2* get_m_Unit();
	Vector2* get_m_Floor();
	Vector2* Clamp( Vector2 *min, Vector2* max );
	Vector2* ClampInto( Vector2* min, Vector2* max );
	Vector2* get_m_Perp();
	Vector2* get_m_Neg();
	Vector2* NegTo( );
	bool Equal(Vector2* v);
	Vector2* FromAngle(float angle);
	float ToAngle();
	Vector2* RandomRadius(float r);
	Vector2* FromPoint( Point *point );
	Point* get_m_Point();
	void Clear( );
	Vector2* Clone( );
	//string toString( );
	Vector2* CloneInto( Vector2* v );
	Vector2* MaxInto( Vector2* b );
	Vector2* MinInto( Vector2* b );
	Vector2* Min( Vector2* b );
	Vector2* Max( Vector2* b );
	void AbsTo();
	Vector2* UnitTo();
	bool IsNaN( );
	Vector2* get_m_MajorAxis( );
	Vector2* FloorTo( );
	Vector2* RoundTo( );
};

Vector2 *kScreenDimensions = new Vector2(640,360);
Vector2 *kWorldHalfExtents;
Vector2 *kUnitYNeg = new Vector2(0,-1);
Vector2 *kExpand = new Vector2(5,5);