#ifndef CUBE_H
#define CUBE_H

#include "entity.h"

class Cube : public Entity
{
public:
	Cube();
	void update() override;
	void startToRotate(int what);
	void stopRotation(int what);
};

#endif // CUBE_H