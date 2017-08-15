#pragma once

#include <string>
#include "BigNumCalculator.h"

BigNumber_t StringToBigNum(std::string str);	//从字符串转换成大数

std::string BigNumToString(BigNumber_t num);	//从大数转换成字符串