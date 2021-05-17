#include "entity.h"
#include "error.h"

namespace {

inline void rotate_angle(float & angle_to_rotate, float angle_to_add)
{
	angle_to_rotate += angle_to_add;
	DEBUG_ASSERT_WARNING((angle_to_add < 360.f and angle_to_add > -360.f), "You try to rotate an object for more than 360 degrees. (%lf degrees)", angle_to_add);
	while (angle_to_rotate > 360.f)
	{
		angle_to_rotate -= 360.f;
	}
	while (angle_to_rotate < -360.f)
	{
		angle_to_rotate += 360.f;
	}
}

} // unnamed namespace

Entity::Entity(char ch, short c)
	:
	x(0.f),
	y(0.f),
	z(0.f),
	x_size(1.f),
	y_size(1.f),
	z_size(1.f),
	x_rotation_deg(0.f),
	y_rotation_deg(0.f),
	z_rotation_deg(0.f),
	x_position_change(0.f),
	y_position_change(0.f),
	z_position_change(0.f),
	x_angle_change_deg(0.f),
	y_angle_change_deg(0.f),
	z_angle_change_deg(0.f),
	character(ch),
	color(c)
{}

void Entity::update() {}

void Entity::rotate_x(float angle_deg_to_add)
{
	rotate_angle(x_rotation_deg, angle_deg_to_add);
}

void Entity::rotate_y(float angle_deg_to_add)
{
	rotate_angle(y_rotation_deg, angle_deg_to_add);
}

void Entity::rotate_z(float angle_deg_to_add)
{
	rotate_angle(z_rotation_deg, angle_deg_to_add);
}


