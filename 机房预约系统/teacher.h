#pragma once
#include<iostream>
#include "identity.h"
#include<vector>

class Teacher :public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int empid, std::string name, std::string pwd);

	//菜单界面
	virtual void openMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//职工号
	int m_empId;
};