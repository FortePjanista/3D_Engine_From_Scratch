#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class InputHandler
{
public:
	virtual bool isKeyPressed(int key) = 0;

	// This should be called at the beggining of every frame in the main loop
	virtual void handleInputs() = 0;

public:
	virtual ~InputHandler() {}
};

#endif // INPUT_HANDLER_H