#include "graphics.h"

#include <math.h>

#include "geometry.h"
#include "graphics_creator.h"

void Graphics::DrawLine(int x1, int y1, int x2, int y2, char character, short color)
{
	int x_difference = x2 - x1;
	int y_difference = y2 - y1;

	// If the slope is steep, solve for x
	if (abs(y_difference) > abs(x_difference))
	{
		float slope = (float)x_difference / (float)y_difference;
		float offset = (float)x1 - slope * (float)y1;

		int y_lower = y1 < y2 ? y1 : y2;
		for (int y = y_lower; y <= y_lower + abs(y_difference); y++)
		{
			float x = slope * (float)y + offset + 0.5f;
			Draw((int)x, (int)y, character, color);
		}
	}
	else // Solve for y
	{
		float slope;
		if((float)x_difference == 0)
			slope = 0;
		else
			slope = (float)y_difference / (float)x_difference;

		float offset = (float)y1 - slope * (float)x1;

		int x_lower = x1 < x2 ? x1 : x2;
		for (int x = x_lower; x <= x_lower + abs(x_difference); x++)
		{
			float y = slope * (float)x + offset + 0.5f;
			Draw((int)x, (int)y, character, color);
		}
	}
}

void Graphics::DrawTriangle(const Triangle2Df & triangle, char character, short color)
{
	DrawLine((int)triangle.p[0].x, (int)triangle.p[0].y, (int)triangle.p[1].x, (int)triangle.p[1].y, character, color);
	DrawLine((int)triangle.p[1].x, (int)triangle.p[1].y, (int)triangle.p[2].x, (int)triangle.p[2].y, character, color);
	DrawLine((int)triangle.p[0].x, (int)triangle.p[0].y, (int)triangle.p[2].x, (int)triangle.p[2].y, character, color);
}

Graphics::~Graphics() {}