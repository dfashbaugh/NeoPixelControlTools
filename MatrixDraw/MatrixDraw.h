#define MaxX 32
#define MaxY 32

class MatrixDraw {
public:

	enum ColorType {RGB, RGBW};

	MatrixDraw();
	MatrixDraw(int xAxis, int yAxis);
	~MatrixDraw();

	int GetMatrixYSize() {return ySize; };
	int GetMatrixXSize() {return xSize; };

	int GetValueAt(int x, int y) {return Canvas[x][y]; };
	void SetPixelAt(int x, int y, int value) {Canvas[x][y] = value; };

	void DrawLine(int x1, int y1, int x2, int y2, int color);
	void DrawCircle(int r, int cX, int cY, int color);

private:

	int xSize;
	int ySize;
	int Canvas[MaxX][MaxY];

};