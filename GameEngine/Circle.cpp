#include "Circle.h"

Circle::Circle( Vector2 *pos, float radius ){
    m_pos=pos;
    m_radius=radius;
}

Vector2 *Circle::get_m_Pos(){
    return m_pos;
}

void Circle::set_m_Pos( Vector2 *p ){
    m_pos = p;
}

float Circle::get_m_Radius(){
    return m_radius;
}

void Circle::set_m_Radius( float newRadius ){
    m_radius = newRadius;
}

bool Circle::Contains( Vector2 *p ){
	float radius = m_radius - kTouchingThresh;
    return p->Sub(m_pos)->get_m_LenSqr() < radius*radius;
}

float Circle::DistanceToPoint( Vector2 *p ){
    return p->Sub( m_pos )->get_m_Len() - m_radius;
}

Vector2 *Circle::ClosestPointOnEdge( Vector2 *p, float bias ){
	Vector2 *d = p->Sub(m_pos);
    return d->get_m_Unit()->MulScalar(m_radius-bias)->Add(m_pos);
}

PointAndDistanceContainer *Circle::ClosestPointAndDistOnEdge( Vector2 *p ){
	Vector2 *d = p->Sub(m_pos);
    
	float distCenter = d->get_m_Len();
	float penetration = distCenter - m_radius;
    
    if( distCenter == 0 ){
        return new PointAndDistanceContainer( m_pos->Add(new Vector2( m_radius, 0 )), -m_radius );
    }
    
    // generate point on edge
    Vector2 *pow = d->MulScalar(m_radius/distCenter)->AddTo(m_pos);

    return new PointAndDistanceContainer(pow, penetration);
}
	
bool Circle::CircleCircleIntersect( Circle *a, Circle *b, Vector2Ref *pointAOut, Vector2Ref *pointBOut ){
	Vector2 *d = b->m_pos->Sub( a->m_pos );
	float centerDist = d->get_m_Len();
    
    if( centerDist > a->m_radius + b->m_radius ){
        // separated
        pointAOut = pointBOut = 0;
        return false;
    } else {
        // partial intersection
        float r0Sqr = a->m_radius*a->m_radius;
        float newCenterDist = ( r0Sqr-b->m_radius*b->m_radius+centerDist*centerDist )/( 2*centerDist );
        
        float sqr = r0Sqr-newCenterDist*newCenterDist;
        
        if( sqr <= 0.0 ){
            // containment
            pointAOut = pointBOut = 0;
            return false;
        }
        
        Vector2 *P2 = a->m_pos->Add( d->MulScalar( newCenterDist/centerDist ) );
        float radius = sqrt( sqr );
        
        Vector2 *perp = b->m_pos->Sub( a->m_pos )->get_m_Perp()->get_m_Unit();
        
        pointAOut->m_Value = P2->Add(perp->MulScalar(radius));
        pointBOut->m_Value = P2->Sub(perp->MulScalar(radius));
        
        return true;
    }
}

float Circle::RayCast( Vector2 *start, Vector2 *end, bool invert ){
    Vector2 *delta = start->Sub(m_pos);
    Vector2 *d = end->Sub(start);

    float a = d->Dot(delta);
    float b = d->get_m_LenSqr();
    float c = delta->get_m_LenSqr();

    float roa = a * a - b * (c - m_radius * m_radius);
    if (roa < 0){
        // no intersection
        return -1;
    } else if (roa == 0) {
        // ray tangent to circle, one intersection
        float num = sqrt(roa);

        float t0 = (-a + num) / b;
        return t0;
    } else {
        // two intersection points
        float num = sqrt(roa);

        float t0 = (-a + num) / b;
        float t1 = (-a - num) / b;

        if (invert) {
            return min(t1, t0);
        } else {
            return t0;
        }
    }
}