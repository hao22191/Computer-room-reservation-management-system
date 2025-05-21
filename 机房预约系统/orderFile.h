#pragma once
#include <iostream>
#include "globafile.h"
#include <fstream>
#include <map>
#include <string>

class OrderFile
{
public:
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updateOrder();

	//��¼ԤԼ����
	int m_size;

	//��¼����ԤԼ��Ϣ������  key��¼����  value �����¼��ֵ��Ӧ��Ϣ
	std::map<int, std::map<std::string, std::string>> m_orderData;
};