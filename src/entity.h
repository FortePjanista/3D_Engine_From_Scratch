#ifndef ENTITY_H
#define ENTITY_H

#include "mesh.h"

class Application;

class Entity
{
protected:
	Entity(char character, short color);

	float x;
	float y;
	float z;

	float x_rotation_deg;
	float y_rotation_deg;
	float z_rotation_deg;

	float x_size;
	float y_size;
	float z_size;

	float x_position_change;
	float y_position_change;
	float z_position_change;

	float x_angle_change_deg;
	float y_angle_change_deg;
	float z_angle_change_deg;

	Mesh mesh;

	char character;
	short color;

	virtual void update();

	void rotate_x(float angle_deg_to_add);
	void rotate_y(float angle_deg_to_add);
	void rotate_z(float angle_deg_to_add);

	friend Application;
};

#endif // ENTITY_H