class MatrixDraw {
public:

	enum ColorType {RGB, RGBW};

	MatrixDraw();
	MatrixDraw(int xAxis, int yAxis);
	~MatrixDraw();

	int GetMatrixYSize() {return ySize; };
	int GetMatrixXSize() {return xSize; };

private:

	int xSize;
	int ySize;

};