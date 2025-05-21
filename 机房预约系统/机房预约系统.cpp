#include<iostream>
#include "identity.h"
#include "globafile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include<fstream>
#include<string>

//进入教师子菜单界面
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//调用教师子菜单
		teacher->openMenu();

		Teacher* tea = (Teacher*)teacher;
		char select = 0;
		//接收用户选择
		std::cin >> select;
		switch (select)
		{
		case '1':  //查看所有人预约
			tea->showAllOrder();
			break;
		case '2':  //审核预约
			tea->validOrder();
			break;
		case '0':  //注销账号
			delete teacher;
			std::cout << "注销成功" << std::endl;
			system("pause");
			system("cls");
			return;
		default:
			std::cout << "输入有误，请重新选择！" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//进入学生子菜单界面
void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学生子菜单
		student->openMenu();

		Student* stu = (Student*)student;

		char select = 0;
		//接收用户选择
		std::cin >> select;
		switch (select)
		{
		case '1':  //申请预约
			stu->applyOrder();
			break;
		case '2':  //查看自身预约
			stu->showMyOrder();
			break;
		case '3':  //查看所有人预约
			stu->showAllOrder();
			break;
		case '4':  //取消预约
			stu->cancleOrder();
			break;
		case '0':  //注销账号
			delete student;
			std::cout << "注销成功" << std::endl;
			system("pause");
			system("cls");
			return;
		default:
			std::cout << "输入有误，请重新选择！" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//进入管理员子菜单界面
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//调用管理员子菜单
		manager->openMenu();

		//将父类指针转化为子类指针  调用子类中的其他接口
		Manager * man = (Manager*)manager;

		char select = 0;
		//接收用户选择
		std::cin >> select;
		switch (select)
		{
		case '1':  //添加账号
			std::cout << "添加账号" << std::endl;
			man->addPerson();
			break;
		case '2':  //查看账号
			std::cout << "查看账号" << std::endl;
			man->showPerson();
			break;
		case '3':  //查看机房
			std::cout << "查看机房" << std::endl;
			man->showComputer();
			break;
		case '4':  //清空预约
			std::cout << "清空预约" << std::endl;
			man->cleanFile();
			break;
		case '0':  //注销账号
			delete manager;
			std::cout << "注销成功" << std::endl;
			system("pause");
			system("cls");
			return;
		default:
			std::cout << "输入有误，请重新选择！" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//登录功能  参数1  操作文件名     参数2  操作身份类型
void LoginIn(std::string filename, int type)
{
	//父类指针  用于指向子类对象
	Identity* person = NULL;

	//读文件
	std::ifstream ifs;
	ifs.open(filename, std::ios::in); 

	//判断文件是否存在
	if (!ifs.is_open())
	{
		std::cout << "文件不存在" << std::endl;
		ifs.close();
		return;
	}

	//准备接收用户信息
	int id = 0;
	std::string name;
	std::string pwd;

	//判断身份
	if (type == 1)  //学生
	{
		std::cout << "请输入你的学号：" << std::endl;
		std::cin >> id;
	}
	if (type == 2)  //教师
	{
		std::cout << "请输入你的职工号：" << std::endl;
		std::cin >> id;
	}

	std::cout << "请输入用户名：" << std::endl;
	std::cin >> name;

	std::cout << "请输入密码：" << std::endl;
	std::cin >> pwd;

	if (type == 1)  //学生身份验证
	{
		int fid;  //从文件中读取的 id 号
		std::string fname;  //从文件中读取的姓名
		std::string fpwd;  //从文件中读取的密码
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				std::cout << "学生身份验证成功！" << std::endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	if (type == 2)  //教师身份验证
	{
		int fid;  //从文件中读取的 id 号
		std::string fname;  //从文件中读取的姓名
		std::string fpwd;  //从文件中读取的密码
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				std::cout << "教师身份验证成功！" << std::endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	if (type == 3)  //管理员身份验证
	{
		std::string fname;  //从文件中读取的姓名
		std::string fpwd;  //从文件中读取的密码
		while ( ifs >> fname && ifs >> fpwd)
		{
			if ( fname == name && fpwd == pwd)
			{
				std::cout << "管理员身份验证成功！" << std::endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}

	std::cout << "验证登录失败！" << std::endl;
	system("pause");
	system("cls");
	return;
}


int main()
{
	char select = '0';  //用于接收用户选择
	while (true)
	{
		std::cout << "======================欢迎来到机房预约系统======================" << std::endl;
		std::cout << std::endl << "请选择您的身份" << std::endl;
		std::cout << "\t\t ------------------------------\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         1.学生代表           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         2.老    师           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         3.管 理 员           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         0.退    出           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t ------------------------------\n";
		std::cout << "请输入您的选择：";

		std::cin >> select;  //接受用户选择
		switch (select)  //根据用户选择  实现不同接口
		{
		case '1':  //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case '2':  //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case '3':  //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case '0':  //退出系统
			std::cout << "欢迎下次使用" << std::endl;
			system("pause");
			return 0;
			break;
		default:
			std::cout << "输入有误，请重新选择！" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}