#include "teacher.h"
#include<iostream>
#include<string>
#include "identity.h"
#include "computerRoom.h"
#include "globafile.h"
#include "orderFile.h"

//默认构造
Teacher::Teacher()
{

}

//有参构造
Teacher::Teacher(int empid, std::string name, std::string pwd)
{
	this->m_empId = empid;
	this->m_name = name;
	this->m_pwd = pwd;
}

//菜单界面
void Teacher::openMenu()
{
	std::cout << "欢迎教师" << this->m_name << "登录！" << std::endl << std::endl;
	std::cout << "\t\t ------------------------------\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         1.查看所有预约       |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         2.审核预约           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         0.注销登录           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t ------------------------------\n";
	std::cout << "请输入您的选择：";
}

//查看所有预约
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "无预约记录！" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_size;i++)
	{
		std::cout << i + 1 << "、";
		std::cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
		std::cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
		std::cout << "学号：" << of.m_orderData[i]["stuid"] << " ";
		std::cout << "姓名：" << of.m_orderData[i]["stuname"] << " ";
		std::cout << "机房号：" << of.m_orderData[i]["roomid"] << " ";
		std::string status = "状态：";
		//1 预约中  2 预约成功  -1 预约失败  0  取消预约
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "预约中";
		}
		if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		if (of.m_orderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		if (of.m_orderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		std::cout << status << std::endl;

	}
	system("pause");
	system("cls");
}

//审核预约
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "无预约记录！" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "待审核的预约记录如下：" << std::endl;
	std::vector<int> v;  //存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0;i < of.m_size;i++)
	{
		if (of.m_orderData[i]["status"] == "1" )
		{
			v.push_back(i);
			std::cout << index++ << "、 ";
			std::cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
			std::cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
			std::cout << "学号：" << of.m_orderData[i]["stuid"] << " ";
			std::cout << "姓名：" << of.m_orderData[i]["stuname"] << " ";
			std::cout << "机房号：" << of.m_orderData[i]["roomid"] << " ";
			std::cout << "状态：预约中" << std::endl;
		}
	}
	std::cout << "请输入审核的预约记录，0代表返回" << std::endl;
	int select = 0;  //接收用户选择的预约记录
	int ret = 0;  //接收预约结果记录
	while (true)
	{
		std::cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				std::cout << "请输入审核结果：" << std::endl;
				std::cout << "1.通过" << std::endl;
				std::cout << "2.不通过" << std::endl;
				std::cin >> ret;
				if (ret == 1)
				{
					//通过情况
					of.m_orderData[v[select - 1]]["status"] = "2";
					std::cout << "审核完毕，已通过预约！" << std::endl;
				}
				else if (ret == 2)
				{
					//不通过情况
					of.m_orderData[v[select - 1]]["status"] = "-1";
					std::cout << "审核完毕，已拒绝预约！" << std::endl;
				}
				of.updateOrder();
				break;
			}
		}
		std::cout << "输入有误，请重新输入！" << std::endl;
	}
	system("pause");
	system("cls");
}