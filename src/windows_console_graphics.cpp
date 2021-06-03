#include "windows_console_graphics.h"
#include "error.h"

namespace {

	COORD getFontSize(HANDLE stdOutHandle)
	{
		CONSOLE_FONT_INFO info;
		GetCurrentConsoleFont(stdOutHandle, FALSE, &info);
		return GetConsoleFontSize(stdOutHandle, info.nFont);
	}

} // unnamed namespace

WindowsConsoleGraphics::WindowsConsoleGraphics(char characterToFilloWith, short colorToFillWith)
	: stdOutHandle(GetStdHandle(STD_OUTPUT_HANDLE))
{
	hideScrollbar();
	disableCursor();
	initSurfaceSize(characterToFilloWith, colorToFillWith);
}

void WindowsConsoleGraphics::Draw(int x, int y, char character, short color)
{
	DEBUG_ASSERT(x >= 0 && x < surface.getWidth() &&
				 y >= 0 && y < surface.getHeight(),
				 "You tried to draw beyond the surface");
	surface[(int)y][(int)x].Char.AsciiChar = character;
	surface[(int)y][(int)x].Attributes = color;
}

void WindowsConsoleGraphics::Render()
{
	handleResizing();

	short screen_width = surface.getWidth();
	short screen_height = surface.getHeight();

	// x, y, width, height
	SMALL_RECT rect_to_write_to = { 0, 0, screen_width - 1, screen_height - 1 };

	WriteConsoleOutputA(stdOutHandle, surface[0], { screen_width, screen_height }, { 0, 0 }, &rect_to_write_to);
}

void WindowsConsoleGraphics::Fill(char character, short color)
{
	for(int i = 0; i < surface.getHeight(); i++)
	{
		for(int j = 0; j < surface.getWidth(); j++)
		{
			surface[i][j] = { (WCHAR)character, (WORD)color };
		}
	}
}

unsigned WindowsConsoleGraphics::GetScreenWidth() const
{
	return surface.getWidth();
}

unsigned WindowsConsoleGraphics::GetScreenHeight() const
{
	return surface.getHeight();
}

unsigned WindowsConsoleGraphics::GetFontWidth() const
{
	COORD fontSize = getFontSize(stdOutHandle);
	return fontSize.X;
}

unsigned WindowsConsoleGraphics::GetFontHeight() const
{
	COORD fontSize = getFontSize(stdOutHandle);
	return fontSize.Y;
}

void WindowsConsoleGraphics::retrieveConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(stdOutHandle, &info);

	unsigned new_width = info.srWindow.Right - info.srWindow.Left + 1;
	unsigned new_height = info.srWindow.Bottom - info.srWindow.Top + 1;

	surface.resize(new_width, new_height);
}

void WindowsConsoleGraphics::disableCursor()
{
	CONSOLE_CURSOR_INFO ci = {/*dwSize*/ 1, /*bVisible*/ false };
	SetConsoleCursorInfo(stdOutHandle, &ci);
}

void WindowsConsoleGraphics::hideScrollbar()
{
	// Change Screen Buffer
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(stdOutHandle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(stdOutHandle, new_size);
	
	// Change console's window size
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = new_size.Y - 1;
	rect.Right = new_size.X - 1;
	SetConsoleWindowInfo(stdOutHandle, TRUE, &rect);
}

void WindowsConsoleGraphics::initSurfaceSize(char character, short color)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(stdOutHandle, &info);

	unsigned new_width = info.dwSize.X + 20;
	unsigned new_height = info.dwSize.Y;

	surface.resize(new_width, new_height);

	Fill(character, color);
}

void WindowsConsoleGraphics::handleResizing()
{
	// Check if the window has resized
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(stdOutHandle, &info);

	unsigned new_width = info.srWindow.Right - info.srWindow.Left + 1;
	unsigned new_height = info.srWindow.Bottom - info.srWindow.Top + 1;
	if(new_width != surface.getWidth() or new_height != surface.getHeight())
	{
		hideScrollbar();
		disableCursor();

		surface.resize(new_width, new_height);
	}
}