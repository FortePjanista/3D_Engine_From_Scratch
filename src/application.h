#ifndef APPLICATOIN_H
#define APPLICATION_H

#include <vector>
class Entity;
class Graphics;
class InputHandler;

class Application
{
protected:
	Application();
	virtual ~Application();

	virtual void init();
	virtual void update();
	void addEntity(Entity * entity);


	Graphics * graphics;
	InputHandler * inputHandler;
	std::vector<Entity *> entities;

	friend int main();

private:
	void run();
	void render(const Entity & entity);
	void handlePosition(Entity & entity);
};

#include "entry_point.h"

#endif // APPLICATION_H