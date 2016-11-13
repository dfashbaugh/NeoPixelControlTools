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

int main(void)
{
	cout << "Test Beginning" << endl;

	TestConstructor();

	return 0;
}