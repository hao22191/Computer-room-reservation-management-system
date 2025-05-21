#include "manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(std::string name, std::string pwd)
{
	//��ʼ������Ա��Ϣ
	this->m_name = name;
	this->m_pwd = pwd;

	//��ʼ������  ����ȡ���ļ������� ѧ����ʦ����Ϣ
	this->initVector();

	//��ʼ��������Ϣ
	std::ifstream ifs;
	ifs.open(COMPUTER_FILE, std::ios::in);;

	ComputerRoom Com;
	while (ifs >> Com.m_Comid && ifs >> Com.m_Maxnum)
	{
		vCom.push_back(Com);
	}
	ifs.close();
	//std::cout << "����������Ϊ��" << vCom.size() << std::endl;
}

//�˵�����
void Manager::openMenu()
{
	std::cout << "��ӭ����Ա"<<this->m_name<<"��¼��" << std::endl << std::endl;
	std::cout << "\t\t ------------------------------\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         1.����˺�           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         2.�鿴�˺�           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         3.�鿴����           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         4.���ԤԼ           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t|         0.ע����¼           |\n";
	std::cout << "\t\t|                              |\n";
	std::cout << "\t\t ------------------------------\n";
	std::cout << "����������ѡ��";
}

//����˺�
void Manager::addPerson()
{
	std::cout << "����������˺ŵ����ͣ�" << std::endl;
	std::cout << "1. ���ѧ��" << std::endl;
	std::cout << "2. �����ʦ" << std::endl;

	std::string filename;  //�����ļ���
	std::string tip;  //��ʾid
	std::string errortip;

	std::ofstream ofs;

	char select;
	while (true)
	{
		std::cin >> select;  //�����û�ѡ�� 
		if (select == '1')
		{
			//���ѧ��
			filename = STUDENT_FILE;
			tip = "������ѧ�ţ�";
			errortip = "ѧ���ظ������������룡";
			break;
		}
		else if (select == '2')
		{
			//���ѧ��
			filename = TEACHER_FILE;
			tip = "������ְ����";
			errortip = "ְ�����ظ������������룡";
			break;
		}
		else
		{
			//��������
			std::cout << "�������" << std::endl;
		}
	}

	//����׷�ӷ�ʽд�ļ�
	ofs.open(filename, std::ios::out | std::ios::app);

	int id; //ѧ��/ְ����
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

	std::cout << "����������" << std::endl;
	std::cin >> name;
	
	std::cout << "����������" << std::endl;
	std::cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << std::endl;

	std::cout << "������" << std::endl;

	system("pause");
	system("cls");
	ofs.close();

	this->initVector();
}

void printStudent(Student &s)
{
	std::cout << "ѧ�ţ�" << s.m_id << " ������" << s.m_name << " ���룺" << s.m_pwd << std::endl;
}

void printTeacher(Teacher& s)
{
	std::cout << "ְ���ţ�" << s.m_empId << " ������" << s.m_name << " ���룺" << s.m_pwd << std::endl;
}

//�鿴�˺�
void Manager::showPerson()
{
	std::cout << "��ѡ��鿴�����ݣ�" << std::endl;
	std::cout << "1.�鿴���е�ѧ��" << std::endl;
	std::cout << "2.�鿴���е���ʦ" << std::endl;

	char select;  //�����û�ѡ��

	while (true)
	{
		std::cin >> select;
		if (select == '1')
		{
			//�鿴ѧ��
			std::cout << "ѧ����Ϣ���£�" << std::endl;
			std::for_each(vStu.begin(), vStu.end(), printStudent);
			break;
		}
		else if (select == '2')
		{
			//�鿴��ʦ
			std::cout << "��ʦ��Ϣ���£�" << std::endl;
			std::for_each(vTea.begin(), vTea.end(), printTeacher);
			break;
		}
		else
		{
			//��������
			std::cout << "�������" << std::endl;
		}
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	std::cout << "������Ϣ���£�" << std::endl;
	for (std::vector<ComputerRoom>::iterator it = vCom.begin();it != vCom.end();it++)
	{
		std::cout << "������ţ�" << it->m_Comid << " �������������" << it->m_Maxnum << std::endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	std::cout << "�Ƿ�ȷ�����" << std::endl;
	std::cout << "1.ȷ��" << std::endl;
	std::cout << "2.ȡ��" << std::endl;
	char select;  //�����û�ѡ��

	while (true)
	{
		std::cin >> select;
		if (select == '1')
		{
			std::ofstream ofs;
			ofs.open(ORDER_FILE, std::ios::trunc);
			ofs.close();
			std::cout << "��ճɹ���" << std::endl;
			break;
		}
		else if (select == '2')
		{
			break;
		}
		else
		{
			//��������
			std::cout << "�������" << std::endl;
		}
	}

	system("pause");
	system("cls");
}

//��ʼ������
void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
	//��ȡ��Ϣ  ѧ�� ��ʦ
	std::ifstream ifs;
	ifs.open(STUDENT_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "�ļ���ȡʧ�ܣ�" << std::endl;
		return;
	}
	Student s;
	while (ifs >> s.m_id && ifs >> s.m_name && ifs >> s.m_pwd)
	{
		vStu.push_back(s);
	}
	//std::cout << "ѧ��������Ϊ��" << vStu.size() << std::endl;

	ifs.close();;
	ifs.open(TEACHER_FILE, std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "�ļ���ȡʧ�ܣ�" << std::endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_empId && ifs >> t.m_name && ifs >> t.m_pwd)
	{
		vTea.push_back(t);
	}
	//std::cout << "��ʦ������Ϊ��" << vTea.size() << std::endl;
	ifs.close();
}

//����ظ�
bool Manager::checkRepeat(int id, char type)
{
	if (type == '1')
	{
		//���ѧ��
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
		//����ʦ
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