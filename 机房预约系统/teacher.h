#pragma once
#include<iostream>
#include "identity.h"
#include<vector>

class Teacher :public Identity
{
public:
	//Ĭ�Ϲ���
	Teacher();

	//�вι���
	Teacher(int empid, std::string name, std::string pwd);

	//�˵�����
	virtual void openMenu();

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	//ְ����
	int m_empId;
};