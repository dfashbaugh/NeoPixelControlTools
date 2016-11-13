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

private:

	int xSize;
	int ySize;
	int Canvas[MaxX][MaxY];

};