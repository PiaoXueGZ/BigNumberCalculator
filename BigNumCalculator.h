#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

typedef int8_t DecimalismBit_t;	//十进制位
typedef std::vector<DecimalismBit_t> NumberPart_t;	//数字部分类型

typedef struct BigNumber
{
	NumberPart_t numberPart;
	int expPart;
	//bool isNegative = false;
} BigNum_t, BigNumber_t;

//BigNumber_t BigNumberAdd(BigNumber_t num1, BigNumber_t num2);	//大数相加
BigNumber_t operator +(BigNumber_t num1, BigNumber_t num2);	//大数加法重载
BigNumber_t operator -(BigNumber_t left, BigNumber_t right);	//大数减法重载
