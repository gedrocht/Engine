#include "Texture.h"

class Physical{
public:
	Physical( Texture *texture );
	void update();
	Texture *texture;
	float Vx,
	      Vy;
	bool active;
};