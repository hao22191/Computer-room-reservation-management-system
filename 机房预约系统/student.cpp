#include "student.h"

//默认构造
Student::Student()
{

}

//有参构造
Student::Student(int id, std::string name, std::string pwd)
{
	//初始化属性
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	//初始化机房信息
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);

	ComputerRoom com;
	while (ifs >> com.m_Comid && ifs >> com.m_Maxnum)
	{
		//将读取到的信息存放到容器中
		vCom.push_back(com);
	}
	ifs.close();
}

//菜单界面
void Student::openMenu()
{
	std::cout << "欢迎学生" << this->m_name << "登录！" << std::endl << std::endl;
	std::cout << "\t\t ------------------------------\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         1.申请预约           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         2.查看我的预约       |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         3.查看所有预约       |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         4.取消预约           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         0.注销登录           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t ------------------------------\n";
	std::cout << "请输入您的选择：";
}

//申请预约
void Student::applyOrder()
{
	std::cout << "机房开放的时间为周一至周五！" << std::endl;
	std::cout << "请输入申请预约的时间" << std::endl;
	std::cout << "1.周一" << std::endl;
	std::cout << "2.周二" << std::endl;
	std::cout << "3.周三" << std::endl;
	std::cout << "4.周四" << std::endl;
	std::cout << "5.周五" << std::endl;

	char date;  //日期
	char interval;  //时间段
	char roomid;  //机房号
	while (true)
	{
		std::cin >> date;
		if (date >= '1' && date <= '5')
		{
			break;
		}
		else
		{
			std::cout << "输入有误，请重新输入!" << std::endl;
		}
	}

	std::cout << "请输入申请的时间段：" << std::endl;
	std::cout << "1.上午" << std::endl;
	std::cout << "2.下午" << std::endl;
	while (true)
	{
		std::cin >> interval;
		if (interval >= '1' && interval <= '2')
		{
			break;
		}
		else
		{
			std::cout << "输入有误，请重新输入!" << std::endl;
		}
	}

	std::cout << "请选择机房：" << std::endl;
	for (int i = 0;i < vCom.size();i++)
	{
		std::cout << vCom[i].m_Comid <<"号机房的容量为："<<vCom[i].m_Maxnum << std::endl;
	}
	while (true)
	{
		std::cin >> roomid;
		if (roomid >= '1' && roomid <= '3')
		{
			break;
		}
		else
		{
			std::cout << "输入有误，请重新输入!" << std::endl;
		}
	}
	std::cout << "预约成功，审核中！" << std::endl;

	std::ofstream ofs;
	ofs.open(ORDER_FILE, std::ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuid:" << this->m_id << " ";
	ofs << "stuname:" << this->m_name << " ";
	ofs << "roomid:" << roomid << " ";
	ofs << "status:" << 1 << std::endl;

	ofs.close();

	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder()
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
		//string 转 int
		//string 利用 .c_str() 转 const char*
		//利用 atoi (const char*) 转 int
		if (this->m_id == atoi(of.m_orderData[i]["stuid"].c_str()))  //找到了自身的预约
		{
			std::cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
			std::cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午":"下午") << " ";
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
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::showAllOrder()
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
		std::cout << i + 1 << "、" ;
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

//取消预约
void Student::cancleOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "无预约记录！" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "审核中或者预约成功的记录可以取消，请选择要取消的预约：" << std::endl;
	std::vector<int> v;  //存放在最大容器中的下标编号
	int index = 1;
	for (int i = 0;i < of.m_size;i++)
	{
		//先判断是否为自身编号
		if (atoi(of.m_orderData[i]["stuid"].c_str()) == this->m_id)
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				std::cout << index++ << "、 ";
				std::cout << "预约日期：周" << of.m_orderData[i]["date"] << " ";
				std::cout << "时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
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
				std::cout << status << std::endl;
			}
		}
	}
	std::cout << "请输入要取消的记录，0代表返回" << std::endl;
	int select = 0;
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
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				std::cout << "已取消预约！" << std::endl;
				break;
			}
		}
		std::cout << "输入有误，请重新输入！" << std::endl;
	}
	system("pause");
	system("cls");
}