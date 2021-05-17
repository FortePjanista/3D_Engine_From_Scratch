#ifndef MESH_H
#define MESH_H

#include <vector>
#include "vector.h"

struct Mesh
{
	std::vector<Vec3f> points;
	std::vector<Vec3uint> indices;
};

#endif // MESH_H