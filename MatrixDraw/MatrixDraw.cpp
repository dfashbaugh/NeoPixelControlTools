#include "MatrixDraw.h"

MatrixDraw::MatrixDraw()
{
	xSize = 0;
	ySize = 0;
}

MatrixDraw::MatrixDraw(int xAxis, int yAxis)
	: xSize(xAxis)
	, ySize(yAxis)
{
	Canvas = new int*[xAxis];
	for (int i = 0; i < xAxis; ++i)
	    Canvas[i] = new int[yAxis];
}

MatrixDraw::~MatrixDraw()
{

}

void MatrixDraw::DrawLine(int x1, int y1, int x2, int y2, int color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	if(dx == 0)
	{
		for(int y = y1; y <= y2; y++){
		  		int x = x1 + dx * (y - y1) / dy;
		  		SetPixelAt(x, y, color);
			}
	}
	else
	{
		for(int x = x1; x <= x2; x++){
  			int y = y1 + dy * (x - x1) / dx;
  			SetPixelAt(x, y, color);
		}
	}
	
}

void MatrixDraw::DrawCircle(int r, int cX, int cY, int color)
{
	int x = r;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        SetPixelAt(cX + x, cY + y, color);
        SetPixelAt(cX + y, cY + x, color);
        SetPixelAt(cX - y, cY + x, color);
        SetPixelAt(cX - x, cY + y, color);
        SetPixelAt(cX - x, cY - y, color);
        SetPixelAt(cX - y, cY - x, color);
        SetPixelAt(cX + y, cY - x, color);
        SetPixelAt(cX + x, cY - y, color);

        y += 1;
        err += 1 + 2*y;
        if (2*(err-x) + 1 > 0)
        {
            x -= 1;
            err += 1 - 2*x;
        }
    }
}

void MatrixDraw::DrawRectangle(int x1, int y1, int x2, int y2, int color)
{
	DrawLine(x1, y1, x2, y1, color);
	DrawLine(x1, y2, x2, y2, color);
	DrawLine(x1, y1, x1, y2, color);
	DrawLine(x2, y1, x2, y2, color);
}

void MatrixDraw::FloodFillRecur(int x, int y, int prevC, int newC)
{
	    // Base cases
    if (x < 0 || x >= xSize || y < 0 || y >= ySize)
        return;
    if (GetValueAt(x,y) != prevC)
        return;
 
    // Replace the color at (x, y)
    SetPixelAt(x,y, newC);
 
    // Recur for north, east, south and west
    FloodFillRecur(x+1, y, prevC, newC);
    FloodFillRecur(x-1, y, prevC, newC);
    FloodFillRecur(x, y+1, prevC, newC);
    FloodFillRecur(x, y-1, prevC, newC);
}


void MatrixDraw::Fill(int x, int y, int color)
{
	int prevC = GetValueAt(x, y);
	if(prevC == color)
		return;
	
	FloodFillRecur(x,y, prevC, color);
}

int MatrixDraw::BilinearInterpolation(int q11, int q12, int q21, int q22, int x1, int x2, int y1, int y2, int x, int y) 
{
    int x2x1, y2y1, x2x, y2y, yy1, xx1;
    x2x1 = x2 - x1;
    y2y1 = y2 - y1;
    x2x = x2 - x;
    y2y = y2 - y;
    yy1 = y - y1;
    xx1 = x - x1;
    return 255 / (x2x1 * y2y1) * (
        q11 * x2x * y2y +
        q21 * xx1 * y2y +
        q12 * x2x * yy1 +
        q22 * xx1 * yy1
    );
}

void MatrixDraw::Bilinear(int x1, int y1, int x2, int y2)
{
	int q11 = GetValueAt(x1,y1);
	int q12 = GetValueAt(x1,y2);
	int q21 = GetValueAt(x2, y1);
	int q22 = GetValueAt(x2, y2);

	for(int y = 0; y < ySize; y++)
	{
		for(int x = 0; x < xSize; x++)
		{
			SetPixelAt(x,y, BilinearInterpolation(q11,q12,q21,q22,x1,x2,y1,y2,x,y));
		}
	}
}

void MatrixDraw::ClearMatrix()
{
	for(int x = 0; x < xSize; x++)
	{
		for(int y = 0; y < ySize; y++)
		{
			Canvas[x][y] = 0;
		}
	}
}