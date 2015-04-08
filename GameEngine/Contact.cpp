#include "Contact.h"

void Contact::Initialize( Vector2 *n, float dist, Vector2 *p ){
	m_normal = n;
	m_dist = dist;
	m_impulse = 0;
	m_p = p;
}