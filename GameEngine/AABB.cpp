#include "AABB.h"

AABB::AABB(){
	Initialize( new Vector2(), new Vector2() );
}

AABB::AABB( Vector2 *center, Vector2 *halfExtents ){
	Initialize( center, halfExtents );	
}

//void AABB::Initialize( //centre:Vector2, halfExtents:Vector2):void
void AABB::Initialize( Vector2 *center, Vector2 *halfExtents ){
	m_Center = center;
	m_HalfExtents = halfExtents;
}

Vector2 *AABB::get_m_Center( ){
	return m_Center;
}

void AABB::set_m_Center( Vector2 *p ){
	m_Center = p;
}

Vector2 *AABB::get_m_HalfExtents(){
	return m_HalfExtents;
}

Vector2 *AABB::get_m_BottomLeft(){
	return m_Center->Add( new Vector2(-m_HalfExtents->m_x, m_HalfExtents->m_y) );
}

Vector2 *AABB::get_m_BottomRight(){
	return m_Center->Add( new Vector2(m_HalfExtents->m_x, m_HalfExtents->m_y) );
}

Vector2 *AABB::get_m_TopLeft(){
	return m_Center->Add( new Vector2(-m_HalfExtents->m_x, -m_HalfExtents->m_y) );
}

Vector2 *AABB::get_m_TopRight(){
	return m_Center->Add( new Vector2(m_HalfExtents->m_x, -m_HalfExtents->m_y) );
}

Vector2 *AABB::get_m_Min(){
	return get_m_TopLeft();
}

Vector2 *AABB::get_m_Max(){
	return get_m_BottomRight();
}

Vector2 *AABB::MinInto( Vector2 *v ){
	v->CloneInto( m_Center );
	v->SubFrom( m_HalfExtents );
	
	return v;
}

void AABB::Enlarge( float amount ){
	m_HalfExtents->m_x += amount;
	m_HalfExtents->m_y += amount;
}

void AABB::EnlargeY( float amount ){
	m_HalfExtents->m_y += amount;
}

bool AABB::Overlap( IAABB *a, IAABB *b ){
	Vector2 *centerDelta = new Vector2();
	centerDelta->CloneInto( b->m_Center );
	centerDelta->SubFrom( a->m_Center );
	centerDelta->AbsTo();

	Vector2 *halfExtentsSum = new Vector2();



	halfExtentsSum->CloneInto( a->m_HalfExtents );
	halfExtentsSum->AddTo( b->m_HalfExtents );

	centerDelta->SubFrom( halfExtentsSum );

	return centerDelta->m_x < 0 && centerDelta->m_y < 0;
}

bool AABB::Within( Vector2 *p ){
	Vector2 *d = p->Sub( m_Center )->get_m_Abs();

	return d->m_x < m_HalfExtents->m_x && d->m_y < m_HalfExtents->m_y;
}

Vector2 *AABB::GetRandomPointWithin( float scaleX, float scaleY ){
	Vector2 *point = new Vector2();
	point->CloneInto( m_Center );
	point->m_x += Scalar::RandBetween( -m_HalfExtents->m_x, m_HalfExtents->m_x ) * scaleX;
	point->m_y += Scalar::RandBetween( -m_HalfExtents->m_y, m_HalfExtents->m_y ) * scaleY;

	return point;
}

Vector2 *AABB::ClampInto( Vector2 *candidate ){
	return candidate->SubFrom(m_Center)->ClampInto(get_m_Max(), get_m_Min())->AddTo(m_Center);
}

void AABB::UpdateFrom( Vector2 *center, Vector2 *halfExtents ){
	m_Center = center;
	m_HalfExtents = halfExtents;
}