#include<iostream>
#include "identity.h"
#include "globafile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include<fstream>
#include<string>

//�����ʦ�Ӳ˵�����
void teacherMenu(Identity*& teacher)
{
	while (true)
	{
		//���ý�ʦ�Ӳ˵�
		teacher->openMenu();

		Teacher* tea = (Teacher*)teacher;
		char select = 0;
		//�����û�ѡ��
		std::cin >> select;
		switch (select)
		{
		case '1':  //�鿴������ԤԼ
			tea->showAllOrder();
			break;
		case '2':  //���ԤԼ
			tea->validOrder();
			break;
		case '0':  //ע���˺�
			delete teacher;
			std::cout << "ע���ɹ�" << std::endl;
			system("pause");
			system("cls");
			return;
		default:
			std::cout << "��������������ѡ��" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//����ѧ���Ӳ˵�����
void studentMenu(Identity*& student)
{
	while (true)
	{
		//����ѧ���Ӳ˵�
		student->openMenu();

		Student* stu = (Student*)student;

		char select = 0;
		//�����û�ѡ��
		std::cin >> select;
		switch (select)
		{
		case '1':  //����ԤԼ
			stu->applyOrder();
			break;
		case '2':  //�鿴����ԤԼ
			stu->showMyOrder();
			break;
		case '3':  //�鿴������ԤԼ
			stu->showAllOrder();
			break;
		case '4':  //ȡ��ԤԼ
			stu->cancleOrder();
			break;
		case '0':  //ע���˺�
			delete student;
			std::cout << "ע���ɹ�" << std::endl;
			system("pause");
			system("cls");
			return;
		default:
			std::cout << "��������������ѡ��" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//�������Ա�Ӳ˵�����
void managerMenu(Identity*& manager)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->openMenu();

		//������ָ��ת��Ϊ����ָ��  ���������е������ӿ�
		Manager * man = (Manager*)manager;

		char select = 0;
		//�����û�ѡ��
		std::cin >> select;
		switch (select)
		{
		case '1':  //����˺�
			std::cout << "����˺�" << std::endl;
			man->addPerson();
			break;
		case '2':  //�鿴�˺�
			std::cout << "�鿴�˺�" << std::endl;
			man->showPerson();
			break;
		case '3':  //�鿴����
			std::cout << "�鿴����" << std::endl;
			man->showComputer();
			break;
		case '4':  //���ԤԼ
			std::cout << "���ԤԼ" << std::endl;
			man->cleanFile();
			break;
		case '0':  //ע���˺�
			delete manager;
			std::cout << "ע���ɹ�" << std::endl;
			system("pause");
			system("cls");
			return;
		default:
			std::cout << "��������������ѡ��" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

//��¼����  ����1  �����ļ���     ����2  �����������
void LoginIn(std::string filename, int type)
{
	//����ָ��  ����ָ���������
	Identity* person = NULL;

	//���ļ�
	std::ifstream ifs;
	ifs.open(filename, std::ios::in); 

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		std::cout << "�ļ�������" << std::endl;
		ifs.close();
		return;
	}

	//׼�������û���Ϣ
	int id = 0;
	std::string name;
	std::string pwd;

	//�ж����
	if (type == 1)  //ѧ��
	{
		std::cout << "���������ѧ�ţ�" << std::endl;
		std::cin >> id;
	}
	if (type == 2)  //��ʦ
	{
		std::cout << "���������ְ���ţ�" << std::endl;
		std::cin >> id;
	}

	std::cout << "�������û�����" << std::endl;
	std::cin >> name;

	std::cout << "���������룺" << std::endl;
	std::cin >> pwd;

	if (type == 1)  //ѧ�������֤
	{
		int fid;  //���ļ��ж�ȡ�� id ��
		std::string fname;  //���ļ��ж�ȡ������
		std::string fpwd;  //���ļ��ж�ȡ������
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				std::cout << "ѧ�������֤�ɹ���" << std::endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	if (type == 2)  //��ʦ�����֤
	{
		int fid;  //���ļ��ж�ȡ�� id ��
		std::string fname;  //���ļ��ж�ȡ������
		std::string fpwd;  //���ļ��ж�ȡ������
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			if (fid == id && fname == name && fpwd == pwd)
			{
				std::cout << "��ʦ�����֤�ɹ���" << std::endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	if (type == 3)  //����Ա�����֤
	{
		std::string fname;  //���ļ��ж�ȡ������
		std::string fpwd;  //���ļ��ж�ȡ������
		while ( ifs >> fname && ifs >> fpwd)
		{
			if ( fname == name && fpwd == pwd)
			{
				std::cout << "����Ա�����֤�ɹ���" << std::endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}

	std::cout << "��֤��¼ʧ�ܣ�" << std::endl;
	system("pause");
	system("cls");
	return;
}


int main()
{
	char select = '0';  //���ڽ����û�ѡ��
	while (true)
	{
		std::cout << "======================��ӭ��������ԤԼϵͳ======================" << std::endl;
		std::cout << std::endl << "��ѡ���������" << std::endl;
		std::cout << "\t\t ------------------------------\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         1.ѧ������           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         2.��    ʦ           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         3.�� �� Ա           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t|         0.��    ��           |\n";
		std::cout << "\t\t|                              |\n";
		std::cout << "\t\t ------------------------------\n";
		std::cout << "����������ѡ��";

		std::cin >> select;  //�����û�ѡ��
		switch (select)  //�����û�ѡ��  ʵ�ֲ�ͬ�ӿ�
		{
		case '1':  //ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case '2':  //��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case '3':  //����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case '0':  //�˳�ϵͳ
			std::cout << "��ӭ�´�ʹ��" << std::endl;
			system("pause");
			return 0;
			break;
		default:
			std::cout << "��������������ѡ��" << std::endl;
			system("pause");
			system("cls");
			break;
		}
	}


	system("pause");
	return 0;
}