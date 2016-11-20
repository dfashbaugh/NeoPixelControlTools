class MatrixDraw {
public:

	enum ColorType {RGB, RGBW};

	MatrixDraw();
	MatrixDraw(int xAxis, int yAxis);
	MatrixDraw(int xAxis, int yAxis, int largestFilterWindow);
	~MatrixDraw();

	int GetMatrixYSize() {return ySize; };
	int GetMatrixXSize() {return xSize; };

	int GetValueAt(int x, int y) {return Canvas[x][y]; };
	void SetPixelAt(int x, int y, int value) {Canvas[x][y] = value; };

	void DrawLine(int x1, int y1, int x2, int y2, int color);
	void DrawCircle(int r, int cX, int cY, int color);
	void DrawRectangle(int x1, int y1, int x2, int y2, int color);
	void Fill(int x, int y, int color);
	void Bilinear(int x1, int y1, int x2, int y2, float q11, float q12, float q21, float q22);

	void MeanFilter(int kernel);

	void ClearMatrix();
private:

	void FloodFillRecur(int x, int y, int prevC, int newC);
	float BilinearInterpolation(float q11, float q12, float q21, float q22, int x1, int x2, int y1, int y2, int x, int y);

	int filtersEnabled;
	int xSize;
	int ySize;
	int maxFilterWindow;
	int **Canvas;
	int **OutputCanvas;
	int **FilterWindow;

};