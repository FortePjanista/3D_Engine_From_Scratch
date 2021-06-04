#include "transformations.h"

#include "maths.h"

Mat4 transformation::size(float x_size, float y_size, float z_size)
{
	return
	{
		{ x_size,   0   ,   0   ,   0   },
		{   0   , y_size,   0   ,   0   },
		{   0   ,   0   , z_size,   0   },
		{   0   ,   0   ,   0   ,   1   }
	};
}

Mat4 transformation::rotation(float x_rotation_angle, float y_rotation_angle, float z_rotation_angle)
{
	float x_rad = degToRad(x_rotation_angle);
	float y_rad = degToRad(y_rotation_angle);
	float z_rad = degToRad(z_rotation_angle);

	Mat4
	x_rotation =
	{
		{     1     ,     0     ,     0     ,     0     },
		{     0     , cos(x_rad), sin(x_rad),     0     },
		{     0     ,-sin(x_rad), cos(x_rad),     0     },
		{     0     ,     0     ,     0     ,     1     }
	},
	y_rotation =
	{
		{ cos(y_rad),     0     ,-sin(y_rad),     0     },
		{     0     ,     1     ,     0     ,     0     },
		{ sin(y_rad),     0     , cos(y_rad),     0     },
		{     0     ,     0     ,     0     ,     1     }
	},
	z_rotation =
	{
		{ cos(z_rad), sin(z_rad),     0     ,     0     },
		{-sin(z_rad), cos(z_rad),     0     ,     0     },
		{     0     ,     0     ,     1     ,     0     },
		{     0     ,     0     ,     0     ,     1     }
	};
	return x_rotation * y_rotation * z_rotation;
}

Mat4 transformation::translation(float x_position, float y_position, float z_position)
{
	return
	{
		{     1     ,     0     ,     0     , x_position},
		{     0     ,     1     ,     0     , y_position},
		{     0     ,     0     ,     1     , z_position},
		{     0     ,     0     ,     0     ,      1    }
	};
}

// We do not normalize z, we dont need znear and zfar yet
// TODO aspect ratio
Mat4 transformation::projection(float fov, float aspect_ratio, float z_near, float z_far)
{
	float fov_rad = degToRad(fov);
	return
	{
		{ 1 / (tan(fov_rad / 2) * aspect_ratio),           0         ,          0          ,         0           },
		{                   0                  , 1 / tan(fov_rad / 2),          0          ,         0           },
		{                   0                  ,           0         ,          1          ,         0           },
		{                   0                  ,           0         ,          0          ,         1           }
	};
}
