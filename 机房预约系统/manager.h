#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include "identity.h"
#include "globafile.h"
#include "student.h"
#include "teacher.h"
#include "computerRoom.h"

class Manager :public Identity
{
public:
	//默认构造
	Manager();

	//有参构造
	Manager(std::string name, std::string pwd);

	//菜单界面
	virtual void openMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看机房信息
	void showComputer();

	//清空预约记录
	void cleanFile();

	//检测重复
	bool checkRepeat(int id, char type);

	//初始化容器
	void initVector();

	//学生容器
	std::vector<Student> vStu;

	//教师容器
	std::vector<Teacher> vTea;

	//机房信息容器
	std::vector<ComputerRoom> vCom;
};