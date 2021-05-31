#ifndef GRAPHICS_H
#define GRAPHICS_H

struct Triangle2Df;

class Graphics
{
public:
	static Graphics * createGraphics();

	virtual void Draw(int x, int y, char character, short color) = 0;
	void DrawLine(int x1, int y1, int x2, int y2, char character, short color);
	void DrawTriangle(const Triangle2Df & triangle, char character, short color);
	
	virtual void Fill(char character, short color) = 0;

	virtual unsigned GetScreenWidth() const = 0;
	virtual unsigned GetScreenHeight() const = 0;

	virtual unsigned GetFontWidth() const = 0;
	virtual unsigned GetFontHeight() const = 0;

	virtual void Render() = 0;

	virtual ~Graphics();
};
#endif // GRAPHICS_H
