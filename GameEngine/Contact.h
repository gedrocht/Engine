#include "Vector2.h"

class Contact {
public:
	Vector2* m_normal;
	float m_dist;
	float m_impulse;
	Vector2 *m_p;
	void Initialize( Vector2 *n, float dist, Vector2 *p );
};