#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

typedef int8_t DecimalismBit_t;	//ʮ����λ
typedef std::vector<DecimalismBit_t> NumberPart_t;	//���ֲ�������

typedef struct BigNumber
{
	NumberPart_t numberPart;
	int expPart;
	//bool isNegative = false;
} BigNum_t, BigNumber_t;

//BigNumber_t BigNumberAdd(BigNumber_t num1, BigNumber_t num2);	//�������
BigNumber_t operator +(BigNumber_t num1, BigNumber_t num2);	//�����ӷ�����
BigNumber_t operator -(BigNumber_t left, BigNumber_t right);	//������������
