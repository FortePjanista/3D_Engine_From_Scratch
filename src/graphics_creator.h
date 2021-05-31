#ifndef GRAPHICS_CREATOR_H
#define GRAPHICS_CREATOR_H

#ifdef _WIN32
#include "windows_console_graphics.h"
#else
#error Platforms other than Windows are not supported yet
#endif

Graphics * Graphics::createGraphics()
{
#ifdef _WIN32
	return new WindowsConsoleGraphics();
#else
#error Platforms other than Windows are not supported yet
#endif
}

#endif // GRAPHICS_CREATOR_H