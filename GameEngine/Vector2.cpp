#include "Vector2.h"

Vector2::Vector2(){
	this->m_x = 0;
	this->m_y = 0;
}

Vector2::Vector2( float x, float y ) {
    Initialize( x, y );
}

void Vector2::Initialize( float x, float y ) {
    m_x = x;
    m_y = y;
}

Vector2 *Vector2::Add( Vector2 *v ) {
    return new Vector2(m_x + v->m_x, m_y + v->m_y);
}

Vector2 *Vector2::AddTo( Vector2* v ) {
    m_x += v->m_x;
    m_y += v->m_y;
    
    return this;
}

Vector2 *Vector2::SubFrom( Vector2 *v ) {
    m_x -= v->m_x;
    m_y -= v->m_y;
    
    return this;
}

Vector2* Vector2::SubScalar( float s ) {
    return new Vector2( m_x-s, m_y-s );
}

Vector2* Vector2::AddScalar( float s ) {
    return new Vector2( m_x+s, m_y+s );
}

Vector2* Vector2::SubScalarFrom( float s ) {
    m_x -= s;
    m_y -= s;
    
    return this;
}

Vector2* Vector2::AddScalarTo( float s ) {
    m_x += s;
    m_y += s;
    
    return this;
}

Vector2* Vector2::AddX( float x ) {
    return new Vector2(m_x + x, m_y);
}

Vector2* Vector2::AddY( float y ) {
    return new Vector2(m_x, m_y+y);
}

Vector2* Vector2::SubX( float x ) {
    return new Vector2(m_x-x, m_y);
}

Vector2* Vector2::SubY( float y ) {
    return new Vector2(m_x, m_y-y);
}

Vector2* Vector2::AddXTo( float x ) {
    m_x += x;
    return this;
}

Vector2* Vector2::AddYTo( float y ) {
    m_y += y;
    return this;
}

Vector2 *Vector2::SubXFrom( float x ) {
    m_x -= x;
    return this;
}

Vector2* Vector2::SubYFrom( float y ) {
    m_y -= y;
    return this;
}

Vector2* Vector2::Sub( Vector2 *v ) {
    return new Vector2(m_x - v->m_x, m_y - v->m_y);
}

Vector2* Vector2::Mul( Vector2 *v ) {
    return new Vector2(m_x * v->m_x, m_y * v->m_y);
}

Vector2* Vector2::MulTo( Vector2 *v ) {
    m_x *= v->m_x;
    m_y *= v->m_y;
    return this;
}

Vector2* Vector2::Div( Vector2 *v ) {
    return new Vector2(m_x / v->m_x, m_y / v->m_y);
}

Vector2* Vector2::MulScalar( float s ) {
    return new Vector2(m_x * s, m_y * s);
}

Vector2* Vector2::MulScalarTo( float s ) {
    m_x *= s;
    m_y *= s;
    
    return this;
}

/// Multiples v by s and then adds to the current vector
Vector2* Vector2::MulAddScalarTo( Vector2 *v, float s ) {
    m_x += v->m_x*s;
    m_y += v->m_y*s;
    
    return this;
}

/// Multiples v by s and then subtracts from the current vector
Vector2* Vector2::MulSubScalarTo( Vector2 *v, float s ) {
    m_x -= v->m_x*s;
    m_y -= v->m_y*s;
    
    return this;
}

float Vector2::Dot( Vector2 *v ) {
    return m_x * v->m_x + m_y * v->m_y;
}

float Vector2::get_m_LenSqr() {
    return Dot(this);
}

float Vector2::get_m_Len() {
    return sqrt( get_m_LenSqr() );
}

Vector2* Vector2::get_m_Abs() {
    return new Vector2( abs( m_x ), abs( m_y ) );
}

Vector2* Vector2::get_m_Unit() {
    float invLen = 1.0 / get_m_Len();
    return MulScalar(invLen);
}

Vector2* Vector2::get_m_Floor() {
    return new Vector2(floor(m_x), floor(m_y));
}

Vector2* Vector2::Clamp( Vector2 *v_min, Vector2* v_max ) {
    return new Vector2
                (
                    max( min(m_x, v_max->m_x), v_min->m_x ),
                    max( min(m_y, v_max->m_y), v_min->m_y )
                );
}

Vector2* Vector2::ClampInto( Vector2* v_min, Vector2* v_max ) {
    m_x = max( min( m_x, v_max->m_x ), v_min->m_x );
    m_y = max( min( m_y, v_max->m_y ), v_min->m_y );
    
    return this;
}

Vector2* Vector2::get_m_Perp() {
    return new Vector2( -m_y, m_x);
}

Vector2* Vector2::get_m_Neg() {
    return new Vector2( -m_x, -m_y);
}

Vector2* Vector2::NegTo( ) {
    m_x = -m_x;
    m_y = -m_y;
    
    return this;
}

bool Vector2::Equal(Vector2* v) {
    return m_x == v->m_x && m_y == v->m_y;
}

Vector2* Vector2::FromAngle(float angle) {
    return new Vector2(cos(angle), sin(angle));
}

float Vector2::ToAngle() {
    float angle = atan2(m_y, m_x);

    // make the returned range 0 -> 2*PI
    if (angle < 0.0)
    {
		angle += kTwoPi;
    }
    return angle;
}

Vector2 *Vector2::RandomRadius(float r) {
    return (new Vector2
                (
                    random() * 2 - 1,
                    random() * 2 - 1
                ))->MulScalar( r );
}

Vector2* Vector2::FromPoint( Point *point ) {
    return new Vector2(point->x,point->y);
}

Point* Vector2::get_m_Point() {
    return new Point(m_x, m_y);
}

void Vector2::Clear( ) {
    m_x=0;
    m_y=0;
}

Vector2* Vector2::Clone( ) {
    return new Vector2(m_x, m_y);
}

Vector2* Vector2::CloneInto( Vector2* v ) {
    m_x = v->m_x;
    m_y = v->m_y;
    return this;
}

Vector2* Vector2::MaxInto( Vector2* b ) {
    m_x = max( m_x, b->m_x );
    m_y = max( m_y, b->m_y );
    
    return this;
}

Vector2* Vector2::MinInto( Vector2* b ) {
    m_x = min( m_x, b->m_x );
    m_y = min( m_y, b->m_y );
    
    return this;
}

Vector2* Vector2::Min( Vector2* b ) {
    return (new Vector2( m_x, m_y ))->MinInto( b );
}

Vector2* Vector2::Max( Vector2* b ) {
    return (new Vector2( m_x, m_y ))->MaxInto( b );
}

void Vector2::AbsTo() {
    m_x = abs( m_x );
    m_y = abs( m_y );
}

Vector2* Vector2::UnitTo() {
    float invLen = 1.0 / get_m_Len();
    m_x *= invLen;
    m_y *= invLen;
    return this;
}

/// Get the largest coordinate and return a signed, unit vector containing only that coordinate
Vector2* Vector2::get_m_MajorAxis( ) {
    if ( abs( m_x )>abs( m_y ) ) {
        return new Vector2( Scalar->Sign(m_x), 0 );
    } else {
        return new Vector2( 0, Scalar->Sign(m_y) );
    }
}

Vector2* Vector2::FloorTo( ) {
    m_x = floor( m_x );
    m_y = floor( m_y );
    return this;
}

Vector2* Vector2::RoundTo( ) {
    m_x = floor( m_x+0.5 );
    m_y = floor( m_y+0.5 );
    return this;
}