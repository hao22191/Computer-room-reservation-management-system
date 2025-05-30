#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include "identity.h"
#include "computerRoom.h"
#include "globafile.h"
#include "orderFile.h"

class Student :public Identity
{
public:
	//默认构造
	Student();

	//有参构造
	Student(int id, std::string name, std::string pwd);

	//菜单界面
	virtual void openMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancleOrder();

	//学生学号
	int m_id;

	//机房容器
	std::vector<ComputerRoom> vCom;
};