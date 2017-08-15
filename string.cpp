#include <iostream>
#include <string>
#include <cctype>
#include "BigNumCalculator.h"
#include "Str.h"

using namespace std;

inline bool isNumberChar(char c)
{
	return (isdigit(c) || c == '.');
}

inline bool StrHasDot(string str)
{
	return (strchr(str.c_str(), '.') != nullptr ? true : false);
}

bool CanConvertToNumber(string str)	//检测是否能够正常转换成数字
{
	bool hasDot = false;

	for (char c : str)	//检测是否能够正常转换成数字
	{
		if (!isNumberChar(c) || (hasDot == true && c == '.'))
			return false;

		if (c == '.')
			hasDot = true;
	}

	return true;
}

inline int GetBigNumExp(string str)
{																			//find函数没有找到时返回-1
	return (str.find('.') == -1 ? 0 : (str.find('.') + 1 - str.size()));	//+1的原因是因为find()返回的是从0数起的字符位置	
}

string NumberPartToString(NumberPart_t v)
{
	string str;

	while (v[0] == 0)
		v.erase(v.begin());

	for (DecimalismBit_t i : v)
		str.push_back((char)(i + 48));	//数字本身加48正好是数字字符

	return str;
}

NumberPart_t StringToNumberPart(string str)
{
	NumberPart_t v;

	for (char c : str)
	{
		if (c != '.')
			v.push_back(c - 48);	//数字字符减去48正好是数字本身
		else
			continue;
	}

	return v;
}

BigNumber_t StringToBigNum(string str)
{
	if (!CanConvertToNumber(str))
		throw runtime_error("ERROR : Can't convent string to number!");

	BigNumber_t bigNum;

	bigNum.numberPart = StringToNumberPart(str);

	bigNum.expPart = GetBigNumExp(str);

	while (bigNum.numberPart[0] == 0)
		bigNum.numberPart.erase(bigNum.numberPart.begin());	//假如一个大数前面有0，把这些无用的0删掉（删掉不影响数值，方便计算）

	while (*(bigNum.numberPart.end() - 1) == 0)
	{
		bigNum.numberPart.erase(bigNum.numberPart.end() - 1);	//假如一个大数后面有0，把这些0删掉，每删掉一个指数就加一（这样处理不影响数值）
		bigNum.expPart++;
	}

	return bigNum;
}

string BigNumToString(BigNumber_t num)
{
	string str = NumberPartToString(num.numberPart);

	if (num.expPart < 0)
		str.insert(str.end() + num.expPart, '.');
	else if (num.expPart > 0)
		for (int i = 0; i != num.expPart; ++i)
			str.push_back('0');

	return str;
}