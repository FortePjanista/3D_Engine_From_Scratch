#ifndef WINDOWS_CONSOLE_GRAPHICS_H
#define WINDOWS_CONSOLE_GRAPHICS_H

#include <Windows.h>
#include "graphics.h"
#include "array2d.h"

class WindowsConsoleGraphics : public Graphics
{
public:
	WindowsConsoleGraphics(char characterToFilloWith = ' ', short colorToFillWith = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	void Draw(int x, int y, char character, short color) override;
	void Render() override;

	void Fill(char character, short color) override;

	unsigned GetScreenWidth() const override;
	unsigned GetScreenHeight() const override;

	unsigned GetFontWidth() const override;
	unsigned GetFontHeight() const override;

	Array2D<CHAR_INFO> surface;
private:
	HANDLE stdOutHandle;

	void retrieveConsoleSize();
	void disableCursor();
	void hideScrollbar();
	void initSurfaceSize(char character, short color);

	void handleResizing();
};

#endif // WINDOWS_CONSOLE_GRAPHICS