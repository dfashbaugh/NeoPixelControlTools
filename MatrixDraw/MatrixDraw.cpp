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
	
}

void MatrixDraw::DrawCircle(int r, int cX, int cY, int color)
{
	
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