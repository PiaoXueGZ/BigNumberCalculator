#include <iostream>
#include <vector>
#include "BigNumCalculator.h"

using namespace std;

void FillNumberToSameDigits(
	NumberPart_t &v1, 
	NumberPart_t &v2, 
	int exp1, int exp2)	//将两个需要处理的数字填充成一样的位数, 使需要相加的位对齐
{
	NumberPart_t &SmallerDigits = ((int)(v1.size()) + exp1 < (int)(v2.size()) + exp2 ? v1 : v2);
	int digitsDiff = abs(((int)(v1.size()) + exp1) - ((int)(v2.size()) + exp2));
	for (int i = 0; i != digitsDiff; ++i)
		SmallerDigits.insert(SmallerDigits.begin(), 0);

	NumberPart_t &BiggerDigits = (exp1 > exp2 ? v1 : v2);
	digitsDiff = abs(exp1 - exp2);
	for (int i = 0; i != digitsDiff; ++i)
		BiggerDigits.push_back(0);

	v1.insert(v1.begin(), 0);	//在对齐的两个数前面各填一个0，用来处理运算结束后的进位
	v2.insert(v2.begin(), 0);
}

/*
BigNumber_t BigNumberAdd(BigNumber_t num1, BigNumber_t num2)
{
	BigNumber_t answer;
	int carryBit = 0;

	FillNumberToSameDigits(num1.numberPart, num2.numberPart, num1.expPart, num2.expPart);	//对齐相加位

	for (
		auto iter1 = num1.numberPart.end() - 1, iter2 = num2.numberPart.end() - 1;
		iter1 != num1.numberPart.begin() && iter2 != num2.numberPart.begin();
		--iter1, --iter2)	//逐位相加，从后往前
	{
		answer.numberPart.insert(answer.numberPart.begin(), (*iter1 + *iter2 + carryBit) % 10);
		carryBit = (*iter1 + *iter2) / 10;
	}

	answer.expPart = (num1.expPart < num2.expPart ? num1.expPart : num2.expPart);	//处理指数部分，选择小的做答案指数

	return answer;
}
*/

BigNumber_t operator +(BigNumber_t left, BigNumber_t right)
{
	BigNumber_t answer;
	int carryBit = 0;

	FillNumberToSameDigits(left.numberPart, right.numberPart, left.expPart, right.expPart);	//对齐相加位

	/*
	for (
		auto iter1 = left.numberPart.end() - 1, iter2 = right.numberPart.end() - 1;
		iter1 != left.numberPart.begin() && iter2 != right.numberPart.begin(); 
		--iter1, --iter2)	//逐位相加，从后往前
	{
		answer.numberPart.insert(answer.numberPart.begin(), (*iter1 + *iter2 + carryBit) % 10);
		carryBit = (*iter1 + *iter2) / 10;
	}
	*/

	for (int i = 0; i != left.numberPart.size() && i != right.numberPart.size(); ++i)
	{
		answer.numberPart.insert(answer.numberPart.begin(), (left.numberPart[left.numberPart.size() - i - 1] + right.numberPart[right.numberPart.size() - i - 1] + carryBit) % 10);
		carryBit = (left.numberPart[left.numberPart.size() - i - 1] + right.numberPart[right.numberPart.size() - i - 1]) / 10;
	}

	answer.expPart = (left.expPart < right.expPart ? left.expPart : right.expPart);	//处理指数部分，选择小的做答案指数

	return answer;
}


BigNumber_t operator -(BigNumber_t left, BigNumber_t right)
{
	BigNumber_t answer;
	int carrybit = 0;

	FillNumberToSameDigits(left.numberPart, right.numberPart, left.expPart, right.expPart);	//对齐

	/*
	for (
		auto iter1 = left.numberPart.end() - 1, iter2 = right.numberPart.end() - 1;
		iter1 != left.numberPart.begin() && iter2 != right.numberPart.begin();
		--iter1, --iter2)
	{
		answer.numberPart.insert(answer.numberPart.begin(), (*iter1 - *iter2 + carrybit) < 0 ? (*iter1 - *iter2 + carrybit + 10) : (*iter1 - *iter2 + carrybit));
		carrybit = (*iter1 - *iter2 + carrybit) < 0 ? -1 : 0;
	}
	*/

	if (answer.numberPart[0] < 0)
	{
		answer.numberPart.clear();
		return answer;
	}

	answer.expPart = (left.expPart < right.expPart ? left.expPart : right.expPart);	//和加法一样处理方法

	return answer;
}