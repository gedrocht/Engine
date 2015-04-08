#include "Vector2.h"

class IAABB {
public:
	Vector2 *m_Center;
	Vector2 *m_HalfExtents;

	Vector2 *get_m_Center();
	Vector2 *get_m_HalfExtents();
};