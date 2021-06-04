#ifndef TRNSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "matrix.h"

namespace transformation
{
	Mat4 size(float x_size, float y_size, float z_size);
	Mat4 rotation(float x_rotation_angle, float y_rotation_angle, float z_rotation_angle);
	Mat4 translation(float x_position, float y_position, float z_position);
	Mat4 projection(float fov, float aspect_ratio, float z_near, float z_far);
}

#endif TRANSFORMATIONS_H