#include <iostream>
#include "MatrixDraw.h"
using namespace std;

struct ExpectedValue
{
	std::string valueName;
	int expectedValue;
	int actualValue;
};

void OnSuccess(std::string testName)
{
	cout << testName << ": " << "Passed" << endl;
}

void OnFailure(std::string testName)
{
	cout << testName << ": " << "Failed" << endl;
}

void ListExpected(ExpectedValue value)
{
	cout << "    " << value.valueName << " - Expected: " << value.expectedValue << " Found: " << value.actualValue << endl;
}

void CheckResults(std::string testName, ExpectedValue valueList [], int numberOfValues)
{
	for(int i = 0; i < numberOfValues; i++)
	{
		if(valueList[i].expectedValue != valueList[i].actualValue)
		{
			OnFailure(testName);

			for(int j = 0; j < numberOfValues; j++)
			{
				ListExpected(valueList[j]);
			}

			return;
		}
	}

	OnSuccess(testName);
}

void DrawMatrix(MatrixDraw &draw)
{
	for(int y = 0; y < draw.GetMatrixYSize(); y++)
	{
		for(int x = 0; x < draw.GetMatrixXSize(); x++)
		{
			if(draw.GetValueAt(x,y) > 0)
			{
				cout << " x";
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
}

void DrawMatrixByNumbers(MatrixDraw &draw)
{
	for(int y = 0; y < draw.GetMatrixYSize(); y++)
	{
		for(int x = 0; x < draw.GetMatrixXSize(); x++)
		{
			if(draw.GetValueAt(x,y) < 10)
			{
				cout << "   " << draw.GetValueAt(x,y);
			}
			else if(draw.GetValueAt(x,y) < 100)
			{
				cout << "  " << draw.GetValueAt(x,y);
			}
			else
			{
				cout << " " << draw.GetValueAt(x,y);
			}
		}
		cout << endl;
	}
}

void TestRectDraw()
{
	MatrixDraw draw(3, 80, 9);
	draw.ClearMatrix();

	draw.DrawRectangle(0, 20, 2, 25, 255);
	draw.Fill(1,22, 255);
	draw.MeanFilter(9);

	DrawMatrixByNumbers(draw);

	cout << "Test Rectangle" << endl;
}

void TestMean()
{
	MatrixDraw draw(20, 20, 9);
	draw.ClearMatrix();
	draw.DrawRectangle(8,8, 12, 12, 255);
	draw.DrawCircle(5, 6, 6, 255);
	draw.Fill(9, 9, 255);
	draw.MeanFilter(9);
	DrawMatrixByNumbers(draw);

	cout << "Test Mean Filter: Visual Inspection" << endl;
}	

void TestBilinear()
{
	MatrixDraw draw(20,20);
	draw.Bilinear(0, 0, 20, 20, 0.2, .10,0,0);
	DrawMatrixByNumbers(draw);

	cout << "Test Biliner: Visual Inspection" << endl;
}	

void TestFloodFillFailureCase()
{
	std::string testName = "Test Flood Fill Failure";

	MatrixDraw draw(20, 20);
	draw.DrawRectangle(8,1, 18, 10, 1);
	draw.Fill(8, 5, 1);

	ExpectedValue valueList [1];
	valueList[0].valueName = "Did Not Crash";
	valueList[0].expectedValue = 1;
	valueList[0].actualValue = 1;

	CheckResults(testName, valueList, 1);
}

void TestRectangleDraw()
{
	std::string testName = "Rectangle Draw";

	MatrixDraw draw(20, 20);
	draw.DrawRectangle(8,1, 18, 10, 1);
	DrawMatrix(draw);

	ExpectedValue valueList [4];
	valueList[0].valueName = "Left XY Position";
	valueList[0].expectedValue = 1;
	valueList[0].actualValue = draw.GetValueAt(8, 5);

	valueList[1].valueName = "Right XY Position";
	valueList[1].expectedValue = 1;
	valueList[1].actualValue = draw.GetValueAt(18, 5);

	valueList[2].valueName = "Up XY Position";
	valueList[2].expectedValue = 1;
	valueList[2].actualValue = draw.GetValueAt(12, 1);

	valueList[3].valueName = "Down XY Position";
	valueList[3].expectedValue = 1;
	valueList[3].actualValue = draw.GetValueAt(14, 10);

	CheckResults(testName, valueList, 4);
}

void TestFillCircle()
{
	std::string testName = "Fill Circle";

	MatrixDraw draw(20, 20);
	draw.DrawCircle(8,10, 10, 1);
	draw.Fill(12, 11, 1);
	DrawMatrix(draw);

	ExpectedValue valueList [1];
	valueList[0].valueName = "Not Circle Edge";
	valueList[0].expectedValue = 1;
	valueList[0].actualValue = draw.GetValueAt(7, 8);

	CheckResults(testName, valueList, 1);
}

void TestCircleDraw()
{
	std::string testName = "Circle Draw";

	MatrixDraw draw(20, 20);
	draw.DrawCircle(8,10, 10, 1);
	DrawMatrix(draw);

	ExpectedValue valueList [4];
	valueList[0].valueName = "Left XY Position";
	valueList[0].expectedValue = 1;
	valueList[0].actualValue = draw.GetValueAt(2, 10);

	valueList[1].valueName = "Right XY Position";
	valueList[1].expectedValue = 1;
	valueList[1].actualValue = draw.GetValueAt(18, 10);

	valueList[2].valueName = "Up XY Position";
	valueList[2].expectedValue = 1;
	valueList[2].actualValue = draw.GetValueAt(10, 2);

	valueList[3].valueName = "Down XY Position";
	valueList[3].expectedValue = 1;
	valueList[3].actualValue = draw.GetValueAt(10, 18);

	CheckResults(testName, valueList, 4);
}

void TestLineDraw()
{
	std::string testName = "Line Draw";

	MatrixDraw draw(20, 20);
	draw.DrawLine(5,2, 19, 15, 1);
	DrawMatrix(draw);

	ExpectedValue valueList [2];
	valueList[0].valueName = "Start XY Position";
	valueList[0].expectedValue = 1;
	valueList[0].actualValue = draw.GetValueAt(5, 2);

	valueList[1].valueName = "End XY Position";
	valueList[1].expectedValue = 1;
	valueList[1].actualValue = draw.GetValueAt(19, 15);

	CheckResults(testName, valueList, 2);
}

void TestConstructor()
{
	std::string testName = "Matrix Constructor";

	MatrixDraw draw(10,20);

	ExpectedValue valueList [2];
	valueList[0].valueName = "Matrix X Size";
	valueList[0].expectedValue = 10;
	valueList[0].actualValue = draw.GetMatrixXSize();

	valueList[1].valueName = "Matrix Y Size";
	valueList[1].expectedValue = 20;
	valueList[1].actualValue = draw.GetMatrixYSize();

	CheckResults(testName, valueList, 2);
}

void TestCanvasAccessor()
{
	std::string testName = "Canvas Accessor";

	MatrixDraw draw(10,20);
	draw.SetPixelAt(5,10, 0xFFA0E1);

	ExpectedValue valueList [1];
	valueList[0].valueName = "Value at 5,10";
	valueList[0].expectedValue = 0xFFA0E1;
	valueList[0].actualValue = draw.GetValueAt(5, 10);

	CheckResults(testName, valueList, 1);
}

void TestClearMatrix()
{
	std::string testName = "Clear Matrix Test";

	MatrixDraw draw(10,20);
	draw.SetPixelAt(5,10, 0xFFA0E1);

	ExpectedValue valueList [2];
	valueList[0].valueName = "Value at 5,10 Before Clear";
	valueList[0].expectedValue = 0xFFA0E1;
	valueList[0].actualValue = draw.GetValueAt(5, 10);

	draw.ClearMatrix();

	valueList[1].valueName = "Value at 5,10 After Clear";
	valueList[1].expectedValue = 0;
	valueList[1].actualValue = draw.GetValueAt(5, 10);

	CheckResults(testName, valueList, 2);
}

int main(void)
{
	cout << "Test Beginning" << endl;

	TestConstructor();
	TestCanvasAccessor();
	TestClearMatrix();
	TestLineDraw();
	TestCircleDraw();
	TestFillCircle();
	TestRectangleDraw();
	TestFloodFillFailureCase();
	TestBilinear();
	TestMean();
	TestRectDraw();

	return 0;
}