#include "cube.h"

#include "color.h"

Cube::Cube() : Entity('X', COLOR_DEFAULT)
{
	x = -20.f;
	y = 60.f;
	z = 200.f;

	x_size = 1.9f;
	y_size = 1.9f;
	z_size = 1.9f;

	x_rotation_deg = 0.f;
	y_rotation_deg = 0.f;
	z_rotation_deg = 0.f;

	x_angle_change_deg = 0.f;
	y_angle_change_deg = 0.00002f;
	z_angle_change_deg = 0.f;

	x_position_change = 0.f;
	y_position_change = 0.f;
	z_position_change = 0.f;

	// Fill in the mesh
	float depth1 = 1.f;
	float depth2 = 35.f;
	mesh.points = 
	{
		{0.f, 0.f, depth1}, // 0
		{1.f, 0.f, depth1}, // 1
		{0.f, 1.f, depth1}, // 2
		{1.f, 1.f, depth1}, // 3

		{0.f, 0.f, depth2}, // 4
		{1.f, 0.f, depth2}, // 5
		{0.f, 1.f, depth2}, // 6
		{1.f, 1.f, depth2}  // 7
	};

	mesh.indices = 
	{
		//Front
		{0, 1, 3},
		{0, 3, 2},

		//Back
		{4, 5, 7},
		{4, 7, 6},

		//Top
		{2, 3, 7},
		{2, 7, 6},

		//Down
		{0, 1, 5},
		{0, 5, 4},

		//Right
		{1, 5, 7},
		{1, 7, 3},

		//Left
		{0, 4, 6},
		{0, 6, 2}
	};
}

void Cube::update()
{

}

void Cube::startToRotate(int what)
{
	if(what == /*x*/0)
		x_angle_change_deg = 0.00002f;
	else /*y*/
		y_angle_change_deg = 0.00002f;
}

void Cube::stopRotation(int what)
{
	if (what == /*x*/0)
		x_angle_change_deg = 0.f;
	else /*y*/
		y_angle_change_deg = 0.f;
}
