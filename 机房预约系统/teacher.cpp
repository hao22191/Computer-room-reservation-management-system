#include "teacher.h"
#include<iostream>
#include<string>
#include "identity.h"
#include "computerRoom.h"
#include "globafile.h"
#include "orderFile.h"

//Ĭ�Ϲ���
Teacher::Teacher()
{

}

//�вι���
Teacher::Teacher(int empid, std::string name, std::string pwd)
{
	this->m_empId = empid;
	this->m_name = name;
	this->m_pwd = pwd;
}

//�˵�����
void Teacher::openMenu()
{
	std::cout << "��ӭ��ʦ" << this->m_name << "��¼��" << std::endl << std::endl;
	std::cout << "\t\t ------------------------------\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         1.�鿴����ԤԼ       |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         2.���ԤԼ           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         0.ע����¼           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t ------------------------------\n";
	std::cout << "����������ѡ��";
}

//�鿴����ԤԼ
void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "��ԤԼ��¼��" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0;i < of.m_size;i++)
	{
		std::cout << i + 1 << "��";
		std::cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
		std::cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
		std::cout << "ѧ�ţ�" << of.m_orderData[i]["stuid"] << " ";
		std::cout << "������" << of.m_orderData[i]["stuname"] << " ";
		std::cout << "�����ţ�" << of.m_orderData[i]["roomid"] << " ";
		std::string status = "״̬��";
		//1 ԤԼ��  2 ԤԼ�ɹ�  -1 ԤԼʧ��  0  ȡ��ԤԼ
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "ԤԼ��";
		}
		if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		if (of.m_orderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		if (of.m_orderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		std::cout << status << std::endl;

	}
	system("pause");
	system("cls");
}

//���ԤԼ
void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		std::cout << "��ԤԼ��¼��" << std::endl;
		system("pause");
		system("cls");
		return;
	}
	std::cout << "����˵�ԤԼ��¼���£�" << std::endl;
	std::vector<int> v;  //�������������е��±���
	int index = 1;
	for (int i = 0;i < of.m_size;i++)
	{
		if (of.m_orderData[i]["status"] == "1" )
		{
			v.push_back(i);
			std::cout << index++ << "�� ";
			std::cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"] << " ";
			std::cout << "ʱ��Σ�" << (of.m_orderData[i]["interval"] == "1" ? "����" : "����") << " ";
			std::cout << "ѧ�ţ�" << of.m_orderData[i]["stuid"] << " ";
			std::cout << "������" << of.m_orderData[i]["stuname"] << " ";
			std::cout << "�����ţ�" << of.m_orderData[i]["roomid"] << " ";
			std::cout << "״̬��ԤԼ��" << std::endl;
		}
	}
	std::cout << "��������˵�ԤԼ��¼��0������" << std::endl;
	int select = 0;  //�����û�ѡ���ԤԼ��¼
	int ret = 0;  //����ԤԼ�����¼
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
				std::cout << "��������˽����" << std::endl;
				std::cout << "1.ͨ��" << std::endl;
				std::cout << "2.��ͨ��" << std::endl;
				std::cin >> ret;
				if (ret == 1)
				{
					//ͨ�����
					of.m_orderData[v[select - 1]]["status"] = "2";
					std::cout << "�����ϣ���ͨ��ԤԼ��" << std::endl;
				}
				else if (ret == 2)
				{
					//��ͨ�����
					of.m_orderData[v[select - 1]]["status"] = "-1";
					std::cout << "�����ϣ��Ѿܾ�ԤԼ��" << std::endl;
				}
				of.updateOrder();
				break;
			}
		}
		std::cout << "�����������������룡" << std::endl;
	}
	system("pause");
	system("cls");
}