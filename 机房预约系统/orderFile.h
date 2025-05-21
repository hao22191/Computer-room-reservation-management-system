#pragma once
#include <iostream>
#include "globafile.h"
#include <fstream>
#include <map>
#include <string>

class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_size;

	//记录所有预约信息的容器  key记录条数  value 具体记录键值对应信息
	std::map<int, std::map<std::string, std::string>> m_orderData;
};