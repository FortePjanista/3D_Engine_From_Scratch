#include "application.h"

#include "transformations.h"
#include "entity.h"
#include "graphics.h"
#include "vector.h"
#include "geometry.h"
#include "color.h"
#include "error.h"

// TODO fps handling
namespace {

inline std::vector<Vec4f> copyVec3ToVec4(const std::vector<Vec3f> & points)
{
	std::vector<Vec4f> ret;
	ret.reserve(points.size());
	for (auto & point : points)
	{
		ret.push_back({ point[/*x*/0], point[/*y*/1], point[/*z*/2], 1.0f });
	}
	return ret;
}

inline bool pointIsVisible(const Vec4f & point, float zNear, float zFar)
{
	// Check x
	if (point[0] < -1.0f or point[0] > 1.0f) return false;

	// Check y
	if (point[1] < -1.0f or point[1] > 1.0f) return false;

	// Check z
	if (point[2] < zNear or point[2] > zFar) return false;
	return true;
}

// Returns triangles made out of indexes of points stored in the mesh
inline std::vector<Vec3uint> discardOutOfBoundTrianlges(const std::vector<Vec4f> & normalizedPoints, const std::vector<Vec3uint> & meshesIndices, float zNear, float zFar)
{
	std::vector<Vec3uint> ret;
	ret.reserve(meshesIndices.size());
	for (auto & indicesToPoints : meshesIndices)
	{
		// Check if the whole triangle is visible (all points are in bounds)
		bool onScreen = true;

		// Do for 3 points in triangle (built out of indicesToPoints)
		for (unsigned p = 0; p < 3; p++)
		{
			const auto & pointToCheck = normalizedPoints.at(indicesToPoints[p]);

			if (!pointIsVisible(pointToCheck, zNear, zFar))
			{
				onScreen = false;
				break;
			}
		}
		if (onScreen)
			ret.push_back(indicesToPoints);
	}
	return ret;
}
} // unnamed namespace

Application::Application() : graphics(Graphics::createGraphics())
{
}

Application::~Application()
{
	delete graphics;
	delete inputHandler;
}

void Application::init() {}

void Application::update() {}

void Application::addEntity(Entity * entity)
{
	entities.push_back(entity);
}

void Application::render(const Entity & entity)
{
	const float screenWidth = (float)graphics->GetScreenWidth();
	const float screenHeight = (float)graphics->GetScreenHeight();
	const float fontWidth = (float)graphics->GetFontWidth();
	const float fontHeight = (float)graphics->GetFontHeight();
	const float zNear = 0.1f;
	const float zFar = 1000.f;

	const float aspect_ratio = (screenWidth / screenHeight) * (fontWidth / fontHeight);

	Mat4 sizeTranformation = transformation::size(entity.x_size, entity.y_size, entity.z_size);
	Mat4 rotationTranformation = transformation::rotation(entity.x_rotation_deg, entity.y_rotation_deg, entity.z_rotation_deg);
	Mat4 translationTranformation = transformation::translation(entity.x, entity.y, entity.z);
	Mat4 projectionTransformation = transformation::projection(/*fov*/ 60.f, aspect_ratio, zNear, zFar);

	Mat4 transformation = translationTranformation * rotationTranformation * sizeTranformation * projectionTransformation;

	// Normalize points
	std::vector<Vec4f> normalizedPoints = copyVec3ToVec4(entity.mesh.points);
	for (auto & point : normalizedPoints)
		point = transformation * point;

	// Divide x and y by z, as we can't do this in matrix multiplication
	for (auto & point : normalizedPoints)
	{
		if (point[/*z*/2] != 0.0f)
		{
			point[/*x*/0] /= point[/*z*/2];
			point[/*y*/1] /= point[/*z*/2];
		}
	}

	// Now we have normalized x and y coordinates of all points in the mesh.

	// Let's check if triangles are within the drawing area
	// For now, we discard only the ones all of which points are out of bounds
	std::vector<Vec3uint> indicesToDraw = discardOutOfBoundTrianlges(normalizedPoints, entity.mesh.indices, zNear, zFar);

	// Create and render 2D triangles out of it
	for (auto & indicesOfPoint : indicesToDraw)
	{
		const Vec4f & normalizedP1 = normalizedPoints[indicesOfPoint[0]];
		const Vec4f & normalizedP2 = normalizedPoints[indicesOfPoint[1]];
		const Vec4f & normalizedP3 = normalizedPoints[indicesOfPoint[2]];

		// Resize normalized coords from [-1, 1] to [0, screenWidth] and [0, screenHeight]
		Triangle2Df triangleToDraw =
		{ {
			{
				(normalizedP1[/*x*/0] + 1.0f) * 0.5f * screenWidth,
				(normalizedP1[/*y*/1] + 1.0f) * 0.5f * screenHeight
			},
			{
				(normalizedP2[/*x*/0] + 1.0f) * 0.5f * screenWidth,
				(normalizedP2[/*y*/1] + 1.0f) * 0.5f * screenHeight
			},
			{
				(normalizedP3[/*x*/0] + 1.0f) * 0.5f * screenWidth,
				(normalizedP3[/*y*/1] + 1.0f) * 0.5f * screenHeight
			}
		} };
		graphics->DrawTriangle(triangleToDraw, entity.character, entity.color);
	}
}

void Application::handlePosition(Entity & entity)
{
	entity.rotate_x(entity.x_angle_change_deg);
	entity.rotate_y(entity.y_angle_change_deg);
	entity.rotate_z(entity.z_angle_change_deg);
}

void Application::run()
{
	bool quit = false;
	while(!quit)
	{
		// Poor fps
		Sleep(10);

		// Update entities' position
		for (Entity * entity : entities)
		{
			handlePosition(*entity);
		}

		// Call entities' update functions
		for (Entity * entity : entities)
		{
			entity->update();
		}

		// Clear screen
		graphics->Fill(' ', COLOR_DEFAULT);

		// Draw entities
		for (const Entity * entity : entities)
		{
			render(*entity);
		}

		// Call user defined application's update
		update();

		// Render current frame
		graphics->Render();
	}
}
