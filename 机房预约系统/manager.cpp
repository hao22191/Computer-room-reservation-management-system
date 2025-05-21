#include "manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(std::string name, std::string pwd)
{
	//初始换管理员信息
	this->m_name = name;
	this->m_pwd = pwd;

	//初始化容器  并获取到文件中所有 学生教师的信息
	this->initVector();

	//初始化机房信息
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);;

	ComputerRoom Com;
	while (ifs >> Com.m_Comid && ifs >> Com.m_Maxnum)
	{
		vCom.push_back(Com);
	}
	ifs.close();
	//std::cout << "机房的数量为：" << vCom.size() << std::endl;
}

//菜单界面
void Manager::openMenu()
{
	std::cout << "欢迎管理员"<<this->m_name<<"登录！" << std::endl << std::endl;
	std::cout << "\t\t ------------------------------\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         1.添加账号           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         2.查看账号           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         3.查看机房           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         4.清空预约           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         0.注销登录           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t ------------------------------\n";
	std::cout << "请输入您的选择：";
}

//添加账号
void Manager::addPerson()
{
	std::cout << "请输入添加账号的类型：" << std::endl;
	std::cout << "1. 添加学生" << std::endl;
	std::cout << "2. 添加老师" << std::endl;

	std::string filename;  //操作文件名
	std::string tip;  //提示id
	std::string errortip;

	std::ofstream ofs;

	char select;
	while (true)
	{
		std::cin >> select;  //接受用户选择 
		if (select == '1')
		{
			//添加学生
			filename = STUDENT_FILE;
			tip = "请输入学号：";
			errortip = "学号重复，请重新输入！";
			break;
		}
		else if (select == '2')
		{
			//添加学生
			filename = TEACHER_FILE;
			tip = "请输入职工号";
			errortip = "职工号重复，请重新输入！";
			break;
		}
		else
		{
			//错误输入
			std::cout << "输入错误！" << std::endl;
		}
	}

	//利用追加方式写文件
	ofs.open(filename, std::ios::out | std::ios::app);

	int id; //学号/职工号
	std::string name;
	std::string pwd;

	std::cout << tip << std::endl;
	while (true)
	{
		std::cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			std::cout << errortip << std::endl;
		}
		else
		{
			break;
		}
	}

	std::cout << "请输入姓名" << std::endl;
	std::cin >> name;
	
	std::cout << "请输入密码" << std::endl;
	std::cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << std::endl;

	std::cout << "添加完成" << std::endl;

	system("pause");
	system("cls");
	ofs.close();

	this->initVector();
}

void printStudent(Student &s)
{
	std::cout << "学号：" << s.m_id << " 姓名：" << s.m_name << " 密码：" << s.m_pwd << std::endl;
}

void printTeacher(Teacher& s)
{
	std::cout << "职工号：" << s.m_empId << " 姓名：" << s.m_name << " 密码：" << s.m_pwd << std::endl;
}

//查看账号
void Manager::showPerson()
{
	std::cout << "请选择查看的内容：" << std::endl;
	std::cout << "1.查看所有的学生" << std::endl;
	std::cout << "2.查看所有的老师" << std::endl;

	char select;  //接收用户选择

	while (true)
	{
		std::cin >> select;
		if (select == '1')
		{
			//查看学生
			std::cout << "学生信息如下：" << std::endl;
			std::for_each(vStu.begin(), vStu.end(), printStudent);
			break;
		}
		else if (select == '2')
		{
			//查看老师
			std::cout << "教师信息如下：" << std::endl;
			std::for_each(vTea.begin(), vTea.end(), printTeacher);
			break;
		}
		else
		{
			//错误输入
			std::cout << "输入错误！" << std::endl;
		}
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	std::cout << "机房信息如下：" << std::endl;
	for (std::vector<ComputerRoom>::iterator it = vCom.begin();it != vCom.end();it++)
	{
		std::cout << "机房编号：" << it->m_Comid << " 机房最大容量：" << it->m_Maxnum << std::endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	std::cout << "是否确认清空" << std::endl;
	std::cout << "1.确认" << std::endl;
	std::cout << "2.取消" << std::endl;
	char select;  //接收用户选择

	while (true)
	{
		std::cin >> select;
		if (select == '1')
		{
			std::ofstream ofs;
			ofs.open(ORDER_FILE, std::ios::trunc);
			ofs.close();
			std::cout << "清空成功！" << std::endl;
			break;
		}
		else if (select == '2')
		{
			break;
		}
		else
		{
			//错误输入
			std::cout << "输入错误！" << std::endl;
		}
	}

	system("pause");
	system("cls");
}

//初始化容器
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//读取信息  学生 老师
	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "文件读取失败！" << std::endl;
		return;
	}
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		vStu.push_back(s);
	}
	//std::cout << "学生的数量为：" << vStu.size() << std::endl;

	ifs.close();;
	ifs.open(TEACHER_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "文件读取失败！" << std::endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}
	//std::cout << "教师的数量为：" << vTea.size() << std::endl;
	ifs.close();
}

//检测重复
bool Manager::checkRepeat(int id, char type)
{
	if (type == '1')
	{
		//检测学生
		for (std::vector<Student>::iterator it = vStu.begin();it != vStu.end();it++)
		{
			if (it->m_id == id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测教师
		for (std::vector<Teacher>::iterator it = vTea.begin();it != vTea.end();it++)
		{
			if (it->m_empId == id)
			{
				return true;
			}
		}
	}
	return false;
}