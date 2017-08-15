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

bool CanConvertToNumber(string str)	//����Ƿ��ܹ�����ת��������
{
	bool hasDot = false;

	for (char c : str)	//����Ƿ��ܹ�����ת��������
	{
		if (!isNumberChar(c) || (hasDot == true && c == '.'))
			return false;

		if (c == '.')
			hasDot = true;
	}

	return true;
}

inline int GetBigNumExp(string str)
{																			//find����û���ҵ�ʱ����-1
	return (str.find('.') == -1 ? 0 : (str.find('.') + 1 - str.size()));	//+1��ԭ������Ϊfind()���ص��Ǵ�0������ַ�λ��	
}

string NumberPartToString(NumberPart_t v)
{
	string str;

	while (v[0] == 0)
		v.erase(v.begin());

	for (DecimalismBit_t i : v)
		str.push_back((char)(i + 48));	//���ֱ����48�����������ַ�

	return str;
}

NumberPart_t StringToNumberPart(string str)
{
	NumberPart_t v;

	for (char c : str)
	{
		if (c != '.')
			v.push_back(c - 48);	//�����ַ���ȥ48���������ֱ���
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
		bigNum.numberPart.erase(bigNum.numberPart.begin());	//����һ������ǰ����0������Щ���õ�0ɾ����ɾ����Ӱ����ֵ��������㣩

	while (*(bigNum.numberPart.end() - 1) == 0)
	{
		bigNum.numberPart.erase(bigNum.numberPart.end() - 1);	//����һ������������0������Щ0ɾ����ÿɾ��һ��ָ���ͼ�һ����������Ӱ����ֵ��
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