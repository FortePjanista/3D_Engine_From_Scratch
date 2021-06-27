#include "application.h"

#include "cube.h"

class MyApp : public Application
{
	std::unique_ptr<Cube > cube;
	bool pause = false;

	void init() override
	{
		// Create a simple cube
		cube = std::make_unique<Cube>();

		// Add this cube to tha engine
		addEntity(cube.get());
	}
};
CREATE_APPLICATION(MyApp);