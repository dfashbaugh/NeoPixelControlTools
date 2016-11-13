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
}

MatrixDraw::~MatrixDraw()
{

}