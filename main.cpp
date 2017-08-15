#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include "BigNumCalculator.h"
#include "Str.h"

using namespace std;

//#define __DEBUG__1__

int main(void)
{
	string str1, str2;
	BigNumber_t num1, num2, answer;
	char calculateType;

	cout << "Enter a formula" << endl << "Between number and operator must have space" << endl;
	cin >> str1 >> calculateType >> str2;

	try
	{
		num1 = StringToBigNum(str1);
		num2 = StringToBigNum(str2);
	}
	catch (runtime_error err)
	{
		cout << err.what() << endl;
		system("pause");
		exit(1);
	}

#ifdef __DEBUG__1__
	for (int i : num1.numberPart)
		cout << i;
	cout << "\n" << num1.expPart << endl;

	for (int i : num2.numberPart)
		cout << i;
	cout << "\n" << num2.expPart << endl;

	system("pause");
#endif // __DEBUG__1__


	switch (calculateType)
	{
	case '+':
		//answer = BigNumberAdd(num1, num2);
		cout << BigNumToString(num1 + num2) << endl;
		break;

	case '-':
		cout << BigNumToString(num1 - num2) << endl;
		break;

	case '*':
	case '/':
	default:
		cout << "The calculate " << calculateType << " are not available" << endl;
		exit(2);
		break;
	}

	system("pause");

	return 0;
}